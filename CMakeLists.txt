cmake_minimum_required(VERSION 3.16)

project(StayNear LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(StayNear
    src/gui/main.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/dialogs/AddPGDialog.cpp
    src/gui/dialogs/AddPGDialog.h
    src/gui/dialogs/PGDetailsDialog.cpp
    src/gui/dialogs/PGDetailsDialog.h
    src/models/Owner.cpp
    src/models/Owner.h
    src/models/Person.cpp
    src/models/Person.h
    src/models/PG.cpp
    src/models/PG.h
    src/models/Room.cpp
    src/models/Room.h
    src/models/SampleData.cpp
    src/models/SampleData.h
    src/models/Student.cpp
    src/models/Student.h
)

target_include_directories(StayNear PRIVATE src/models)
target_link_libraries(StayNear PRIVATE Qt6::Widgets)
