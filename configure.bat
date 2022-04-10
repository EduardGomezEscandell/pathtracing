
@echo off
set PROJECT_DIR=%~dp0

if not defined BUILD_TYPE set BUILD_TYPE=Release
echo Build type: %BUILD_TYPE%

set BUILD_DIR=%PROJECT_DIR%\build
set BIN_DIR=%PROJECT_DIR%\bin\%BUILD_TYPE%
set SOURCE_DIR=%PROJECT_DIR%\

:: /EHsc necessary to compile with /W4
:: /Wv:18 disables a warning in Eigen
set CMAKE_CXX_FLAGS="/EHsc /Wv:18"

:: Building
@echo on
cmake -G"Visual Studio 16 2019"                 ^
-B"%BUILD_DIR%\%BUILD_TYPE%" -H"%SOURCE_DIR%"   ^
-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                 ^
-DCMAKE_CXX_FLAGS=%CMAKE_CXX_FLAGS%

cmake --build "%BUILD_DIR%\%BUILD_TYPE%" -- /property:configuration=%BUILD_TYPE%

:: Creating links in bin
@echo off
rd /s /q "%BIN_DIR%"
mkdir "%BIN_DIR%"
mklink "%BIN_DIR%\run_tests.exe" "%BUILD_DIR%\%BUILD_TYPE%\test\%BUILD_TYPE%\run_tests.exe"
mklink "%BIN_DIR%\pathtracer.exe" "%BUILD_DIR%\%BUILD_TYPE%\src\%BUILD_TYPE%\pathtracer.exe"