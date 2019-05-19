#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP


void getDirContent(char const * path, vector<string> &filesList);
string readFile(char const * path);
void readFile(char const * path, vector<string> &vec);
vector<string> readFileToVec(char const * path);
void getTutContent(const char *path, vector<string> &files, vector<string> &strings);
void getTutContent(const char *path, vector<string> &files, vector< vector<string> > &strings);
void createTesterDirectories(string folder);
void removeTesterDirectories();
bool checkFileOnDisk(const string& name);

#endif //FILE-MANAGER_HPP
