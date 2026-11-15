#include "Database.h"

#include <windows.h>

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QSettings>

#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

namespace
{
using MysqlHandle = void;
using MysqlResult = void;
using MysqlRow = char **;

using MysqlInitFn = MysqlHandle *(*)(MysqlHandle *);
using MysqlRealConnectFn = MysqlHandle *(*)(MysqlHandle *, const char *, const char *,
                                            const char *, const char *, unsigned int,
                                            const char *, unsigned long);
using MysqlQueryFn = int (*)(MysqlHandle *, const char *);
using MysqlStoreResultFn = MysqlResult *(*)(MysqlHandle *);
using MysqlFetchRowFn = MysqlRow (*)(MysqlResult *);
using MysqlFreeResultFn = void (*)(MysqlResult *);
using MysqlCloseFn = void (*)(MysqlHandle *);
using MysqlErrorFn = const char *(*)(MysqlHandle *);
using MysqlInsertIdFn = unsigned long long (*)(MysqlHandle *);
using MysqlEscapeFn = unsigned long (*)(MysqlHandle *, char *, const char *, unsigned long);
using MysqlSelectDbFn = int (*)(MysqlHandle *, const char *);
using MysqlSetCharsetFn = int (*)(MysqlHandle *, const char *);

struct MysqlApi
{
    MysqlInitFn init = nullptr;
    MysqlRealConnectFn realConnect = nullptr;
    MysqlQueryFn query = nullptr;
    MysqlStoreResultFn storeResult = nullptr;
    MysqlFetchRowFn fetchRow = nullptr;
    MysqlFreeResultFn freeResult = nullptr;
    MysqlCloseFn close = nullptr;
    MysqlErrorFn error = nullptr;
    MysqlInsertIdFn insertId = nullptr;
    MysqlEscapeFn escape = nullptr;
    MysqlSelectDbFn selectDb = nullptr;
    MysqlSetCharsetFn setCharset = nullptr;
};

MysqlApi &api()
{
    static MysqlApi instance;
    return instance;
}

template <typename Fn>
bool loadFunction(HMODULE library, const char *name, Fn &fn)
{
    fn = reinterpret_cast<Fn>(GetProcAddress(library, name));
    return fn != nullptr;
}

std::string quoted(const std::string &value)
{
    return "'" + value + "'";
}

std::string cell(MysqlRow row, int index)
{
    return row[index] == nullptr ? std::string() : std::string(row[index]);
}

bool validDatabaseName(const std::string &name)
{
    return !name.empty() && name.size() <= 64 &&
        std::all_of(name.begin(), name.end(), [](unsigned char ch) {
            return std::isalnum(ch) != 0 || ch == '_';
        });
}
}

Database::Database() = default;

Database::~Database()
{
    if (connection_ != nullptr && api().close != nullptr)
    {
        api().close(connection_);
        connection_ = nullptr;
    }

    if (library_ != nullptr)
    {
        FreeLibrary(static_cast<HMODULE>(library_));
        library_ = nullptr;
    }
}

std::string Database::configPath()
{
    const QString appDir = QCoreApplication::applicationDirPath();
    QStringList candidates = {
        appDir + "/database.ini",
        QDir::currentPath() + "/database.ini",
        QFileInfo(appDir + "/../database.ini").absoluteFilePath(),
        QFileInfo(appDir + "/../../database.ini").absoluteFilePath()
    };

    for (const QString &path : candidates)
    {
        if (QFileInfo::exists(path))
        {
            return path.toStdString();
        }
    }

    return (appDir + "/database.ini").toStdString();
}

Database::Settings Database::loadSettings()
{
    QSettings ini(QString::fromStdString(configPath()), QSettings::IniFormat);
    ini.beginGroup("mysql");

    Settings settings;
    settings.host = ini.value("host", "127.0.0.1").toString().toStdString();
    settings.port = ini.value("port", 3306).toInt();
    settings.user = ini.value("user", "root").toString().toStdString();
    settings.password = ini.value("password").toString().toStdString();
    settings.database = ini.value("database", "staynear").toString().toStdString();
    return settings;
}

void Database::saveSettings(const Settings &settings)
{
    QSettings ini(QString::fromStdString(configPath()), QSettings::IniFormat);
    ini.beginGroup("mysql");
    ini.setValue("host", QString::fromStdString(settings.host));
    ini.setValue("port", settings.port);
    ini.setValue("user", QString::fromStdString(settings.user));
    ini.setValue("password", QString::fromStdString(settings.password));
    ini.setValue("database", QString::fromStdString(settings.database));
    ini.sync();
}

bool Database::isOpen() const
{
    return connection_ != nullptr;
}

