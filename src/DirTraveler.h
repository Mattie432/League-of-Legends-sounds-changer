#ifndef DIRTRAVELER_H
#define DIRTRAVELER_H
#include <string>
#include <vector>
using namespace std;
/// Directory traveler (mostly used with zgui manager)
class DirTraveler
{
    public:
        DirTraveler();
        virtual ~DirTraveler();
        vector<string> travelDirectory(string directory);
        void travelDirectoryRecursiveReturnFolders(string directory, vector<string> *fullList);
        void travelDirectoryRecursiveReturnFiles(string directory, vector<string> *fullList);
    protected:
    private:
};
#endif // DIRTRAVELER_H
