# StayNear

StayNear is a beginner-friendly C++17 project for managing student paying-guest (PG) accommodation in Bhimtal. The desktop interface is built entirely with **native Qt 6 Widgets**. It does not use HTML, CSS, JavaScript, or a WebView.

## Features

- Browse example PGs near GEHU and BIAS.
- Search by PG, college, or location; filter by PG type, monthly rent, and bed availability.
- See total, occupied, and available bed counts.
- Register a PG with owner details and room capacities.
- Inspect rooms, occupancy, and resident student information.

The data is held in memory and resets when the app closes.

## Project layout

```text
StayNear/
├── CMakeLists.txt
├── README.md
├── build.bat
├── src/
│   ├── models/                 # Data classes and example data
│   │   ├── Person.h/.cpp       # Shared name and phone
│   │   ├── Student.h/.cpp      # Student details
│   │   ├── Owner.h/.cpp        # Owner details
│   │   ├── Room.h/.cpp         # Beds and students in a room
│   │   ├── PG.h/.cpp           # PG details and bed totals
│   │   └── SampleData.h/.cpp   # Example PGs
│   └── gui/                    # Qt windows and dialogs
│       ├── main.cpp            # Starts the app
│       ├── MainWindow.h/.cpp   # Main PG list and filters
│       └── dialogs/            # Add PG and view room details
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

PGs added while the app is running are kept in memory and are cleared when the app closes.
