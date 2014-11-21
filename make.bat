@echo off
echo Staring compiler
g++ src/Utilities/Utilities.cpp ^
src/DirTraveler/DirTraveler.cpp ^
src/FileActions/FileActions.cpp ^
src/Main.cpp ^
-o League_of_Legends_sound_changer.exe
echo:
SET Input=
SET /P Input="Start the compiled program? (y/n)"

IF /I %Input%==y start League_of_Legends_sound_changer.exe debug
exit
