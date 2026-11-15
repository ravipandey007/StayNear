# StayNear

StayNear is a beginner-friendly C++17 project for managing student paying-guest (PG) accommodation in Bhimtal. The desktop interface is built entirely with **native Qt 6 Widgets**. It does not use HTML, CSS, JavaScript, or a WebView.

## Features

- Browse example PGs near GEHU and BIAS.
- Search by PG, college, or location; filter by PG type, monthly rent, and bed availability.
- See total, occupied, and available bed counts.
- Register a PG with owner details and room capacities.
- Inspect rooms, occupancy, and resident student information.

PG listings and their owners, rooms, and students are stored in MySQL so they
remain available after the app closes. If MySQL is unavailable, the app warns
you and uses temporary sample data for that session.

## Project layout

```text
StayNear/
├── CMakeLists.txt
├── README.md
├── build.bat
├── database.ini.example     # Example local MySQL settings
├── sql/schema.sql           # MySQL schema (also created automatically)
├── src/
│   ├── models/                 # Data classes, sample data, and MySQL access
│   │   ├── Person.h/.cpp       # Shared name and phone
│   │   ├── Student.h/.cpp      # Student details
│   │   ├── Owner.h/.cpp        # Owner details
│   │   ├── Room.h/.cpp         # Beds and students in a room
│   │   ├── PG.h/.cpp           # PG details and bed totals
│   │   ├── SampleData.h/.cpp   # Example PGs
│   │   └── Database.h/.cpp     # MySQL connection and queries
│   └── gui/                    # Qt windows and dialogs
│       ├── main.cpp            # Starts the app
│       ├── MainWindow.h/.cpp   # Main PG list and filters
│       └── dialogs/            # Add PG, MySQL login, and room details
```

In VS Code, expand `src` to see the separate `gui` and `models` folders. The registration and room details forms are inside `src/gui/dialogs`. The Explorer keeps folders separate and hides generated build files automatically.

## Build the Qt desktop app

Install Qt 6 with the **Widgets** component, CMake, Ninja, and a compatible C++ compiler. Open a terminal in the project folder and configure CMake with the path to your Qt installation:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:\Qt\6.11.1\mingw_64" -DCMAKE_BUILD_TYPE=Release
cmake --build build
$env:Path = "C:\Qt\6.11.1\mingw_64\bin;$env:Path"
.\build\StayNear.exe
```

Use the Qt version and compiler kit installed on your computer. On Windows, Qt and the compiler used by CMake must come from compatible kits. Alternatively, run `build.bat`; set the `QT_DIR` environment variable first if Qt is installed somewhere other than `C:\Qt\6.11.1\mingw_64`.

## Four pillars of OOP

- **Encapsulation:** `Person`, `Room`, and `PG` keep their data private and provide public functions to read or update it.
- **Abstraction:** `PG::getAvailableBedsCount()` gives the total without making the window calculate each room's beds itself.
- **Inheritance:** `Student` and `Owner` are both kinds of `Person`; they reuse the person's name and phone.
- **Polymorphism:** the details window calls `getRole()` through a `Person` reference. C++ chooses `"Student"` or `"PG Owner"` depending on the actual object.

The basic example is in `src/models/Person.h`, `Student.h`, and `Owner.h`. In `PGDetailsDialog.cpp`, `describePerson()` shows polymorphism in use.

## Build and run

Install Qt 6 Widgets, CMake, Ninja, and a compatible C++ compiler. On Windows, open a terminal in the project folder and run:

```powershell
.\build.bat
.\build\StayNear.exe
```

If Qt is not installed in `C:\Qt\6.11.1\mingw_64`, set the `QT_DIR` environment variable to your Qt folder before running `build.bat`.

## MySQL setup

1. Install and start MySQL Server (8.0 or later). On Windows, StayNear also
   needs `libmysql.dll`, which is included with the MySQL Server installation.
2. Optionally copy `database.ini.example` to `database.ini` and enter your
   connection settings. Otherwise, StayNear asks for them when it starts.
3. On the first successful connection, StayNear creates the selected database
   and its tables, then seeds the example PGs only if there are no listings yet.

The app saves connection settings, including the password, in the local
`database.ini` file. That file is ignored by Git; keep it private. If MySQL is
unavailable or the login dialog is cancelled, StayNear continues with temporary
sample data. PGs registered in that offline session are not persisted.
