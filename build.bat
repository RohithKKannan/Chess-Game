@echo off
setlocal EnableDelayedExpansion

set OUTPUT=main.exe

REM Clean previous build
if exist %OUTPUT% del %OUTPUT%

REM Gather all source files
set SOURCES=main.cpp

for %%f in (Board\*.cpp) do set SOURCES=!SOURCES! %%f
for %%f in (Pieces\*.cpp) do set SOURCES=!SOURCES! %%f
for %%f in (Utils\*.cpp) do set SOURCES=!SOURCES! %%f
for %%f in (CommandSystem\*.cpp) do set SOURCES=!SOURCES! %%f
for %%f in (Game\*.cpp) do set SOURCES=!SOURCES! %%f

REM Compile with include paths
g++ -std=c++17 -Wall -Wextra -O2 ^
-I. ^
-IBoard ^
-IPieces ^
-IUtils ^
-ICommandSystem ^
-IGame ^
-ICore ^
%SOURCES% -o %OUTPUT%

if %ERRORLEVEL% NEQ 0 (
    echo Build failed.
) else (
    echo Build successful! Run %OUTPUT%
)
pause
