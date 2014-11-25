
#include "DirTraveler/DirTraveler.hpp"
#include "FileActions/FileActions.hpp"
#include "Utilities/Utilities.hpp"

#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

string* currentLangSelection(string);
string getLeagueFolderPath();
string BrowseFolder();
void changeChampSelectSounds();
void changeGameCharacter();
void downloadFiles();
void changeAnnouncerSounds();
int soundSelection();
void processTransfer();
vector<string> findChampionFolders(string inDir);

//global vars
DirTraveler traveler;
bool debug = false;
string leaguePath;
string currentLangName;
string currentLangCode;
string desiredLangName;
string desiredLangCode;
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
  "Chogath",
  "Corki",
  "Darius",
  "Diana",
  "DrMundo",
  "Draven",
  "Elise",
  "Evelynn",
  "Ezreal",
  "FiddleSticks",
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
  "Jax",
  "Jayce",
  "Jinx",
  "Karma",
  "Karthus",
  "Kalista",
  "Kassadin",
  "Katarina",
  "Kayle",
  "Kennen",
  "Khazix",
  "KogMaw",
  "Leblanc",
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
  "Velkoz",
  "Viktor",
  "Vi",
  "Vladimir",
  "Volibear",
  "Warwick",
  "MonkeyKing",
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



int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++){
      string str = argv[i];
      if (str == "debug"){
        cout << "Im here" << endl;
        currentLangCode = "en_GB";
        currentLangName = "English";
        desiredLangCode = "ko_KR";
        desiredLangName = "Korean";
        leaguePath = "C:\\Games\\League of Legends";
        soundInt = 7;
        debug = true;
        processTransfer();
      }
    }

    if (debug == false){
      string *currentLang = currentLangSelection("CURRENT");
      currentLangName = currentLang[0];
      currentLangCode = currentLang[1];
      cls();
      string *desiredLang = currentLangSelection("DESIRED");
      desiredLangName = desiredLang[0];
      desiredLangCode = desiredLang[1];
      cls();
      leaguePath = getLeagueFolderPath();
      cls();
      downloadFiles();
      cls();
      soundInt = soundSelection();
      cls();
      processTransfer();
    }
    cout << "At the end" << endl;
    pause();
    return 0;
}



void processTransfer(){
  if(soundInt >= 4){
    //need to do announcer sounds
    soundInt = soundInt - 4;
    cout << endl << endl;
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "Current operation : Changing the announcer sounds." << endl << endl;
    changeAnnouncerSounds();
    cout << "Status - Complete : Changing the announcer sounds." << endl < endl;
  }

  if(soundInt >= 2){
    //need to do in game character sounds
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "Current operation : Changing the in-game character sounds." << endl << endl;
    changeGameCharacter();
    cout << "Status - Complete : Changing the in-game character sounds." << endl < endl;
    soundInt = soundInt - 2;
  }

  if(soundInt >= 1){
    //need to do champ select character sounds
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "Current operation : Changing champion select champion sounds." << endl << endl;
    changeChampSelectSounds();
    cout << "Status - Complete : Changing champion select champion sounds." << endl < endl;
    soundInt = soundInt - 1;
  }

}


void changeAnnouncerSounds(){
  vector<string> currentPath;
  vector<string> desiredPath;

  vector<string> foo;
  vector<string> rejected;
  traveler.travelDirectoryRecursiveReturnFiles(leaguePath,&foo);
  //sort according to path folder numbers
  sort(foo.begin(), foo.end(), numeric_string_compare);

  for (int i=foo.size()-1; i>=2; i--){
    string ppath = foo[i].c_str();
    //cout << "Checking folder : " << folder << endl;

    //look for announcer file
    //Creats three lists of "announcer file"
    if(ppath.find("Announcer") != std::string::npos | ppath.find("NPC_Map") != std::string::npos){
      if(ppath.find(desiredLangCode) != std::string::npos | ppath.find(lowerCase(desiredLangCode)) != std::string::npos){
        //its a desired path
        desiredPath.push_back(ppath);
      }else if(ppath.find(currentLangCode) != std::string::npos | ppath.find(lowerCase(currentLangCode)) != std::string::npos){
        //its a current path (e.g. gb_GB)
        currentPath.push_back(ppath);
      }else{
        rejected.push_back(ppath);
      }
    }
  }

    for(int i=0; i<desiredPath.size(); i++){
        string srcItem = desiredPath[i];
        //Get file name
        string fileName = stripFileName(srcItem);

        if(debug){
            cout << "Filenames = " << fileName << endl;
        }

        for(string dstItem : currentPath){
            if(dstItem.find(fileName)  != std::string::npos){
                //found srcItem in current folder
                //replace with desired srcItem
                if(debug){
                    cout << "Found match with " << dstItem << endl;
                }
                cout << "     Source = " << srcItem << endl << "Destination = " << dstItem << endl;
                replaceFile(srcItem, dstItem);

                //remove found srcItem from vector
                currentPath.erase(std::remove(currentPath.begin(), currentPath.end(), dstItem), currentPath.end());
                cout << endl;
                break;
            }
        }
    }
}

