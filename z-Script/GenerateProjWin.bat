@echo off
pushd %~dp0\..\
call Dependencies\Binary\Premake\premake5.exe vs2019
popd
PAUSE