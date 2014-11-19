#ifndef FILEACTIONS_H
#define FILEACTIONS_H
#include <limits>
#include <shlobj.h>
#include <sys\stat.h>
#include <iostream>
#include <algorithm>
#include "../DirTraveler/DirTraveler.hpp"

using namespace std;

int CopyDirectory(const std::string &refcstrSourceDirectory,const std::string &refcstrDestinationDirectory);
int DeleteDirectory(const std::string &refcstrRootDirectory);
#endif // DIRTRAVELER_H
