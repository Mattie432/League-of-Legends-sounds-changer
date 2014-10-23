#include <iostream>
#include <stdlib.h>
#include <limits>
#include <shlobj.h>
#include <windows.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "DirTraveler.cpp"
#include <list>
#define _OPEN_SYS
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>     //for using the function sleep
#include <string>
#include <windows.h>
#include <conio.h>
#undef _OPEN_SYS
#include <stdio.h>
#define chunk (5*1024)

using namespace std;

string* currentLangSelection(string);
string getFolder();
void cls();
string BrowseFolder();
void SearchFolder( TCHAR * );
void changeChampSelectSounds();
void changeGameCharacter();
void downloadFiles();
void pause();
int soundSelection();
void processTransfer();
void copy_folder(char, char);
void traverse(char, int);

//global vars
string leaguePath;
string currentLangName;
string currentLangCode;
string desiredLangName;
string desiredLangCode;
//TODO wukong may be monkeyking?
string champions[] = {
  "Aatrox",
  "Ahri",
  "Akali",
  "Alistar",
  "Amumu",
  "Anivia",
  "Annie",
  "Ashe",
  "Azir",
  "Blitzcrank",
  "Brand",
  "Braum",
  "Caitlyn",
  "Cassiopeia",
  "ChoGath",
  "Corki",
  "Darius",
  "Diana",
  "DrMundo",
  "Draven",
  "Elise",
  "Evelynn",
  "Ezreal",
  "Fiddlesticks",
  "Fiora",
  "Fizz",
  "Galio",
  "Gangplank",
  "Garen",
  "Gnar",
  "Gragas",
  "Graves",
  "Hecarim",
  "Heimerdinger",
  "Irelia",
  "Janna",
  "JarvanIV",
  "Vi",
  "Jax",
  "Jayce",
  "Jinx",
  "Karma",
  "Karthus",
  "Kassadin",
  "Katarina",
  "Kayle",
  "Kennen",
  "KhaZix",
  "KogMaw",
  "LeBlanc",
  "LeeSin",
  "Leona",
  "Lissandra",
  "Lucian",
  "Lulu",
  "Lux",
  "Malphite",
  "Malzahar",
  "Maokai",
  "MasterYi",
  "MissFortune",
  "Mordekaiser",
  "Morgana",
  "Nami",
  "Nasus",
  "Nautilus",
  "Nidalee",
  "Nocturne",
  "Nunu",
  "Olaf",
  "Orianna",
  "Pantheon",
  "Poppy",
  "Quinn",
  "Rammus",
  "Renekton",
  "Rengar",
  "Riven",
  "Rumble",
  "Ryze",
  "Sejuani",
  "Shaco",
  "Shen",
  "Shyvana",
  "Singed",
  "Sion",
  "Sivir",
  "Skarner",
  "Sona",
  "Soraka",
  "Swain",
  "Syndra",
  "Talon",
  "Taric",
  "Teemo",
  "Thresh",
  "Tristana",
  "Trundle",
  "Tryndamere",
  "TwistedFate",
  "Twitch",
  "Udyr",
  "Urgot",
  "Varus",
  "Vayne",
  "Veigar",
  "VelKoz",
  "Vi",
  "Viktor",
  "Vladimir",
  "Volibear",
  "Warwick",
  "Wukong",
  "Xerath",
  "XinZhao",
  "Yasuo",
  "Yorick",
  "Zac",
  "Zed",
  "Ziggs",
  "Zilean",
  "Zyra"
};
int soundInt;

bool dirExists(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}




void processTransfer(){
  if(soundInt >= 4){
    //need to do announcer sounds
    soundInt = soundInt - 4;
  }

  if(soundInt >= 2){
    //need to do in game character sounds
    changeGameCharacter();
    soundInt = soundInt - 2;
  }

  if(soundInt >= 1){
    //need to do champ select character sounds
    changeChampSelectSounds();
    soundInt = soundInt - 1;
  }

}

int CopyDirectory(const std::string &refcstrSourceDirectory,
                  const std::string &refcstrDestinationDirectory)
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

