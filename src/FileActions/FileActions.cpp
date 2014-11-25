#include "FileActions.hpp"
#include "../Utilities/Utilities.hpp"

using namespace std;


int CopyDirectory(const std::string &refcstrSourceDirectory, const std::string &refcstrDestinationDirectory)
{
  std::string     strSource;               // Source file
  std::string     strDestination;          // Destination file
  std::string     strPattern;              // Pattern
  HANDLE          hFile;                   // Handle to file
  WIN32_FIND_DATA FileInformation;         // File information


  strPattern = refcstrSourceDirectory + "\\*.*";

  // Create destination directory
  if(::CreateDirectory(refcstrDestinationDirectory.c_str(), 0) == FALSE)
    return ::GetLastError();

  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if(hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if(FileInformation.cFileName[0] != '.')
      {
        strSource.erase();
        strDestination.erase();

        strSource      = refcstrSourceDirectory + "\\" + FileInformation.cFileName;
        strDestination = refcstrDestinationDirectory + "\\" + FileInformation.cFileName;

        if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          // Copy subdirectory
          if(CopyDirectory(strSource, strDestination))
            return 0;
        }
        else
        {
          // Copy file
          if(::CopyFile(strSource.c_str(), strDestination.c_str(), TRUE) == FALSE)
            return ::GetLastError();
        }
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

    // Close handle
    ::FindClose(hFile);

    DWORD dwError = ::GetLastError();
    if(dwError != ERROR_NO_MORE_FILES)
      return dwError;
  }

  return 0;
}


int DeleteDirectory(const std::string &refcstrRootDirectory)
{
  bool bDeleteSubdirectories = true;
  bool            bSubdirectory = false;       // Flag, indicating whether
                                               // subdirectories have been found
  HANDLE          hFile;                       // Handle to directory
  std::string     strFilePath;                 // Filepath
  std::string     strPattern;                  // Pattern
  WIN32_FIND_DATA FileInformation;             // File information


  strPattern = refcstrRootDirectory + "\\*.*";
  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if(hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if(FileInformation.cFileName[0] != '.')
      {
        strFilePath.erase();
        strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

        if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          if(bDeleteSubdirectories)
          {
            // Delete subdirectory
            int iRC = DeleteDirectory(strFilePath);
            if(iRC)
              return iRC;
          }
          else
            bSubdirectory = true;
        }
        else
        {
          // Set file attributes
          if(::SetFileAttributes(strFilePath.c_str(),
                                 FILE_ATTRIBUTE_NORMAL) == FALSE)
            return ::GetLastError();

          // Delete file
          if(::DeleteFile(strFilePath.c_str()) == FALSE)
            return ::GetLastError();
        }
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

    // Close handle
    ::FindClose(hFile);

    DWORD dwError = ::GetLastError();
    if(dwError != ERROR_NO_MORE_FILES)
      return dwError;
    else
    {
      if(!bSubdirectory)
      {
        // Set directory attributes
        if(::SetFileAttributes(refcstrRootDirectory.c_str(),
                               FILE_ATTRIBUTE_NORMAL) == FALSE)
          return ::GetLastError();

        // Delete directory
        if(::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
          return ::GetLastError();
      }
    }
  }

  return 0;
}

int ReplaceDirectory(const std::string &dirToReplace, const std::string &dirToReplaceWith)
{
    cout << "Copying  " << dirToReplaceWith << endl << "      to " << dirToReplace << endl;
  if(dirToReplace != "" & dirToReplaceWith != "" & dirToReplace != "null" & dirToReplaceWith != "null"){

    cout << "Deleting " << dirToReplace << endl;
    int del = DeleteDirectory(dirToReplace);

    if(del != 0){
      cout << "Error deleting " << dirToReplace << endl << "code: " << del << endl << endl;
      pause();
    }
    mySleep(1000);
    int cpy = CopyDirectory(dirToReplaceWith, dirToReplace);
    if(cpy != 0){
      cout << "Error copying " << dirToReplaceWith << endl << "code: " << cpy << endl << endl;
      pause();
    }else{
      cout << "Copy complete" << endl << "Code = " << cpy << endl << endl;
    }
  }else{
    cout << "Error! Null input!" << endl;
    pause();
  }
}

int copyFile(string strSource, string strDestination){
    return CopyFile(strSource.c_str(), strDestination.c_str(), TRUE);
}

int deleteFile(string strSource){
    return DeleteFile(strSource.c_str());
}


void replaceFile(string strSource, string strDestination){
    int del = deleteFile(strDestination);
    if(del != 0){
      cout << "Error deleting " << strDestination << ", code: " << del << endl;
      pause();
    }
    int cpy = copyFile(strSource, strDestination);
    if(cpy != 0){
      cout << "Error copying " << strSource << ", code: " << cpy << endl;
      pause();
    }else{
      cout << "Copy complete" << endl << "Code = " << cpy <<endl;
    }
}
