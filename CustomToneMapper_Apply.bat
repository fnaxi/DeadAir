@echo off



cd /d "%~dp0"

set "REG_KEY=HKLM\SOFTWARE\EpicGames\Unreal Engine\5.6"
set "REG_VALUE=InstalledDirectory"

for /f "tokens=2*" %%A in ('reg query "%REG_KEY%" /v "%REG_VALUE%" 2^>nul') do (
	set "UE_PATH=%%B"
)

if not defined UE_PATH (
	echo Could not find Unreal Engine 5.6 installation path!
	pause
	exit /b
)
echo Found UE5.6 installation at: %UE_PATH%

set "TARGET_DIR=%UE_PATH%\Engine\Shaders\Private"
set "TARGET_NAME=PostProcessCombineLUTs.usf"
set "TARGET_FILE=%TARGET_DIR%\%TARGET_NAME%"

if not exist %TARGET_NAME% (
	echo Can't find '%TARGET_NAME%' in current directory!
	pause
	exit /b
)

copy /y "%TARGET_NAME%" "%TARGET_DIR%"

if %errorLevel% == 0 (
	echo Custom tonemapper was successfully applied to UE5.6!
) else (
	echo Failed to copy the file! Check folder permissions.
	pause
)