int DeleteDirectory(const std::string &refcstrRootDirectory,
                    bool              bDeleteSubdirectories = true)
{
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
            int iRC = DeleteDirectory(strFilePath, bDeleteSubdirectories);
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

int copy(string src, string dst)
{
  SHFILEOPSTRUCTA sf;
  int result;

  string source = src;
  string dest = dst;

  sf.pFrom = source.c_str( );
  sf.pTo = dest.c_str( );
  sf.wFunc = FO_MOVE;
  sf.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_SILENT;

  cout << endl << "Copying" << endl;
  cout << "Source : " << source << endl;
  cout << "Dest   : " << dest << endl;

  result = SHFileOperationA(&sf);
  cout << "Result: " << result << endl << endl;
  return result;
}


void changeGameCharacter()
{
  string currentClientFolder = leaguePath + "\\RADS\\projects\\lol_game_client_" + currentLangCode ;
  string desiredClientFolder = leaguePath + "\\RADS\\projects\\lol_game_client_" + desiredLangCode ;

  cout << "Folder 1 " << currentClientFolder << endl;
  cout << "Folder 2 " << desiredClientFolder << endl;

  if(dirExists(currentClientFolder)){
    if(dirExists(desiredClientFolder)){
      //both folders exist;
      int numOfChamps = sizeof( champions ) / sizeof( champions[ 0 ] );
      cout << "Size of champ array is " << numOfChamps << endl;


      DirTraveler traveler;
      //Array of fodlers in current folder
      vector<string> foo;
      traveler.travelDirectoryRecursiveReturnFolders(currentClientFolder,&foo);
      for (int i=2; i<foo.size(); ++i){
        string folder = foo[i].c_str();
        cout << "Checking folder : " << folder << endl;

        //Check if its a champion folder
        for (int i=0; i<numOfChamps; i++){
          string name = champions[i];
          if(folder.find(name) != std::string::npos){
            //if found exit loop
            i = numOfChamps;
            cout << "Found champ folder for " << name << endl;
            string folderPath = folder.substr(0,folder.find(name)) + name;
            cout << "At path : " << folderPath << endl << endl;

            

          }

        }
      }

      //END both folders exist;
    }else {
      cout << "Could not find desired language folder : " << desiredClientFolder << endl;
      pause();
    }
  }else{
    cout << "Could not find current language folder : " << currentClientFolder << endl;
    pause();

  }

}

void changeChampSelectSounds()
{
  string str = leaguePath + "\\RADS\\projects\\lol_air_client\\releases";
  cout << str << endl;
  DirTraveler traveler;
  vector<string>foo;
  foo = traveler.travelDirectory(str);
  for (int i=2; i<foo.size(); ++i){
      string folder = foo[i].c_str();
      //cout << folder << endl;

      string newPath = str + "\\" + folder + "\\deploy\\assets\\sounds\\";
      //cout << "new path = " << newPath << endl;
      BOOL ansCurrentLang = DirectoryExists((newPath + currentLangCode).c_str());
      BOOL ansDesiredLang = DirectoryExists((newPath + desiredLangCode).c_str());

      cout << "Currently changing the announcer sounds to " << desiredLangName << endl;

      if(ansCurrentLang == 1 && DirectoryExists((newPath + currentLangCode + "_BACKUP").c_str()) != 1){
        cout << "Creating a backup of " << currentLangCode << " file." << endl;
        //folders found
          // If backup not exist, backup.
          copy(newPath + currentLangCode, newPath + currentLangCode + "_BACKUP");
      }else{

          cout << "Backup of " << currentLangCode << " already exists." << endl;
      }

      if(ansDesiredLang == 1){
        //copy((newPath + desiredLangCode), (newPath + currentLangCode));;
        cout << "Copying " << desiredLangCode << " to " << currentLangCode << "." << endl;

        int del = DeleteDirectory(newPath + currentLangCode);
        if(del != 0){
          cout << "Error deleting " << currentLangCode << ", code: " << del << endl;
        }
        Sleep(2000);
        int cpy = copy(newPath + desiredLangCode, newPath + currentLangCode);
        if(cpy != 0){
          cout << "Error copying " << desiredLangCode << ", code: " << del << endl;
        }else{
          cout << "Copy complete" << endl;
        }
        cout << "Finished changing the champion select sounds." << endl << endl;
        cout <<  "--------------------------------------------------------------------------------" << endl;
      }else{
        cout << "ERROR: could not find folders;" << endl;
        cout << newPath + currentLangCode << endl;
        cout << newPath + desiredLangCode << endl;
        pause();
      }
  }

}

void traverse(char *fn, int indent) {
  DIR *dir;
  struct dirent *entry;
  int count;
  char path[1025];
  struct stat info;

  for (count=0; count<indent; count++) printf("  ");
  printf("%s\n", fn);

  if ((dir = opendir(fn)) == NULL)
    perror("opendir() error");
  else {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_name[0] != '.') {
        strcpy(path, fn);
        strcat(path, "/");
        strcat(path, entry->d_name);
        if (stat(path, &info) != 0)
          fprintf(stderr, "stat() error on %s: %s\n", path,
                  strerror(errno));
        else if (S_ISDIR(info.st_mode))
               traverse(path, indent+1);
      }
    }
    closedir(dir);
  }
}


