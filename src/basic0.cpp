#include <iostream>
#include <stdlib.h>
#include <limits>
#include <shlobj.h>
#include <windows.h>
#include <string.h>
using namespace std;

string* currentLangSelection(string);
string getFolder();
void cls();
string BrowseFolder();
void SearchFolder( TCHAR * );
void downloadFiles();
void pause();
int soundSelection();
void processTransfer();

//global vars
string leaguePath;
string currentLangName;
string currentLangCode;
string desiredLangName;
string desiredLangCode;
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


void processTransfer(){
  if(soundInt >= 4){
    //need to do announcer sounds

    soundInt = soundInt - 4;
  }

  if(soundInt >= 2){
    //need to do in game character sounds

    soundInt = soundInt - 2;
  }

  if(soundInt >= 1){
    //need to do champ select character sounds

    soundInt = soundInt - 1;
  }

}

int soundSelection(){

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

void downloadFiles(){
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
  if (dirExists(currentPath)){
    if (!dirExists(desiredPath)){
      // remote path dosent exist
      cout << "ERRORL: Count not find path:" << endl;
      cout << desiredPath << endl << endl;
      cout << "Please check you entered the correct path and try again." << endl;
      pause();
      exit;
    }
  }else{
    // local path dosent exist
    cout << "ERRORL: Count not find path:" << endl;
    cout << currentPath << endl << endl;
    cout << "Please check you entered the correct path and try again." << endl;
    pause();
    exit;
  }
}


//Gets the location of the league folder
string getFolder(){
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
string BrowseFolder(){
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
          //  cout << path << endl;
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
