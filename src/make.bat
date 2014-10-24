@echo off
g++ basic.cpp -o basic.exe
echo:
SET Input=
SET /P Input="Start the compiled program? (y/n)"

IF /I %Input%==y start basic.exe debug
exit