int soundSelection()
{

  string sounds[3] = {
    "Champion select character sounds",
    "In Game character sounds",
    "Announcer sounds"
  };

  cout <<  "--------------------------------------------------------------------------------" << endl;
  cout << "Choose which sounds to change." << endl;
  cout << endl;
  cout << "1. " << sounds[0] << endl;
  cout << "2. " << sounds[1] << endl;
  cout << "4. " << sounds[2] << endl;
  cout << endl;
  cout << "To make your selection enter the sum of the sounds you wish to install." << endl;
  cout << "e.g. to install ALL sounds enter '7' (as 1 + 2 + 4 = 7)." << endl;
  cout <<endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << endl;



  int number;
  while ((cout << "Please enter a number ")
         && (!(cin >> number) || number < 1 || number > 7)) {
    cout << "That's not a valid input. " << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cout << endl << "You chose " << number << endl;

  char answer;
  while ((cout << "Is this correct? (y/n) ")
         && (!(cin >> answer) || answer != 'y' && answer != 'n')) {
    cout << "That's not a valid input. " << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  if(answer == 'n'){
    //  need to re-ask for language selection.
    cls();
    return soundSelection();
  }else{
    return number;
  }

  return 0;
}

void downloadFiles()
{
  cout <<  "--------------------------------------------------------------------------------" << endl;
  cout << "1: Go to " << leaguePath << "\\Rads\\system\\" << " and open up 'locale.cfg'" << endl;
  cout << endl;
  cout << "2: Paste 'locale=" << desiredLangCode << "' into the document (without the quotes) overwriting the" << endl;
  cout << "   existing text." << endl;
  cout << "   NOTE: Keep a record of what the origional text was as you will need to" << endl;
  cout << "   replace it later." << endl;
  cout << endl;
  cout << "3: Open up the league of legends launcher and let the client download the new" << endl;
  cout << "   files. This will download the korean versions of the files needed. Once" << endl;
  cout << "   completed you should have two folders in the" << endl;
  cout << "   '" << leaguePath << "\\RADS\\projects\\'" << endl;
  cout << "   folder, 'lol_game_client_" << desiredLangCode << "' and 'lol_game_client_" << currentLangCode << "'." << endl;
  cout << endl;
  cout << "4: Once League of Legends has downloaded the alternate version close the League" << endl;
  cout << "   window and re-open " << leaguePath << "\\system\\locale.cfg and" << endl;
  cout << "   replace the text with what it was origionally ('locale=" << currentLangCode << "')."  << endl;
  cout << endl;
  cout <<  "--------------------------------------------------------------------------------" << endl;
  pause();

  //e.g. ko_KR
  string desiredPath = leaguePath + "\\RADS\\projects\\lol_game_client_" + desiredLangCode;
  string currentPath = leaguePath + "\\RADS\\projects\\lol_game_client_" + currentLangCode;

    if (!dirExists(desiredPath)){
      // remote path dosent exist
      cout << "ERROR: Count not find path:" << endl;
      cout << desiredPath << endl << endl;
      cout << "Please check you entered the correct path and try again." << endl << endl;
      pause();
      exit(1);
    }
}


//Gets the location of the league folder
string getFolder()
{
  cout <<  "--------------------------------------------------------------------------------" << endl;
  cout << "Please enter the location of the 'League of Legends' folder." << endl;
  cout << endl;
  cout <<  "--------------------------------------------------------------------------------" << endl;
  return BrowseFolder();
}

void pause()
{
  // cout << endl << "Press any key to continue...";
  // getchar();
  system("pause");
}

//BROWSE FOLDER - Opens a browse folder dialog.
string BrowseFolder()
{
    TCHAR path[MAX_PATH];
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = ("All Folders Automatically Recursed.");
    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
    string path_;
    if ( pidl != 0 )
    {

        // get the name of the folder and put it in path
        SHGetPathFromIDList ( pidl, path );
        //Set the current directory to path
        SetCurrentDirectory ( path );

        path_ = path;

        //     //Begin the search
        //     SearchFolder( path );

        // free memory used
        IMalloc * imalloc = 0;
        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
        {
            imalloc->Free ( pidl );
            imalloc->Release ( );
        }
        return path;
  }
  return path_;
}


//SEARCH FOLDER - Searches folder and all sub-folders,
//reading every file it comes across.
void SearchFolder( TCHAR * path )
{
    //Declare all needed handles
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    TCHAR filename[ MAX_PATH + 256 ];
    TCHAR pathbak[ MAX_PATH ];

    //Make a backup of the directory the user chose
    strcpy( pathbak, path );

    //Find the first file in the directory the user chose
    hFind = FindFirstFile ( "*.*", &FindFileData );

    //Use a do/while so we process whatever FindFirstFile returned
    do
    {
        //Is it valid?
        if ( hFind != INVALID_HANDLE_VALUE )
        {
            //Is it a . or .. directory? If it is, skip, or we'll go forever.
            if ( ! ( strcmp( FindFileData.cFileName, "." ) ) ||
                ! ( strcmp( FindFileData.cFileName, ".." ) ) )
            {
                continue;
            }
            //Restore the original directory chosen by the user
            strcpy( path, pathbak );

            //Append the file found on to the path of the
            //directory the user chose
            sprintf( path, "%s\\%s", path, FindFileData.cFileName );

            //If SetCurrentDirectory Succeeds ( returns 1 ) the
            //current file is a directory. Pause this function,
            //and have it call itself. This will begin the whole
            //process over in a sub directory.
            if ( ( SetCurrentDirectory( path ) ) )
            {
                SearchFolder( path );
            }

            //Otherwise right here is where you need to
            //insert what you want to do.
            //As an example let's add the filename to a list box.
            //INSERT WHAT YOU WANT DONE BELOW!
            //SendMessage( m_listbox_hwnd, LB_ADDSTRING, 0, path );
            cout << path << endl;
        }
    }
    while ( FindNextFile ( hFind, &FindFileData )
        && hFind != INVALID_HANDLE_VALUE );
    FindClose ( hFind );
}//SEARCH FOLDER





// returns array with first element the string name of the language
// and the second is the code ascociate with it.
//
// Parameter = "current" or "desired"
string* currentLangSelection(string currentOrdesired){
  string languagesName[] = {
  "English (US)",
  "English (GB)",
  "Korean",
  "German",
  "Italian",
  "Polish",
  "French",
  "Romanian",
  "Greek",
  "Brazilian/Portugese",
  "Spanish",
  "Chinese"
  };
  string languagesCode[] = {
    "en_US",
    "en_GB",
    "ko_KR",
    "de_DE",
    "it_IT",
    "pl_PL",
    "fr_FR",
    "ro_RO",
    "el_GR",
    "pt_BR",
    "es_ES",
    "zh_CN"
    };

  int languagesNameSize = sizeof(languagesName)/sizeof(languagesName[0]); //Get the array size


  cout <<  "--------------------------------------------------------------------------------" << endl;
  cout <<  "Please select your " << currentOrdesired <<" language." << endl;
  cout << endl;

  for (int i = 0; i < languagesNameSize; i++){
    if(i < 9){
      //Just for neatness
      cout << " ";
    }
    cout << i+1 << ". " <<languagesName[i] << endl;
  }

  cout << endl;
  cout <<  "--------------------------------------------------------------------------------" << endl;
  cout << endl;

  int number;
  while ((cout << "Please enter a number ")
         && (!(cin >> number) || number < 1 || number > languagesNameSize)) {
    cout << "That's not a valid input. " << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cout << endl << "You selected " << languagesName[number-1] << " as your " << currentOrdesired <<" language." << endl;

  char answer;
  while ((cout << "Is this correct? (y/n) ")
         && (!(cin >> answer) || answer != 'y' && answer != 'n')) {
    cout << "That's not a valid input. " << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  if(answer == 'n'){
    //  need to re-ask for language selection.
    cls();
    return currentLangSelection(currentOrdesired);
  }else{
    static string returnValue[2];
    returnValue[0] = languagesName[number-1];
    returnValue[1] = languagesCode[number-1];
    return returnValue;
  }
}

// clears the shell
void cls(){
  system("cls");
}


int main()
{
    string *currentLang = currentLangSelection("CURRENT");
    currentLangName = currentLang[0];
    currentLangCode = currentLang[1];
    cls();
    string *desiredLang = currentLangSelection("DESIRED");
    desiredLangName = desiredLang[0];
    desiredLangCode = desiredLang[1];
    cls();
    leaguePath = getFolder();
    cls();
    downloadFiles();
    cls();
    soundInt = soundSelection();
    cls();
    processTransfer();
    pause();
    return 0;
}
