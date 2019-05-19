#ifndef TUTORIALSCLASS_H
#define TUTORIALSCLASS_H

enum Mode {Immediate_Mode, Retained_Mode, Both};
Mode immediateMode = Immediate_Mode;
Mode retainedMode = Retained_Mode;
ImVec4 hpCol1 = ImVec4(1.0,1.0,1.0,1.0);
ImVec4 hpCol2 = ImVec4(1.0,1.0,1.0,1.0);

class T_Code{
private:

  void loadCode(){
    strcpy(this->codeText, readFile(url.c_str()).c_str());
  }

public:
  string url;
  char codeText[1024*64];
  char codeTabName[1024];
  int tutNum;
  T_Code(string url, int tutNo, string name){

    this->url = url;
    this->tutNum = tutNo;
    strcpy(this->codeTabName, name.c_str());
    loadCode();

  }
  ~T_Code();


};vector<T_Code*> t_CodeVec;

class T_Image{
private:


public:
  string url;
  unsigned int id;
  int tutNum;
  int lineNum;
  int width,height;
  T_Image(string url, int tutNo, int lineNo){

    this->url = url;
    this->tutNum = tutNo;
    this->lineNum = lineNo;

  }
  ~T_Image();

  void loadTheImage(){
    this->id = loadTex_stb(url.c_str(), width, height);
  }

};vector<T_Image*> t_ImageVec;

class About{
private:
  string mainHyperlink, otherHyperlink;
  string tmp;

public:

  vector<string> aboutText;

  About(vector<string> hyperlinks, vector<string> text){

    mainHyperlink = hyperlinks.at(0);
    otherHyperlink = hyperlinks.at(1);
    for (size_t i = 0; i < text.size(); i++) {
      aboutText.push_back(text.at(i));
    }
    aboutText.at(aboutText.size()-3) = aboutText.at(aboutText.size()-3) + mainHyperlink;
    aboutText.at(aboutText.size()-1) = aboutText.at(aboutText.size()-1) + otherHyperlink;

  }

  void renderAbout(){
    for (size_t i = 0; i < aboutText.size()-3; i++) {
      ImGui::Text(aboutText.at(i).c_str());
    }

    ImGui::TextColored(hpCol1,aboutText.at(aboutText.size()-3).c_str());
    if (ImGui::IsItemHovered()){
      hpCol1.x = 0.5;hpCol1.y = 0.5;hpCol1.z = 1.0;
    }else{
      hpCol1.x = 1.5;hpCol1.y = 1.5;hpCol1.z = 1.0;
    }
    tmp = "xdg-open " + aboutText.at(aboutText.size()-3);
    if (ImGui::IsItemClicked()){system(tmp.c_str());}

    ImGui::Text(aboutText.at(aboutText.size()-2).c_str());

    ImGui::TextColored(hpCol2,aboutText.at(aboutText.size()-1).c_str());
    if (ImGui::IsItemHovered()){
      hpCol2.x = 0.5;hpCol2.y = 0.5;hpCol2.z = 1.0;
    }else{
      hpCol2.x = 1.5;hpCol2.y = 1.5;hpCol2.z = 1.0;
    }
    tmp = "xdg-open " + aboutText.at(aboutText.size()-1);
    if (ImGui::IsItemClicked()){system(tmp.c_str());}
  }

};

class Resources{
private:
  string hyperLinkName, url, commandTmpString;
  ImVec4 origColor;
public:
  int atTutNum, afterlineNum;
  bool isHovered = false;
  Resources(string hlName, string url, int tutNumber, int lineNum){
    this->hyperLinkName = hlName;
    this->url = url;
    this->atTutNum = tutNumber;
    this->afterlineNum = lineNum;
    commandTmpString = "xdg-open " + url;
  }
  ~Resources(){}
  void renderResources(int index, int i){

    if(atTutNum == index && i == afterlineNum){
      ImGui::TextColored(origColor, hyperLinkName.c_str(),i);
      ImGui::SameLine();
      if(ImGui::IsItemClicked()){
        system(commandTmpString.c_str());
      }
      if(ImGui::IsItemHovered()){
        isHovered = true;
        origColor = ImVec4(0.3,0.4,1.0,1.0);
      }
      else{
        isHovered = false;
        origColor = ImVec4(0.4,0.5,1.0,1.0);
      }
    }
  }
};vector<Resources*> t_ResourcesVec; vector<bool> isHyprLinkHoveredVec;

class Tutorial{

private:

  string name;
  Mode mode;
  vector<string> tutorialsMainFolder;
  vector<string> titles, tmpFiles;
  //vector<vector<string> > codeDisplayList;
  vector<About> about;

public:
  vector<vector<string> > tutDisplayList;
  Tutorial(string name, Mode mode, string pathList[], int pathListSize);
  ~Tutorial();

  void generate_Tutorials_Components();
  void generate_Tutorials_Titles();
  void generate_Tutorials_Abouts();
  //setters
  void set_name(string name);
  void set_Mode(Mode mode);
  void set_tutorials_path(string pathList[], int pathListSize);
  //getters
  vector<string> get_Tutorial_Text_At(int x);
  About get_About_At(int x);
  string get_Tutorial_Title_at(int x);
  vector<string> get_Tutorial_Titles();
  string get_name();
  Mode get_Mode();

};

