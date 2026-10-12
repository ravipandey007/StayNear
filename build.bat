@echo off
setlocal

echo =======================================================
echo   Building StayNear (Modular & Standalone Targets)
echo =======================================================

set "CMAKE_BIN=C:\Qt\Tools\CMake_64\bin\cmake.exe"
set "NINJA_DIR=C:\Qt\Tools\Ninja"
set "MINGW_DIR=C:\Qt\Tools\mingw1310_64\bin"

set "PATH=%MINGW_DIR%;%NINJA_DIR%;%PATH%"

if not exist build mkdir build
cd build

echo Configuring with CMake...
"%CMAKE_BIN%" -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
if errorlevel 1 (
    echo [ERROR] CMake configuration failed.
    exit /b 1
)

echo Building executables with Ninja...
"%CMAKE_BIN%" --build . --config Release
if errorlevel 1 (
    echo [ERROR] Build failed.
    exit /b 1
)

echo =======================================================
echo   Build Successful!
echo   Modular CLI:     build\StayNear_CLI.exe
echo   Standalone:      build\StayNear_Simple.exe
echo =======================================================

endlocal
