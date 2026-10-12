@echo off
setlocal

if not defined QT_DIR set "QT_DIR=C:\Qt\6.11.1\mingw_64"
if exist "C:\Qt\Tools\CMake_64\bin" set "PATH=C:\Qt\Tools\CMake_64\bin;%PATH%"
if exist "C:\Qt\Tools\Ninja" set "PATH=C:\Qt\Tools\Ninja;%PATH%"
if exist "C:\Qt\Tools\mingw1310_64\bin" set "PATH=C:\Qt\Tools\mingw1310_64\bin;%PATH%"

cd /d "%~dp0"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="%QT_DIR%"
if errorlevel 1 (
    echo [ERROR] CMake configuration failed.
    exit /b 1
)

cmake --build build --config Release
if errorlevel 1 (
    echo [ERROR] Build failed.
    exit /b 1
)

echo Build successful.
echo Qt desktop app: build\StayNear.exe

endlocal
