cmake_minimum_required(VERSION 3.16)

project(StayNear VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Core C++ Sources
# -----------------------------------------------------------------------------
set(CORE_SOURCES
    Person.h
    Person.cpp
    Student.h
    Student.cpp
    Owner.h
    Owner.cpp
    Room.h
    Room.cpp
    PG.h
    PG.cpp
)

# -----------------------------------------------------------------------------
# Target 1: Modular CLI Executable
# -----------------------------------------------------------------------------
add_executable(StayNear_CLI
    ${CORE_SOURCES}
    main.cpp
)

# -----------------------------------------------------------------------------
# Target 2: Standalone Single-File Executable
# -----------------------------------------------------------------------------
add_executable(StayNear_Simple
    StayNear_Simple.cpp
)
