set CONFIG=%~1
set PLATFORM=%2
set PROJECT=%3
set ACTION=Build
if %PLATFORM% == x64 (set MACHINE=x64) else (set MACHINE=x86)
call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat" %MACHINE%

devenv /nologo SndVol.sln /Project %PROJECT% /%ACTION% "%CONFIG%|%PLATFORM%"

if %ERRORLEVEL% neq 0 (
@echo %~1 %2 %3 failed
pause
exit
)