const std::string &Database::lastError() const
{
    return lastError_;
}

bool Database::loadClient()
{
    if (library_ != nullptr)
    {
        return true;
    }

    const std::vector<std::wstring> searchDirs = {
        L"C:\\Program Files\\MySQL\\MySQL Server 8.0\\bin",
        L"C:\\Program Files\\MySQL\\MySQL Server 8.4\\bin",
        L"C:\\Program Files\\MySQL\\MySQL Server 9.0\\bin"
    };

    for (const std::wstring &dir : searchDirs)
    {
        if (QDir(QString::fromStdWString(dir)).exists())
        {
            SetDllDirectoryW(dir.c_str());
            break;
        }
    }

    const std::vector<std::wstring> libraries = {
        L"libmysql.dll",
        L"C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib\\libmysql.dll",
        L"C:\\Program Files\\MySQL\\MySQL Server 8.0\\bin\\libmysql.dll",
        L"C:\\Program Files\\MySQL\\MySQL Server 8.4\\lib\\libmysql.dll"
    };

    HMODULE library = nullptr;
    for (const std::wstring &path : libraries)
    {
        library = LoadLibraryW(path.c_str());
        if (library != nullptr)
        {
            break;
        }
    }

    if (library == nullptr)
    {
        lastError_ = "Could not load libmysql.dll. Install MySQL Server 8 and keep it on this computer.";
        return false;
    }

    MysqlApi &mysql = api();
    const bool loaded =
        loadFunction(library, "mysql_init", mysql.init) &&
        loadFunction(library, "mysql_real_connect", mysql.realConnect) &&
        loadFunction(library, "mysql_query", mysql.query) &&
        loadFunction(library, "mysql_store_result", mysql.storeResult) &&
        loadFunction(library, "mysql_fetch_row", mysql.fetchRow) &&
        loadFunction(library, "mysql_free_result", mysql.freeResult) &&
        loadFunction(library, "mysql_close", mysql.close) &&
        loadFunction(library, "mysql_error", mysql.error) &&
        loadFunction(library, "mysql_insert_id", mysql.insertId) &&
        loadFunction(library, "mysql_real_escape_string", mysql.escape) &&
        loadFunction(library, "mysql_select_db", mysql.selectDb) &&
        loadFunction(library, "mysql_set_character_set", mysql.setCharset);

    if (!loaded)
    {
        lastError_ = "libmysql.dll is missing required MySQL functions.";
        FreeLibrary(library);
        return false;
    }

    library_ = library;
    return true;
}

bool Database::query(const std::string &sql)
{
    if (api().query(connection_, sql.c_str()) != 0)
    {
        lastError_ = api().error(connection_);
        return false;
    }

    return true;
}

std::string Database::escape(const std::string &value) const
{
    std::string buffer(value.size() * 2 + 1, '\0');
    const unsigned long length = api().escape(
        connection_, buffer.data(), value.c_str(), static_cast<unsigned long>(value.size())
    );
    buffer.resize(length);
    return buffer;
}

bool Database::open(const Settings &settings)
{
    lastError_.clear();
    if (settings.host.empty() || settings.user.empty() ||
        settings.port < 1 || settings.port > 65535 ||
        !validDatabaseName(settings.database))
    {
        lastError_ = "Enter a host, user, valid port, and database name using only letters, numbers, and underscores.";
        return false;
    }

    if (!loadClient())
    {
        return false;
    }

    if (connection_ != nullptr)
    {
        api().close(connection_);
        connection_ = nullptr;
    }

    MysqlHandle *mysql = api().init(nullptr);
    if (mysql == nullptr)
    {
        lastError_ = "mysql_init failed.";
        return false;
    }

    MysqlHandle *connected = api().realConnect(
        mysql,
        settings.host.c_str(),
        settings.user.c_str(),
        settings.password.c_str(),
        nullptr,
        static_cast<unsigned int>(settings.port),
        nullptr,
        0
    );

    if (connected == nullptr)
    {
        lastError_ = api().error(mysql);
        api().close(mysql);
        return false;
    }

    connection_ = connected;
    api().setCharset(connection_, "utf8mb4");

    if (!query("CREATE DATABASE IF NOT EXISTS `" + settings.database +
               "` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci"))
    {
        api().close(connection_);
        connection_ = nullptr;
        return false;
    }

    if (api().selectDb(connection_, settings.database.c_str()) != 0)
    {
        lastError_ = api().error(connection_);
        api().close(connection_);
        connection_ = nullptr;
        return false;
    }

    if (!createSchema())
    {
        api().close(connection_);
        connection_ = nullptr;
        return false;
    }

    return true;
}

