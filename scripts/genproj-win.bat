@echo off
pushd %~dp0\..\
call .\vendor\Windows-bin\premake\premake5.exe vs2019
popd
PAUSE
