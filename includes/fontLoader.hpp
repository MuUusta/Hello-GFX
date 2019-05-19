#ifndef FONTLOADER_HPP
#define FONTLOADER_HPP

#include <iostream>
#include <algorithm>
#include <dirent.h>
#include <vector>
#include <string>
#include <common.h>
using namespace std;

class MyFont{
public:
  std::string name;
  float size = 15.0f;
  MyFont(string s){name = s;}
};

void getFontDirContent(char const * path, vector<string> &filesList);
void addFontList(vector<MyFont> &list);

#endif //FONTLOADER_HPP
