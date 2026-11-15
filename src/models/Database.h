#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include "PG.h"

// Connects to MySQL and hides SQL from the rest of the app.
class Database
{
public:
    struct Settings
    {
        std::string host = "127.0.0.1";
        int port = 3306;
        std::string user = "root";
        std::string password;
        std::string database = "staynear";
    };

    Database();
    ~Database();

    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

    static std::string configPath();
    static Settings loadSettings();
    static void saveSettings(const Settings &settings);

    bool open(const Settings &settings);
    bool isOpen() const;
    const std::string &lastError() const;

    std::vector<PG> loadPgs();
    bool savePg(const PG &pg);
    bool seedIfEmpty(const std::vector<PG> &samplePgs);

private:
    bool loadClient();
    bool query(const std::string &sql);
    std::string escape(const std::string &value) const;
    bool createSchema();
    PG loadPgById(long long pgId);

    void *library_ = nullptr;
    void *connection_ = nullptr;
    std::string lastError_;
};

#endif