bool Database::createSchema()
{
    const std::vector<std::string> statements = {
        "CREATE TABLE IF NOT EXISTS owners ("
        "id INT AUTO_INCREMENT PRIMARY KEY,"
        "name VARCHAR(100) NOT NULL,"
        "phone VARCHAR(30) NOT NULL,"
        "email VARCHAR(120) NOT NULL)",
        "CREATE TABLE IF NOT EXISTS pgs ("
        "id INT AUTO_INCREMENT PRIMARY KEY,"
        "name VARCHAR(120) NOT NULL,"
        "college VARCHAR(160) NOT NULL,"
        "location VARCHAR(160) NOT NULL,"
        "type VARCHAR(20) NOT NULL,"
        "rent INT NOT NULL,"
        "rating DECIMAL(2,1) NOT NULL,"
        "owner_id INT NOT NULL,"
        "FOREIGN KEY (owner_id) REFERENCES owners(id))",
        "CREATE TABLE IF NOT EXISTS rooms ("
        "id INT AUTO_INCREMENT PRIMARY KEY,"
        "pg_id INT NOT NULL,"
        "room_number INT NOT NULL,"
        "total_beds INT NOT NULL,"
        "FOREIGN KEY (pg_id) REFERENCES pgs(id))",
        "CREATE TABLE IF NOT EXISTS students ("
        "id INT AUTO_INCREMENT PRIMARY KEY,"
        "room_id INT NOT NULL,"
        "name VARCHAR(100) NOT NULL,"
        "phone VARCHAR(30) NOT NULL,"
        "course VARCHAR(80) NOT NULL,"
        "year INT NOT NULL,"
        "FOREIGN KEY (room_id) REFERENCES rooms(id))"
    };

    for (const std::string &sql : statements)
    {
        if (!query(sql))
        {
            return false;
        }
    }

    return true;
}

bool Database::savePg(const PG &pg)
{
    lastError_.clear();
    if (!isOpen())
    {
        lastError_ = "MySQL is not connected.";
        return false;
    }

    if (!query("START TRANSACTION"))
    {
        return false;
    }

    const Owner &owner = pg.getOwner();
    std::ostringstream ownerSql;
    ownerSql << "INSERT INTO owners (name, phone, email) VALUES ("
             << quoted(escape(owner.getName())) << ", "
             << quoted(escape(owner.getPhone())) << ", "
             << quoted(escape(owner.getEmail())) << ")";
    if (!query(ownerSql.str()))
    {
        query("ROLLBACK");
        return false;
    }
    const unsigned long long ownerId = api().insertId(connection_);

    std::ostringstream pgSql;
    pgSql << "INSERT INTO pgs (name, college, location, type, rent, rating, owner_id) VALUES ("
          << quoted(escape(pg.getPGName())) << ", "
          << quoted(escape(pg.getCollegeName())) << ", "
          << quoted(escape(pg.getLocation())) << ", "
          << quoted(escape(pg.getPGType())) << ", "
          << pg.getRent() << ", "
          << pg.getRating() << ", "
          << ownerId << ")";
    if (!query(pgSql.str()))
    {
        query("ROLLBACK");
        return false;
    }
    const unsigned long long pgId = api().insertId(connection_);

    for (const Room &room : pg.getRooms())
    {
        std::ostringstream roomSql;
        roomSql << "INSERT INTO rooms (pg_id, room_number, total_beds) VALUES ("
                << pgId << ", "
                << room.getRoomNumber() << ", "
                << room.getTotalBeds() << ")";
        if (!query(roomSql.str()))
        {
            query("ROLLBACK");
            return false;
        }
        const unsigned long long roomId = api().insertId(connection_);

        for (const Student &student : room.getStudents())
        {
            std::ostringstream studentSql;
            studentSql << "INSERT INTO students (room_id, name, phone, course, year) VALUES ("
                       << roomId << ", "
                       << quoted(escape(student.getName())) << ", "
                       << quoted(escape(student.getPhone())) << ", "
                       << quoted(escape(student.getCourse())) << ", "
                       << student.getYear() << ")";
            if (!query(studentSql.str()))
            {
                query("ROLLBACK");
                return false;
            }
        }
    }

    return query("COMMIT");
}

