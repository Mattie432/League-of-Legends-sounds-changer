#ifndef DIRTRAVELER_H
#define DIRTRAVELER_H
#include <string>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
using namespace std;
class DirTraveler
{
    public:
        DirTraveler();
        virtual ~DirTraveler();
        vector<string> travelDirectory(string directory);
        void travelDirectoryRecursiveReturnFolders(string directory, vector<string> *fullList);
        void travelDirectoryRecursiveReturnFiles(string directory, vector<string> *fullList);
        bool DirectoryExists(LPCTSTR szPath);
    protected:
    private:
};
#endif // DIRTRAVELER_H