//  Checks for duplicate champion folders and chooses the one with the highest verion number.
vector<string> removeChampionFolderDuplicates(vector<string> origList){
  int numOfChamps = sizeof( champions ) / sizeof( champions[ 0 ] );
  vector<string> newList;
  //for each champ
  for (int i=0; i<numOfChamps; i++){
    vector<string> duplicateList;
    string name = champions[i];
    cout << endl << name << endl;
    //for each path
    for(int i = 0; i<origList.size(); i++){
      string path = origList[i];
      //if patch contaitns champion name
      if(path.find(name) != std::string::npos){
        duplicateList.push_back(path);
        cout << "Adding to dup list " << path << endl;
      }
    }
    cout << "Duplicate list size " << duplicateList.size() << endl;
    if(duplicateList.size() >= 1){
      cout << "Before sort " << duplicateList[0] << endl;
      sort(duplicateList.begin(), duplicateList.end(), numeric_string_compare);
      cout << "AFter sort " << duplicateList[duplicateList.size()-1] << endl;

      newList.push_back(duplicateList[duplicateList.size()-1]);

    }else{
      cout << "ERROR: no folder for champion " << name << endl << endl;
      pause();
    }

  }

  return newList;
}


void changeGameCharacter()
{
  string currentClientFolder = leaguePath + "\\RADS\\projects\\lol_game_client_" + currentLangCode ;
  string desiredClientFolder = leaguePath + "\\RADS\\projects\\lol_game_client_" + desiredLangCode ;

  cout << "Folder 1 " << currentClientFolder << endl;
  cout << "Folder 2 " << desiredClientFolder << endl;

  if(traveler.DirectoryExists(currentClientFolder.c_str())){
    if(traveler.DirectoryExists(desiredClientFolder.c_str())){

      vector<string> currentChampsWithDuplicates = findChampionFolders(currentClientFolder);
      vector<string> currentChamps = removeChampionFolderDuplicates(currentChampsWithDuplicates);

      vector<string> desiredChampsWithDuplicates = findChampionFolders(desiredClientFolder);
      vector<string> desiredChamps = removeChampionFolderDuplicates(desiredChampsWithDuplicates);

      int numOfChamps = sizeof( champions ) / sizeof( champions[ 0 ] );

      for(int i=0; i<numOfChamps; i++){
        string champ = champions[i];
        cout << endl << "Current champ: " << champ << endl;
        string currentPath = searchVectorFor(champ, currentChamps);
        string desiredPath = searchVectorFor(champ, desiredChamps);

        ReplaceDirectory(currentPath,desiredPath);

      }
    }else {
      cout << "Could not find desired language folder : " << desiredClientFolder << endl;
      pause();
    }
  }else{
    cout << "Could not find current language folder : " << currentClientFolder << endl;
    pause();

  }
}


//finds all the champion subfolders in a folder
vector<string> findChampionFolders(string inDir){
  //both folders exist;
  int numOfChamps = sizeof( champions ) / sizeof( champions[ 0 ] );
  cout << "Size of champ array is " << numOfChamps << endl;
  vector<string> listOfDoneChamps;

  //Array of fodlers in current folder
  vector<string> foo;
  traveler.travelDirectoryRecursiveReturnFolders(inDir ,&foo);
  //Look at each folder for champion folders
  for (int i=2; i<foo.size(); ++i){
    string folder = foo[i].c_str();
    //cout << "Checking folder : " << folder << endl;

    //Check if its a champion folder
    for (int i=0; i<numOfChamps; i++){
      string name = champions[i];
      if(folder.find(name) != std::string::npos){
        //if found exit loop
        i = numOfChamps;
        //cout << "Found champ folder for " << name << endl;
        string folderPath = folder.substr(0,folder.find(name)) + name;
        //cout << "At path : " << folderPath << endl << endl;

        if (find(listOfDoneChamps.begin(), listOfDoneChamps.end(), folderPath) == listOfDoneChamps.end()){
          //NOt found in listOfDoneChamps
          cout << "Adding " << folderPath << endl;
          listOfDoneChamps.push_back(folderPath);
        }
      }
    }
  }

  if(listOfDoneChamps.size() != numOfChamps){
    cout << "ERROR: Number of champs too low, only found " << listOfDoneChamps.size() << " number of champion folders" << endl;
  }else{
    cout << "Found all champion folders in : " << inDir << endl;
  }

  return listOfDoneChamps;

}


