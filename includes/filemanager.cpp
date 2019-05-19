#include <boost/algorithm/string.hpp>
#include <string.h>
#include <time.h>
#include <GL/glui.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

#include <algorithm>
#include <dirent.h>
#include <common.h>
#include <filemanager.hpp>

string workingDirectory;

void getDirContent(char const * path, vector<string> &filesList)
{
  string s;
  DIR *dirp;
  struct dirent *directory;
  dirp = opendir(path);
  filesList.erase(filesList.begin(), filesList.end());

  if (dirp)
  {
    while ((directory = readdir(dirp)) != NULL)
    {
      s = directory->d_name;
      if(s.at(0)!= '.')
      filesList.push_back(s);
    }

    closedir(dirp);
  }else{
    cout<<"error opening dir!!"<<endl;
  }
  std::sort( filesList.begin(), filesList.end() );

}

string readFile(char const * path)
{

  string line,result="";

  ifstream readData (path);
  if (readData.is_open())
  {
    while ( getline (readData,line) )
    {
      result+=line+"\n";
    }
    readData.close();
  }else{
    cout<<"enable to openfile -> "<< path <<endl;
  }

  return result;
}

void readFile(char const * path, vector<string> &vec)
{

  string line;
  vec.erase(vec.begin(), vec.end());

  ifstream readData (path);
  if (readData.is_open())
  {
    while ( getline (readData,line) )
    {

      vec.push_back(line);
    }
    readData.close();
  }else{
    cout<<"Can't to openfile -> "<<path<<endl;
  }

}

vector<string> readFileToVec(char const * path)
{
  vector<string> vec;
  string line;

  ifstream readData (path);
  if (readData.is_open())
  {
    while ( getline (readData,line) )
    {

      vec.push_back(line);
    }
    readData.close();
  }else{
    cout<<"Can't to openfile -> "<<path<<endl;
  }

  return vec;
}

void getTutContent(const char *path, vector<string> &files, vector<string> &strings)
{
  string s;
  int strLength;
  getDirContent(path, files);

  for(unsigned int i=0; i< files.size(); i++){
    s = path;
    s +="/"+files.at(i);
    strings.push_back(readFile(s.c_str()));
    strLength = files.at(i).length();
  }
}

void getTutContent(const char *path, vector<string> &files, vector< vector<string> > &strings)
{
  string s;
  vector<string> tmpVec;
  int strLength;
  files.erase(files.begin(), files.end());
  getDirContent(path, files);

  for(unsigned int i=0; i< files.size(); i++){
    s = path;
    s +="/"+files.at(i);
    readFile(s.c_str(),tmpVec);
    strings.push_back(tmpVec);
    strLength = files.at(i).length();
  }

}

void createTesterDirectories(string folder)
{
  string s = "cd "+workingDirectory + " && mkdir -p " + folder + "/includes";
  //s += " && mkdir -p testerFiles/includes";
  system(s.c_str());

  s = "cd "+workingDirectory+"/" + folder;
  //s = "cd "+workingDirectory+"/testerFiles";
  s += " && mkdir -p includes/headers";
  system(s.c_str());

  s = "cd "+workingDirectory+"/" + folder;
  //s = "cd "+workingDirectory+"/testerFiles";
  s += " && mkdir -p includes/shaders";
  system(s.c_str());

  s = "cd "+workingDirectory+"/" + folder;
  //s = "cd "+workingDirectory+"/testerFiles";
  s += " && mkdir -p includes/textFiles";
  system(s.c_str());

  s = "cd "+workingDirectory+"/" + folder;
  //s = "cd "+workingDirectory+"/testerFiles";
  s += " && mkdir -p includes/other";
  system(s.c_str());
}

bool checkFileOnDisk(const string& name){
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void removeTesterDirectories()
{

  string s = "rm -rf "+workingDirectory+"/testerFiles/includes";
  system(s.c_str());

  s = "rm -f "+workingDirectory+"/testerFiles/exe "+workingDirectory+"/testerFiles/main.cpp "+workingDirectory+"/testerFiles/error.log "+workingDirectory+"/testerFiles/terminalOutput.txt";
  system(s.c_str());

}
