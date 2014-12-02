#ifndef UTILITIES_H
#define UTILITIES_H

#include <sstream>
#include <string>
#include <unistd.h>
#include <set>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <shlobj.h>
#include <cstdlib>

#include <vector>
using namespace std;
using std::string;

void cls();
void mySleep(int myTime);
void pause();
bool numeric_string_compare(const std::string& s1, const std::string& s2);
bool is_not_digit(char c);
string searchVectorFor(string value, vector<string> vector);
string BrowseFolder();
string lowerCase(string str);
string stripFileName(string path);
void remove_duplicates(vector<string>& vec);
#endif