void changeChampSelectSounds()
{

  string str = leaguePath + "\\RADS\\projects\\lol_air_client\\releases";
  cout << str << endl;
  vector<string>foo;

  foo = traveler.travelDirectory(str);
  for (int i=2; i<foo.size(); ++i){
      string folder = foo[i].c_str();
      //cout << folder << endl;

      string newPath = str + "\\" + folder + "\\deploy\\assets\\sounds\\";
      //cout << "new path = " << newPath << endl;
      bool ansCurrentLang = traveler.DirectoryExists((newPath + currentLangCode).c_str());
      bool ansDesiredLang = traveler.DirectoryExists((newPath + desiredLangCode).c_str());


      cout << "Currently changing the announcer sounds to " << desiredLangName << endl;

      if(ansCurrentLang == 1 && traveler.DirectoryExists((newPath + currentLangCode + "_BACKUP").c_str()) != 1){
        cout << "Creating a backup of " << currentLangCode << " file." << endl;
        //folders found
          // If backup not exist, backup.
          CopyDirectory(newPath + currentLangCode, newPath + currentLangCode + "_BACKUP");
      }else{

          cout << "Backup of " << currentLangCode << " already exists." << endl;
      }

      if(ansDesiredLang == 1){
        //copy((newPath + desiredLangCode), (newPath + currentLangCode));
        ReplaceDirectory(newPath + currentLangCode,newPath + desiredLangCode);
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
  cout <<  "Please ensure that this program is running as administrator!!!" << endl;
  cout << endl;
  cout << "1: Go to " << leaguePath << "\\Rads\\system\\" << " and open 'locale.cfg' in a" << endl;
  cout << "   text editor." << endl;
  cout << endl;
  cout << "2: Paste 'locale=" << desiredLangCode << "' into the document (without the quotes) overwriting the" << endl;
  cout << "   existing text." << endl;
  cout << endl;
  cout << "3: Reopen the league of legends launcher and let the client download the new" << endl;
  cout << "   files. This will download the new language versions of the files needed. Once" << endl;
  cout << "   completed you should have two folders in the" << endl;
  cout << "   '" << leaguePath << "\\RADS\\projects\\'" << endl;
  cout << "   folder, 'lol_game_client_" << desiredLangCode << "' and 'lol_game_client_" << currentLangCode << "'." << endl;
  cout << endl;
  cout << "4: Once League of Legends has downloaded the alternate version close the League" << endl;
  cout << "   window and re-open " << leaguePath << "\\system\\locale.cfg and" << endl;
  cout << "   replace the text with what it was origionally ('locale=" << currentLangCode << "')."  << endl;
  cout << endl;
  cout << "5: Reopen the league of legends client again and it should download a smaller patch.";
  cout << endl;
  cout <<  "--------------------------------------------------------------------------------" << endl;
  pause();

  //e.g. ko_KR
  string desiredPath = leaguePath + "\\RADS\\projects\\lol_game_client_" + desiredLangCode;
  string currentPath = leaguePath + "\\RADS\\projects\\lol_game_client_" + currentLangCode;

    if (!traveler.DirectoryExists(desiredPath.c_str())){
      // remote path dosent exist
      cout << "ERROR: Count not find path:" << endl;
      cout << desiredPath << endl << endl;
      cout << "Please check you entered the correct path and try again." << endl << endl;
      pause();
      exit(1);
    }
}


//Gets the location of the league folder
string getLeagueFolderPath()
{
  cout <<  "--------------------------------------------------------------------------------" << endl;
  cout << "Please enter the location of the 'League of Legends' folder." << endl;
  cout << endl;
  cout <<  "--------------------------------------------------------------------------------" << endl;
  return BrowseFolder();
}

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
