
@echo off
set PROJECT_DIR=%~dp0

if not defined BUILD_TYPE set BUILD_TYPE=Release
echo Build type: %BUILD_TYPE%

set BUILD_DIR=%PROJECT_DIR%\build
set SOURCE_DIR=%PROJECT_DIR%\

set CMAKE_CXX_FLAGS="/W4 /WX /EHsc"

@echo on
cmake -G"Visual Studio 16 2019"                 ^
-B"%BUILD_DIR%\%BUILD_TYPE%" -H"%SOURCE_DIR%"   ^
-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                 ^
-DCMAKE_CXX_FLAGS=%CMAKE_CXX_FLAGS%

cmake --build "%BUILD_DIR%\%BUILD_TYPE%" -- /property:configuration=%BUILD_TYPE%
