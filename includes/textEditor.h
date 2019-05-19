#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


static char mainFunctionText[1024*16] = "int main(int argc, char* argv[])\n{\n\n return 0;\n}";
static char displayFunctionText[1024*16] = "void myDisplayFunction()\n{\n\n glutSwapBuffers();\n}";
static char reshapeFunctionText[1024*16] = "void myReshapeFunction( int x, int y )\n{\n\n}";
static char keyboardFunctionText[1024*16] = "void myKeyboardFunction(unsigned char key, int x, int y)\n{\n\n}";
static char keyboardUpFunctionText[1024*16] = "void myKeyboardUpFunction(unsigned char key, int x, int y)\n{\n\n}";
static char specialFunctionText[1024*16] = "void mySpecialFunction(int key, int x, int y)\n{\n\n}";
static char specialUpFunctionText[1024*16] = "void mySpecialUpFunction(int key, int x, int y)\n{\n\n}";
static char motionFunctionText[1024*16] = "void myMotionFunction(int x, int y )\n{\n\n}";
static char mouseFunctionText[1024*16] = "void myMouseFunction(int button, int state, int x, int y )\n{\n\n}";
static char idleFunctionText[1024*16] = "void myIdleFunction()\n{\n\n}";
static char timerFunctionText[1024*16] = "void myTimerFunction(int)\n{\n glutPostRedisplay();\n glutTimerFunc(1000/60, myTimerFunction, 0);\n}";

static char teIncludedFiles[1024*16] = "#include <string.h>\n#include <time.h>\n#include <vector>\n#include <GL/freeglut.h>\n#include <iostream>\n\nusing namespace std;\n";
static char teGlobalVars[1024*16] = "//Global variables.";

static char customFuncText[128] = "";
static char customFileText[128] = "";

enum TabType {EmptyType,Function_Tab, File_Tab}; TabType globalTabType;
enum Functions {EmptyFunc, DisplayFunc, ReshapeFunc, KeyboardFunc, KeyboardUpFunc, SpecialFunc, SpecialUpFunc, MotionFunc, MouseFunc, IdleFunc, TimerFunc, CustomFunction}; Functions globalTabFunc;
enum Files {EmptyFile, Header, Shader, Text, Other}; Files globalTabFile;

int teTabsNumber = 0;
static ImGuiInputTextFlags teTabsFlags = ImGuiInputTextFlags_AllowTabInput;

class Tabs{

private:

public:
  string tab_Name, id="##textInput";
  char tabText[1024*16];
  TabType tType = EmptyType;
  Functions func = EmptyFunc;
  Files tFile = EmptyFile;
  bool open;

  Tabs(TabType tt, Functions tFunc, int id);
  Tabs(TabType tt, Functions tFunc, string fname, int id);
  Tabs(TabType tt, Files tfile, char fname[], int id, bool dif);
 ~Tabs();
 void renderTab();

};vector<Tabs> teTabs;

Tabs::Tabs(TabType tt, Functions tFunc, int id){
  this->tType = tt;
  this->func = tFunc;
  this->id += id;
  this->open = true;

    if(tFunc == DisplayFunc){strcpy(tabText, displayFunctionText);this->tab_Name ="myDisplayFunction";}     if(tFunc == ReshapeFunc){strcpy(tabText, reshapeFunctionText);this->tab_Name ="myReshapeFunction";}
    if(tFunc == KeyboardFunc){strcpy(tabText, keyboardFunctionText);this->tab_Name ="myKeyboardFunction";}  if(tFunc == KeyboardUpFunc){strcpy(tabText, keyboardUpFunctionText);this->tab_Name ="myKeyboardUpFunction";}
    if(tFunc == SpecialFunc){strcpy(tabText, specialFunctionText);this->tab_Name ="mySpecialFunction";}     if(tFunc == SpecialUpFunc){strcpy(tabText, specialUpFunctionText);this->tab_Name ="mySpecialUpFunction";}
    if(tFunc == MotionFunc){strcpy(tabText, motionFunctionText);this->tab_Name ="myMotionFunction";}        if(tFunc == MouseFunc){strcpy(tabText, mouseFunctionText);this->tab_Name ="myMouseFunction";}
    if(tFunc == IdleFunc){strcpy(tabText, idleFunctionText);this->tab_Name ="myIdleFunction";}              if(tFunc == TimerFunc){strcpy(tabText, timerFunctionText);this->tab_Name ="myTimerFunction";}

}
Tabs::Tabs(TabType tt, Functions tFunc, string fname, int id){
  this->tType = tt;
  this->func = tFunc;
  this->tab_Name = fname;
  this->id += id;
  this->open = true;
  string s = "void ";
  s+= this->tab_Name;
  s+= "( /* DataType param1 */, /* DataType paaram2 */)\n{\n\n\n\n\n}";
  strcpy(tabText, s.c_str());
}
Tabs::Tabs(TabType tt, Files tfile, char fname[], int id, bool dif){
  this->tType = tt;
  this->tFile = tfile;
  this->id += id;
  this->open = true;
  this->tab_Name = fname;
  string tmp = "", tmp2 = "";
  strcpy(tabText, "");
  if(tfile == Header){
    tmp = "#ifndef "; tmp2 = this->tab_Name.substr(0, this->tab_Name.length()-2); boost::to_upper(tmp2);
    tmp += tmp2;
    tmp += "_H";
    tmp +="\n#define ";
    tmp += tmp2;
    tmp += "_H\n\n\n\n\n#endif //";
    tmp += tmp2;

    strcpy(this->tabText, tmp.c_str());

    tmp = teIncludedFiles;
    tmp += "\n#include \"includes/headers/"+this->tab_Name+"\"";
    strcpy(teIncludedFiles, tmp.c_str());
  }
  if(tfile == Shader){
    tmp = "//This file path to include in your code = \"includes/shaders/"+this->tab_Name+"\"";
    tmp += "\n#version 330 core\n\n\nvoid main()\n{\n\n\n}";
    strcpy(this->tabText, tmp.c_str());
  }
  if(tfile == Text){

    tmp = "//This file path to include in your code = \"includes/textFiles/"+this->tab_Name+"\"";
    strcpy(this->tabText, tmp.c_str());
  }
  if(tfile == Other){
    tmp = "//This file path to include in your code = \"includes/other/"+this->tab_Name+"\"";
    strcpy(this->tabText, tmp.c_str());
  }

}

Tabs::~Tabs(){

}
void Tabs::renderTab(){
  if(open){
    if (ImGui::BeginTabItem(tab_Name.c_str(), &open))
    {
      ImGui::InputTextMultiline(id.c_str(), tabText, IM_ARRAYSIZE(tabText), ImVec2(teWindowSize.x-15, teWindowSize.y-100), teTabsFlags);

      ImGui::EndTabItem();
    }
  }
}
#endif //TEXTEDITOR_H