PG Database::loadPgById(long long pgId)
{
    std::ostringstream pgSql;
    pgSql << "SELECT p.name, p.college, p.location, p.type, p.rent, p.rating, "
             "o.name, o.phone, o.email "
             "FROM pgs p JOIN owners o ON o.id = p.owner_id WHERE p.id = "
          << pgId;

    if (!query(pgSql.str()))
    {
        return PG("", "", "", "", 0, 0.0f);
    }

    MysqlResult *pgResult = api().storeResult(connection_);
    MysqlRow pgRow = pgResult == nullptr ? nullptr : api().fetchRow(pgResult);
    if (pgRow == nullptr)
    {
        if (pgResult != nullptr)
        {
            api().freeResult(pgResult);
        }
        lastError_ = "MySQL did not return the requested PG listing.";
        return PG("", "", "", "", 0, 0.0f);
    }

    PG pg(
        cell(pgRow, 0),
        cell(pgRow, 1),
        cell(pgRow, 2),
        cell(pgRow, 3),
        std::stoi(cell(pgRow, 4)),
        std::stof(cell(pgRow, 5))
    );
    pg.setOwner(Owner(cell(pgRow, 6), cell(pgRow, 7), cell(pgRow, 8)));
    api().freeResult(pgResult);

    std::ostringstream roomSql;
    roomSql << "SELECT id, room_number, total_beds FROM rooms WHERE pg_id = "
            << pgId << " ORDER BY room_number";
    if (!query(roomSql.str()))
    {
        return pg;
    }

    MysqlResult *roomResult = api().storeResult(connection_);
    if (roomResult == nullptr)
    {
        lastError_ = "MySQL did not return room data for a PG listing.";
        return pg;
    }

    struct RoomRow
    {
        long long id;
        int number;
        int beds;
    };
    std::vector<RoomRow> rooms;
    while (roomResult != nullptr)
    {
        MysqlRow row = api().fetchRow(roomResult);
        if (row == nullptr)
        {
            break;
        }
        rooms.push_back({std::stoll(cell(row, 0)), std::stoi(cell(row, 1)), std::stoi(cell(row, 2))});
    }
    if (roomResult != nullptr)
    {
        api().freeResult(roomResult);
    }

    for (const RoomRow &roomRow : rooms)
    {
        Room room(roomRow.number, roomRow.beds);
        std::ostringstream studentSql;
        studentSql << "SELECT name, phone, course, year FROM students WHERE room_id = "
                   << roomRow.id << " ORDER BY id";
        if (!query(studentSql.str()))
        {
            pg.addRoom(room);
            continue;
        }

        MysqlResult *studentResult = api().storeResult(connection_);
        if (studentResult == nullptr)
        {
            lastError_ = "MySQL did not return student data for a room.";
            pg.addRoom(room);
            return pg;
        }

        while (studentResult != nullptr)
        {
            MysqlRow row = api().fetchRow(studentResult);
            if (row == nullptr)
            {
                break;
            }
            room.addStudent(Student(
                cell(row, 0),
                cell(row, 1),
                cell(row, 2),
                std::stoi(cell(row, 3))
            ));
        }
        if (studentResult != nullptr)
        {
            api().freeResult(studentResult);
        }
        pg.addRoom(room);
    }

    return pg;
}

std::vector<PG> Database::loadPgs()
{
    lastError_.clear();
    std::vector<PG> pgs;
    if (!isOpen())
    {
        lastError_ = "MySQL is not connected.";
        return pgs;
    }
    if (!query("SELECT id FROM pgs ORDER BY id"))
    {
        return pgs;
    }

    MysqlResult *result = api().storeResult(connection_);
    if (result == nullptr)
    {
        lastError_ = "MySQL did not return PG listing data.";
        return pgs;
    }
    std::vector<long long> ids;
    while (result != nullptr)
    {
        MysqlRow row = api().fetchRow(result);
        if (row == nullptr)
        {
            break;
        }
        ids.push_back(std::stoll(cell(row, 0)));
    }
    if (result != nullptr)
    {
        api().freeResult(result);
    }

    for (long long id : ids)
    {
        pgs.push_back(loadPgById(id));
    }
    return pgs;
}

bool Database::seedIfEmpty(const std::vector<PG> &samplePgs)
{
    lastError_.clear();
    if (!isOpen())
    {
        lastError_ = "MySQL is not connected.";
        return false;
    }
    if (!query("SELECT COUNT(*) FROM pgs"))
    {
        return false;
    }

    MysqlResult *result = api().storeResult(connection_);
    if (result == nullptr)
    {
        lastError_ = "MySQL did not return the PG listing count.";
        return false;
    }

    MysqlRow row = api().fetchRow(result);
    if (row == nullptr)
    {
        api().freeResult(result);
        lastError_ = "MySQL did not return the PG listing count.";
        return false;
    }

    const int count = std::stoi(cell(row, 0));
    api().freeResult(result);

    if (count > 0)
    {
        return true;
    }

    for (const PG &pg : samplePgs)
    {
        if (!savePg(pg))
        {
            return false;
        }
    }

    return true;
}
