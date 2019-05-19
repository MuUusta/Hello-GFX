#include <fontLoader.hpp>

void getFontDirContent(char const * path, vector<string> &filesList)
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

void addFontList(vector<MyFont> &list){
  vector<string> tmpList;
  getFontDirContent("fonts/", tmpList);

  for (size_t i = 0; i < tmpList.size(); i++) {
    list.push_back(MyFont(tmpList.at(i)));
  }
}
