#include "Utilities.hpp"

using namespace std;


// clears the shell
void cls(){
  system("cls");
}

void pause()
{
  system("pause");
}

void mySleep(int myTime){
    Sleep(myTime);
}

string stripFileName(string path){
    int indexOfLastSlash = path.find_last_of("/");
    string fileName = path.substr(indexOfLastSlash+1,path.size());
    return fileName;
}

bool numeric_string_compare(const std::string& s1, const std::string& s2)
{
    // handle empty strings...
    //https://stackoverflow.com/questions/4622516/sorting-stdstrings-with-numbers-in-them

    std::string::const_iterator it1 = s1.begin(), it2 = s2.begin();

    if (std::isdigit(s1[0]) && std::isdigit(s2[0])) {
        int n1, n2;
        std::stringstream ss(s1);
        ss >> n1;
        ss.clear();
        ss.str(s2);
        ss >> n2;

        if (n1 != n2) return n1 < n2;

        it1 = std::find_if(s1.begin(), s1.end(), is_not_digit);
        it2 = std::find_if(s2.begin(), s2.end(), is_not_digit);
    }

    return std::lexicographical_compare(it1, s1.end(), it2, s2.end());
}


bool is_not_digit(char c)
{
    return !std::isdigit(c);
}


string searchVectorFor(string value, vector<string> vector)
{
  for(int i=0; i<vector.size(); i++){
    string item = vector[i];
    if(item.find(value) != std::string::npos){
      //found
      return vector[i];
    }
  }
  return "null";
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

string lowerCase(string str){
  std::string my_string(str);
  for(unsigned int i = 0; i < my_string.length(); ++i) {
      my_string[i] = tolower(my_string[i]);
  }
  return my_string;
}
