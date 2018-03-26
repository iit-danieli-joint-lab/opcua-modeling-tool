set /p fullversion=<version.txt

FOR /f "tokens=1,2 delims=," %%a IN ("%fullversion%") DO (
	set version=%%a
	set build=%%b
	set /a build+=1
)

echo Version:%version%
echo Build:%build%

REM Update version.txt
echo %version%,%build% > version.txt

REM Update version.ini
echo [UMX] > version.ini
echo Version=%version% >> version.ini
echo Build=%build% >> version.ini