Tutorial::Tutorial(string name, Mode mode, string pathList[], int pathListSize){

  set_name(name);
  set_Mode(mode);

  set_tutorials_path(pathList, pathListSize);
  generate_Tutorials_Components();
  generate_Tutorials_Titles();
  generate_Tutorials_Abouts();

}

Tutorial::~Tutorial(){

}

void Tutorial::generate_Tutorials_Components(){

  //getting tutorials file strings
  for (size_t i = 0; i < tutorialsMainFolder.size(); i++) {
    getTutContent((tutorialsMainFolder.at(i)+"/tutorials").c_str(), tmpFiles, tutDisplayList);
  }

  //tutorial images
  ifstream readImageData ("Configurations/images.CONFIG");
  int counter = 0, tmp1,tmp2; string tmpUrl ="",line, tmpTName;
  if (readImageData.is_open())
  {
    while ( getline (readImageData,line) )
    {
      if(counter > 2)
      counter = 0;

      if(counter == 0)
      tmpUrl = line;
      if(counter == 1)
      tmp1 = stoi(line);
      if(counter == 2){
        tmp2 = stoi(line);
        t_ImageVec.push_back(new T_Image(tmpUrl,tmp1,tmp2));
      }
      counter++;
    }
    readImageData.close();
  }else
  cout<<"can't open >"<<"Configurations/images.CONFIG"<<endl;

  //tutorial code files
  ifstream readCodeData ("Configurations/codes.CONFIG");
  counter = 0;
  if (readCodeData.is_open())
  {
    while ( getline (readCodeData,line) )
    {
      if(counter > 2)
      counter = 0;

      if(counter == 0)
      tmpUrl = line;
      if(counter == 1)
      tmpTName = line;
      if(counter == 2){
        tmp1 = stoi(line);
        t_CodeVec.push_back(new T_Code(tmpUrl,tmp1,tmpTName));
      }
      counter++;
    }
    readCodeData.close();
  }else
  cout<<"can't open >"<<"Configurations/codes.CONFIG"<<endl;


  //tutorial's additional resources
  ifstream readResourcesData ("Configurations/resources.CONFIG");
  string hlNameTmp,urlTmp;
  counter = 0;
  if (readResourcesData.is_open())
  {
    while ( getline (readResourcesData,line) )
    {
      if(counter > 3){
        counter = 0;
      }

      if(counter == 0)
        hlNameTmp = line;
      if(counter == 1)
        urlTmp = line;
      if(counter == 2)
        tmp1 = stoi(line);
      if(counter == 3){
        tmp2 = stoi(line);
        t_ResourcesVec.push_back(new Resources(hlNameTmp,urlTmp,tmp1,tmp2));
        isHyprLinkHoveredVec.push_back(false);
      }

      counter++;
    }
    readResourcesData.close();
  }else
  cout<<"can't open >"<<"Configurations/resources.CONFIG"<<endl;

}

void Tutorial::generate_Tutorials_Titles(){
  readFile("titles/tutorial_titles.txt", titles);
    tutorialsNumber = titles.size();
}

void Tutorial::generate_Tutorials_Abouts(){
  vector<string> tmpHL, finalHL;
  finalHL.push_back("");
  finalHL.push_back("");
  for (size_t i = 0; i < tutorialsMainFolder.size(); i++) {
    tmpHL = readFileToVec((tutorialsMainFolder.at(i)+"/hyperlinks/hyperlinks.txt").c_str());
    for (size_t j = 0; j < tmpHL.size()-1; j++) {
      finalHL.at(0) = tmpHL.at(0);
      finalHL.at(1) = tmpHL.at(j+1);
      about.push_back(About(finalHL,readFileToVec((tutorialsMainFolder.at(i)+"/about/about.txt").c_str()) ));
    }
    tmpHL.erase(tmpHL.begin(), tmpHL.end());
  }


  finalHL.erase(finalHL.begin(), finalHL.end());
}

void Tutorial::set_name(string name){
  this->name = name;
}

void Tutorial::set_Mode(Mode mode){
  this->mode = mode;
}

void Tutorial::set_tutorials_path(string pathList[], int pathListSize){

  for (int i = 0; i < pathListSize; i++) {
    this->tutorialsMainFolder.push_back(pathList[i]);
  }

}

vector<string> Tutorial::get_Tutorial_Text_At(int x){
  return this->tutDisplayList.at(x);
}

string Tutorial::get_Tutorial_Title_at(int x){
  return this->titles.at(x);
}

vector<string> Tutorial::get_Tutorial_Titles(){
  return this->titles;
}

About Tutorial::get_About_At(int x){
  return this->about.at(x);
}


string Tutorial::get_name(){
  return this->name;
}

Mode Tutorial::get_Mode(){
  return this->mode;
}

#endif //TUTORIALSCLASS_H
