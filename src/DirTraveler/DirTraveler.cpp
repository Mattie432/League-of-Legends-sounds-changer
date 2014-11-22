#include "DirTraveler.hpp"

using namespace std;
DirTraveler::DirTraveler()
{
    //ctor
}
DirTraveler::~DirTraveler()
{
    //dtor
}

bool DirTraveler::DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


bool dirExists2(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

vector<string> DirTraveler::travelDirectory(string directory)
{
    // travel thru a directory gathering all the file and directory naems
    vector<string> fileList;
    DIR *dir;
    struct dirent *ent;
    // open a directory
    if ((dir=opendir(directory.c_str())) != NULL)
    {
        while((ent=readdir(dir)) != NULL) // loop until the directory is traveled thru
        {
            // push directory or filename to the list
            fileList.push_back(ent->d_name);
        }
        // close up
        closedir(dir);
    }
    //return the filelust
    return fileList;
}
//return only folders
void DirTraveler::travelDirectoryRecursiveReturnFolders(string directory, vector<string> *fullList)
{
    // get the "root" directory's directories
    vector<string> fileList = travelDirectory(directory);

    // loop thru the list
    for (vector<string>::iterator i=fileList.begin(); i!=fileList.end(); ++i)
    {
        // test for . and .. directories (this and back)
        if (strcmp((*i).c_str(), ".") && strcmp((*i).c_str(), "..")){
            // i use stringstream here, not string = foo; string.append(bar);
            stringstream fullname;
            fullname << directory << "/" << (*i);
            string strFullname;
            strFullname = directory + "/" + (*i);
            //cout << "Fullname = " << strFullname << endl;
          if(dirExists2(strFullname)){
            fullList->push_back(fullname.str());
            travelDirectoryRecursiveReturnFolders(fullname.str(), fullList);
          }
        }
    }
}

//return folders and files
void DirTraveler::travelDirectoryRecursiveReturnFiles(string directory, vector<string> *fullList)
{
    // get the "root" directory's directories
    vector<string> fileList = travelDirectory(directory);
    // loop thru the list
    for (vector<string>::iterator i=fileList.begin(); i!=fileList.end(); ++i)
    {
        // test for . and .. directories (this and back)
        if (strcmp((*i).c_str(), ".") &&
            strcmp((*i).c_str(), ".."))
        {
            // i use stringstream here, not string = foo; string.append(bar);
            stringstream fullname;
            fullname << directory << "/" << (*i);
            fullList->push_back(fullname.str());
            travelDirectoryRecursiveReturnFiles(fullname.str(), fullList);
        }
    }
}
