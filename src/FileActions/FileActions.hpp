#ifndef FILEACTIONS_H
#define FILEACTIONS_H
#include <limits>
#include <shlobj.h>
#include <sys\stat.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <algorithm>
#include "../DirTraveler/DirTraveler.hpp"

using namespace std;

int CopyDirectory(const std::string &refcstrSourceDirectory,const std::string &refcstrDestinationDirectory);
int DeleteDirectory(const std::string &refcstrRootDirectory);
int ReplaceDirectory(const std::string &replace, const std::string &with);
int copyFile(string source, string destination);
int deleteFile(string strSource);
void replaceFile(string source, string destination);
#endif // DIRTRAVELER_H
