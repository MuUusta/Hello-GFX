
//ignoring some compilation warnings/////////////////////
#pragma GCC diagnostic ignored "-Wformat-security"     //
#pragma GCC diagnostic ignored "-Wconversion-null"     //
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" //
#pragma GCC diagnostic ignored "-Wformat-zero-length"  //
/////////////////////////////////////////////////////////

///////////////////ImGui/////////////////
#include <imgui/imgui.h>               //
#include <imgui/imgui_impl_freeglut.h> //
#include <imgui/imgui_impl_opengl2.h>  //
/////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER                                                                  //
#pragma warning (disable: 4505) // unreferenced local function has been removed  //
#endif                                                                           //
///////////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <chrono>

///////////////////////////////
#include <string>            //
#include <textureLoading.h>  //
#include <math.h>            //
#include <SFML/Audio.hpp>    //
#include <musicPlayer.hpp>   //
#include <stb_image.h>       //
#include <common.h>          //
#include <filemanager.hpp>   //
///////////////////////////////

using namespace std;

bool showExternCtrl = false;
bool openPlayer, mpInitialized = false, playFlag = true, pauseFlag = false, resumeFlag = false, stopButtonPressed = true;
bool loop1Song = false, shuffleSongs = false;
GLuint bkgId,loopIcon,shuffleIcon,prvIcon,stopIcon,playIcon,nxtIcon,volume,pauseIcon,play_pauseIcon;
int currentSongINdex=0;
int volumeInt = 80;
float titleInc= 0.0f;
static float songPlayOffsetBarValue;
ImGuiStyle defStyle;

string mP_msg,mp_hide_buttonTXT = "Hide",mp_update_buttonTXT = "Update", mP_Msg_Default = "";
vector<Song> songsVec;
ImVec4 ctrlBcolors1(0.0, 0.5, 0.7, .4);
ImVec4 ctrlBcolors2(1.0, 0.3, 0.3, .9);
ImVec4 ctrlBcolors3(0.0, 0.5, 0.7, .4);
ImVec4 btnColor(0.2, 0.3, 0.4, 0.7);
ImVec4 btnColor2(0.2, 0.3, 0.4, 0.7);

Song::Song(string url, string name){
  buffer.loadFromFile(url+name);
  duration = buffer.getDuration().asSeconds();
  this->name = name;
}
Song::~Song(){

}
void Song::play(){

  soundCo = sf::Sound(buffer);
  soundCo.setVolume(volumeInt);
  soundCo.play();


}
void Song::setVolume(){
  soundCo.setVolume(volumeInt);
}
void Song::stop(){
  soundCo.stop();
}
void Song::pause(){
  soundCo.pause();
  pauseTime = soundCo.getPlayingOffset().asSeconds();
}
void Song::resume(){
  soundCo = sf::Sound(buffer);
  soundCo.setVolume(volumeInt);
  soundCo.play();
  soundCo.setPlayingOffset(sf::seconds(pauseTime));
}

string Song::getPlayOffset(){
  string res;int tmp;
  tmp = (int)(soundCo.getPlayingOffset().asSeconds());
  tmpInt = (int)(soundCo.getPlayingOffset().asSeconds()) % 61;
  seconds = (int)(soundCo.getPlayingOffset().asSeconds()) % 60;

  if(tmp < 1)
  minutes = 0;
  if(tmpInt != 60)
  reset = true;
  if (tmpInt == 60 && reset){
    minutes++;
    reset = false;
  }

  songPlayOffsetBarValue = soundCo.getPlayingOffset().asSeconds()/duration;
  if(minutes < 10)
  res = "0" + to_string(minutes);
  else
  res = to_string(minutes);

  res += ":";
  if(seconds < 10)
  res += "0" + to_string(seconds);
  else
  res += to_string(seconds);

  return res;
}

GLuint loadMPTextures(const char *path){
  int my_image_width, my_image_height;
  unsigned char* my_image_data = stbi_load(path, &my_image_width, &my_image_height, NULL, 4);

  // Turn the RGBA pixel data into an OpenGL texture:
  GLuint my_opengl_texture;
  glGenTextures(1, &my_opengl_texture);
  glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, my_image_width, my_image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_image_data);

  return my_opengl_texture;
}
void MP_init(){
  if(!mpInitialized){
    std::cout << "Initializing MusicPlayer!." << '\n';
    loadPLayerImages();
    mpInitialized = true;
  }
}
void loadPLayerImages(){
  bkgId = loadMPTextures("textures/musicPlayer/bkg.jpg");
  loopIcon = loadMPTextures("textures/musicPlayer/loop.png");
  shuffleIcon = loadMPTextures("textures/musicPlayer/shuffle.png");
  prvIcon = loadMPTextures("textures/musicPlayer/prev.png");
  stopIcon = loadMPTextures("textures/musicPlayer/stop.png");
  playIcon = loadMPTextures("textures/musicPlayer/play.png");
  pauseIcon = loadMPTextures("textures/musicPlayer/pause.png");
  nxtIcon = loadMPTextures("textures/musicPlayer/next.png");
  volume = loadMPTextures("textures/musicPlayer/volume.png");
  play_pauseIcon = playIcon;

  thread th{[](){
    loadSongs("Loading Songs.");
  }};
  th.detach();

}

std::vector<string> songsNamesList, songsTitles, songsNamesListOGG;
void loadSongs(string msg)
{
  std::cout << msg << '\n';
  int dotsCount = 0;
  ctrlBcolors2 = ImVec4(1.0, 0.3, 0.3, .9);
  mp_hide_buttonTXT = "";mp_update_buttonTXT = "";
  mP_msg = msg;

  getDirContent("Songs/MP-Sources", songsNamesListOGG);
  dotsCount++;
  mP_msg += ".";

  songsVec.erase(songsVec.begin(), songsVec.end());
  for (size_t i = 0; i < songsNamesListOGG.size(); i++) {
    songsVec.push_back(Song("Songs/MP-Sources/",songsNamesListOGG.at(i)));
    dotsCount++;
    mP_msg += ".";
    if(dotsCount > 3){
      dotsCount = 0;
      mP_msg = msg;
    }
  }
  ctrlBcolors2 = ImVec4(0.3, 0.7, 0.3, .9);
  mP_msg = "Done " + msg;
  std::this_thread::sleep_for (std::chrono::seconds(3));
  mP_msg = "";
  mp_hide_buttonTXT = "Hide";mp_update_buttonTXT = "Update";

  //convertMp3ToOGG();
}

void generateTitles()
{
  std::size_t foundAt;
  getDirContent("Songs/UserFiles", songsNamesList);
  for (size_t i = 0; i < songsNamesList.size(); i++) {
    foundAt = songsNamesList.at(i).find(".");
    songsTitles.push_back(songsNamesList.at(i).substr(0, foundAt));
  }
}

void convertMp3ToOGG()
{
  mp_hide_buttonTXT = "";mp_update_buttonTXT = "";
  ctrlBcolors2 = ImVec4(1.0, 0.3, 0.3, .9);
  int dots = 0;
  mP_Msg_Default = mP_msg = "Updating Songs.";
  string tmpString = "";
  generateTitles();
  dots++;
  mP_Msg_Default = mP_msg += ".";
  for (size_t i = 0; i < songsNamesList.size(); i++) {
    tmpString = "ffmpeg -i "+workingDirectory+"/Songs/UserFiles/"+songsNamesList.at(i)+" -n "+workingDirectory+"/Songs/MP-Sources/"+songsTitles.at(i)+".ogg";
    system(tmpString.c_str());
    dots++;
    mP_Msg_Default = mP_msg += ".";
    if(dots > 4){
      dots = 0;
      mP_Msg_Default = mP_msg = "Updating Songs.";
    }
  }
  ctrlBcolors2 = ImVec4(0.3, 0.7, 0.3, .9);
  mP_Msg_Default = mP_msg = "Done Updating Songs!";
  std::this_thread::sleep_for (std::chrono::seconds(3));
  mP_Msg_Default = mP_msg = "";
  mp_hide_buttonTXT = "Hide";mp_update_buttonTXT = "Update";
}

bool Song::isStatusStopped(){
  if (soundCo.getStatus() == sf::SoundSource::Status::Stopped) {
    return true;
  }else
  return false;
}

void stylingMusicPlayer(ImGuiStyle& style){

  defStyle = style;
  ImVec4(0.4f, 0.5f, 0.6f, 0.7f);
  style.Colors[2] = ImVec4(0.88f, 0.9f, 1.0f, 0.95f);
  style.Colors[7] = ImVec4(0.7f, 0.7f, 0.8f, 1.0f);
  style.Colors[8] = ImVec4(0.7f, 0.7f, 0.8f, 1.0f);
  style.Colors[9] = ImVec4(0.7f, 0.7f, 0.8f, 1.0f);
  style.Colors[19] = ImVec4(0.2f, 0.3f, 0.4f, 0.7f);
  style.Colors[20] = ImVec4(0.4f, 0.5f, 0.6f, 0.7f);
  style.Colors[21] = ImVec4(0.2f, 0.3f, 0.4f, 0.7f);
  style.Colors[22] = ImVec4(0.4f, 0.5f, 0.6f, 0.7f);
  style.Colors[23] = ImVec4(0.2f, 0.3f, 0.4f, 0.7f);
  style.WindowPadding =ImVec2(7,6);
  style.WindowRounding = 10.0f;
}

void player_Ui(bool &op){
  openPlayer = op;

  if(songsVec.size() > 0 && !stopButtonPressed){
    if(songsVec.at(currentSongINdex).isStatusStopped()){
      if(currentSongINdex < songsVec.size()-1){

        if(!shuffleSongs && !loop1Song){
          currentSongINdex++;
          songsVec.at(currentSongINdex).play();
        }else if(shuffleSongs && !loop1Song){
          srand (time(NULL));
          currentSongINdex = rand() % songsVec.size();
          songsVec.at(currentSongINdex).play();
        }
        else if(!shuffleSongs && loop1Song){
          songsVec.at(currentSongINdex).play();
        }
        else if(shuffleSongs && loop1Song){
          songsVec.at(currentSongINdex).play();
        }

      }else{
        if(loop1Song){
          songsVec.at(currentSongINdex).play();
        }else if(shuffleSongs){
          srand (time(NULL));
          currentSongINdex = rand() % songsVec.size();
          songsVec.at(currentSongINdex).play();
        }
        else
        songsVec.at(currentSongINdex).stop();
      }

    }
  }

  ImGuiStyle& style = ImGui::GetStyle();
  stylingMusicPlayer(style);

  if(openPlayer){
    showExternCtrl = false;
    MP_init();
    ImGui::SetNextWindowSize(ImVec2(535,380));
    ImGui::Begin("Music-Player",&openPlayer, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    if(songsVec.size() > 0){
      uiAfterLoading(style, op);
    }else{
      defPlayerUI(style, op);
    }

    ImGui::End();
  }


  style.Colors[2].x = 0.0f; style.Colors[2].y = 0.0f; style.Colors[2].z = 0.0f; style.Colors[2].w = 0.6f;
  style = defStyle;
}
void uiAfterLoading(ImGuiStyle& style, bool &openFlag)
{
  ImGui::BeginChild("MP-PLayer-Layout", ImVec2(525,200));
  ImVec2 p = ImGui::GetCursorScreenPos();
  ImGui::Image((void*)bkgId, ImVec2(522,200));
  ImGui::EndChild();
  ImGui::BeginChild("MP-PLayer-Layout");
  ImGui::GetWindowDrawList()->AddText(ImVec2(p.x + titleInc,p.y+180),IM_COL32(255, 255, 255, 255), songsVec.at(currentSongINdex).name.c_str());
  titleInc += 1.0;
  if(titleInc > 525.0f){
    titleInc = -320.0f;
  }
  ImGui::EndChild();
  ImGui::Text(" ");

  float f=0.0;
  style.FrameRounding = 20.0f;
  style.GrabRounding = style.FrameRounding;
  ImGui::PushItemWidth(520);
  style.Colors[40].x = 0.3f; style.Colors[40].y = 0.7f; style.Colors[40].z = 0.8f;
  style.FramePadding = ImVec2(4,0);
  ImGui::ProgressBar(songPlayOffsetBarValue, ImVec2(0.f,0.f),songsVec.at(currentSongINdex).getPlayOffset().c_str());
  style.FramePadding = ImVec2(4,3);
  ImGui::Text("");
  ImGui::Separator();

  ImGui::Dummy(ImVec2(0.0f, 20.0f));
  ImGui::Dummy(ImVec2(20.0f, 0.0f));ImGui::SameLine();
  style.Colors[21] = btnColor;
  if(ImGui::ImageButton((void*)loopIcon, ImVec2(20,20), ImVec2(0,0)))
  {
    if(loop1Song){
      loop1Song = false;
      btnColor = ImVec4(0.2 ,0.3 ,0.4, 0.7);
    }
    else{
      loop1Song = true;
      shuffleSongs = false;
      btnColor2 = ImVec4(0.2 ,0.3 ,0.4, 0.7);
      btnColor = ImVec4(0.2 ,0.3 ,0.4, 0.3);
    }
  }
  ImGui::SameLine();ImGui::Dummy(ImVec2(-12.0f, 0.0f));ImGui::SameLine();
  style.Colors[21] = btnColor2;
  if(ImGui::ImageButton((void*)shuffleIcon, ImVec2(25,20), ImVec2(0,0)))
  {
    if(shuffleSongs){
      shuffleSongs = false;
      btnColor2 = ImVec4(0.2 ,0.3 ,0.4, 0.7);
    }
    else{
      shuffleSongs = true;
      loop1Song = false;
      btnColor = ImVec4(0.2 ,0.3 ,0.4, 0.7);
      btnColor2 = ImVec4(0.2 ,0.3 ,0.4, 0.3);
    }
  }

  ImGui::SameLine();ImGui::Dummy(ImVec2(10.0f, 0.0f));ImGui::SameLine();
  style.Colors[21] = ImVec4(0.2 ,0.3 ,0.4, 0.7);
  if(ImGui::ImageButton((void*)prvIcon, ImVec2(30,25), ImVec2(0,0)))
  {
    stopButtonPressed = false;
    play_pauseIcon = pauseIcon;
    songsVec.at(currentSongINdex).stop();
    if(shuffleSongs){
      srand (time(NULL));
      currentSongINdex = rand() % songsVec.size();
    }
    else
    currentSongINdex--;
    if(currentSongINdex < 0){
      currentSongINdex = 0;
    }
    songsVec.at(currentSongINdex).play();
  }

  ImGui::SameLine();ImGui::Dummy(ImVec2(0.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)stopIcon, ImVec2(40,40), ImVec2(0,0)))
  {
    stopButtonPressed = true;
    songsVec.at(currentSongINdex).stop();pauseFlag = false;playFlag = true;resumeFlag = false;play_pauseIcon = playIcon;
  }

  ImGui::SameLine();ImGui::Dummy(ImVec2(-10.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)play_pauseIcon, ImVec2(50,50), ImVec2(0,0)))
  {
    stopButtonPressed = false;
    if(pauseFlag){
      songsVec.at(currentSongINdex).pause();
      pauseFlag = false;
      playFlag = true;
      resumeFlag = true;
      play_pauseIcon = playIcon;
    }
    else if(playFlag){
      if(resumeFlag)
      {
        resumeFlag = false;
        songsVec.at(currentSongINdex).resume();
      }
      else
      songsVec.at(currentSongINdex).play();
      pauseFlag = true;
      play_pauseIcon = pauseIcon;
      playFlag = false;


    }
    //songsVec.at(currentSongINdex).play();
  }

  ImGui::SameLine();ImGui::Dummy(ImVec2(0.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)nxtIcon, ImVec2(30,25), ImVec2(0,0)))
  {
    stopButtonPressed = false;
    play_pauseIcon = pauseIcon;
    songsVec.at(currentSongINdex).stop();
    if(shuffleSongs){
      srand (time(NULL));
      currentSongINdex = rand() % songsVec.size();
    }
    else
    currentSongINdex++;
    if(currentSongINdex > songsVec.size()-1){
      currentSongINdex = songsVec.size()-1;
    }
    songsVec.at(currentSongINdex).play();
  }

  ImGui::SameLine();ImGui::Dummy(ImVec2(10.0f, 0.0f));ImGui::SameLine();

  ImGui::Dummy(ImVec2(0.0f, -20.0f));ImGui::SameLine();

  ImGui::PushItemWidth(100);
  style.FramePadding = ImVec2(4,0);
  ImGui::SliderInt("##vol", &volumeInt, 0, 100, "");ImGui::SameLine();ImGui::Image((void*)volume, ImVec2(15,15), ImVec2(0,0));
  if(ImGui::IsItemClicked){
    songsVec.at(currentSongINdex).setVolume();
  }

  ImGui::TextColored(ctrlBcolors1,mp_hide_buttonTXT.c_str());
  if(ImGui::IsItemClicked()){
    openFlag = false;
    showExternCtrl = true;
    std::cout << "Closing MusicPlayer!." << '\n';
  }
  if(ImGui::IsItemHovered()){
    ctrlBcolors1.w = 1.0;
  }else
  ctrlBcolors1.w = 0.4;

  ImGui::SameLine();ImGui::Dummy(ImVec2(190.0f, 0.0f));ImGui::SameLine();
  ImGui::TextColored(ctrlBcolors2,mP_msg.c_str());ImGui::SameLine();ImGui::Dummy(ImVec2(220.0f, 0.0f));ImGui::SameLine();
  ImGui::TextColored(ctrlBcolors3,mp_update_buttonTXT.c_str());
  if(ImGui::IsItemClicked()){
    thread th{[](){
      convertMp3ToOGG();
      getDirContent("Songs/MP-Sources", songsNamesListOGG);
      for (size_t i = 0; i < songsNamesListOGG.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < songsVec.size(); j++) {
          if(songsNamesListOGG.at(i) == songsVec.at(j).name){
            found = true;
            break;
          }
        }
        if(!found){
          songsVec.push_back(Song("Songs/MP-Sources/",songsNamesListOGG.at(i)));
        }
      }
    }};

    th.detach();
  }
  if(ImGui::IsItemHovered()){
    ImGui::SetTooltip("Make sure your imported music names \ndoesn't contain brackets \'(), {}, [] \' or white spaces \nfor the the process to be done successfully.");
    ctrlBcolors3.w = 1.0;
  }else
  ctrlBcolors3.w = 0.4;
}

void defPlayerUI(ImGuiStyle& style, bool &openFlag)
{
  ImGui::BeginChild("MP-PLayer-Layout", ImVec2(525,200));
  ImVec2 p = ImGui::GetCursorScreenPos();
  ImGui::Image((void*)bkgId, ImVec2(522,200));
  ImGui::EndChild();
  ImGui::BeginChild("MP-PLayer-Layout");
  ImGui::GetWindowDrawList()->AddText(ImVec2(p.x + titleInc,p.y+180),IM_COL32(255, 255, 255, 255), "");
  titleInc += 1.0;
  if(titleInc > 525.0f){
    titleInc = -320.0f;
  }
  ImGui::EndChild();
  ImGui::Text(" ");

  float f=0.0;
  style.FrameRounding = 20.0f;
  style.GrabRounding = style.FrameRounding;
  ImGui::PushItemWidth(520);
  style.Colors[40].x = 0.3f; style.Colors[40].y = 0.7f; style.Colors[40].z = 0.8f;
  style.FramePadding = ImVec2(4,0);
  ImGui::ProgressBar(songPlayOffsetBarValue, ImVec2(0.f,0.f),"");
  style.FramePadding = ImVec2(4,3);
  ImGui::Text("");
  ImGui::Separator();

  ImGui::Dummy(ImVec2(0.0f, 20.0f));
  ImGui::Dummy(ImVec2(20.0f, 0.0f));ImGui::SameLine();ImGui::ImageButton((void*)loopIcon, ImVec2(20,20), ImVec2(0,0));ImGui::SameLine();ImGui::Dummy(ImVec2(-12.0f, 0.0f));ImGui::SameLine();
  ImGui::ImageButton((void*)shuffleIcon, ImVec2(25,20), ImVec2(0,0));ImGui::SameLine();ImGui::Dummy(ImVec2(10.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)prvIcon, ImVec2(30,25), ImVec2(0,0)))
  {

  }
  ImGui::SameLine();ImGui::Dummy(ImVec2(0.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)stopIcon, ImVec2(40,40), ImVec2(0,0))){}
  ImGui::SameLine();ImGui::Dummy(ImVec2(-10.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)play_pauseIcon, ImVec2(50,50), ImVec2(0,0)))
  {

  }

  ImGui::SameLine();ImGui::Dummy(ImVec2(0.0f, 0.0f));ImGui::SameLine();
  if(ImGui::ImageButton((void*)nxtIcon, ImVec2(30,25), ImVec2(0,0)))
  {

  }
  ImGui::SameLine();ImGui::Dummy(ImVec2(10.0f, 0.0f));ImGui::SameLine();

  ImGui::Dummy(ImVec2(0.0f, -20.0f));ImGui::SameLine();

  ImGui::PushItemWidth(100);
  style.FramePadding = ImVec2(4,0);
  ImGui::SliderInt("##vol", &volumeInt, 0, 100, false);ImGui::SameLine();ImGui::Image((void*)volume, ImVec2(15,15), ImVec2(0,0));

  ImGui::TextColored(ctrlBcolors1,mp_hide_buttonTXT.c_str());
  if(ImGui::IsItemClicked()){
    openFlag = false;
    showExternCtrl = true;
    std::cout << "Closing MusicPlayer!." << '\n';
  }
  if(ImGui::IsItemHovered()){
    ctrlBcolors1.w = 1.0;
  }else
  ctrlBcolors1.w = 0.4;

  ImGui::SameLine();ImGui::Dummy(ImVec2(190.0f, 0.0f));ImGui::SameLine();
  ImGui::TextColored(ctrlBcolors2,mP_Msg_Default.c_str());ImGui::SameLine();ImGui::Dummy(ImVec2(220.0f, 0.0f));ImGui::SameLine();
  ImGui::TextColored(ctrlBcolors3,mp_update_buttonTXT.c_str());
  if(ImGui::IsItemClicked()){
    thread th{[](){
      convertMp3ToOGG();
      getDirContent("Songs/MP-Sources", songsNamesListOGG);
      for (size_t i = 0; i < songsNamesListOGG.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < songsVec.size(); j++) {
          if(songsNamesListOGG.at(i) == songsVec.at(j).name){
            found = true;
            break;
          }
        }
        if(!found){
          songsVec.push_back(Song("Songs/MP-Sources/",songsNamesListOGG.at(i)));
        }
      }
    }};

    th.detach();
  }
  if(ImGui::IsItemHovered()){
    ImGui::SetTooltip("Make sure your imported music names \ndoesn't contain brackets \'(), {}, [] \' or white spaces \nfor the the process to be done successfully.");
    ctrlBcolors3.w = 1.0;
  }else
  ctrlBcolors3.w = 0.4;

}

void MP_ExternalControls(){
  if(showExternCtrl){

    ImGui::SameLine();ImGui::Dummy(ImVec2(SCR_WIDTH/3, 0.0f));
    if(ImGui::ImageButton((void*)prvIcon, ImVec2(10,13), ImVec2(0,0))){
      stopButtonPressed = false;
      play_pauseIcon = pauseIcon;
      songsVec.at(currentSongINdex).stop();
      if(shuffleSongs){
        srand (time(NULL));
        currentSongINdex = rand() % songsVec.size();
      }
      else
      currentSongINdex--;
      if(currentSongINdex < 0){
        currentSongINdex = 0;
      }
      songsVec.at(currentSongINdex).play();
    }ImGui::SameLine();
    if(ImGui::IsItemHovered()){
      if(currentSongINdex >= 1)
      ImGui::SetTooltip(songsVec.at(currentSongINdex-1).name.c_str());
      else
      ImGui::SetTooltip("This is the first song in the list.");
    }




    if(ImGui::ImageButton((void*)stopIcon, ImVec2(10,13), ImVec2(0,0))){
      stopButtonPressed = true;
      songsVec.at(currentSongINdex).stop();pauseFlag = false;playFlag = true;resumeFlag = false;play_pauseIcon = playIcon;
    }ImGui::SameLine();
    if(ImGui::IsItemHovered()){
      ImGui::SetTooltip(songsVec.at(currentSongINdex).name.c_str());
    }



    if(ImGui::ImageButton((void*)play_pauseIcon, ImVec2(13,13), ImVec2(0,0))){
      stopButtonPressed = false;
      if(pauseFlag){
        songsVec.at(currentSongINdex).pause();
        pauseFlag = false;
        playFlag = true;
        resumeFlag = true;
        play_pauseIcon = playIcon;
      }
      else if(playFlag){
        if(resumeFlag)
        {
          resumeFlag = false;
          songsVec.at(currentSongINdex).resume();
        }
        else
        songsVec.at(currentSongINdex).play();
        pauseFlag = true;
        play_pauseIcon = pauseIcon;
        playFlag = false;


      }
    }ImGui::SameLine();
    if(ImGui::IsItemHovered()){
      ImGui::SetTooltip(songsVec.at(currentSongINdex).name.c_str());
    }



    if(ImGui::ImageButton((void*)nxtIcon, ImVec2(10,13), ImVec2(0,0))){
      stopButtonPressed = false;
      play_pauseIcon = pauseIcon;
      songsVec.at(currentSongINdex).stop();
      if(shuffleSongs){
        srand (time(NULL));
        currentSongINdex = rand() % songsVec.size();
      }
      else
      currentSongINdex++;
      if(currentSongINdex > songsVec.size()-1){
        currentSongINdex = songsVec.size()-1;
      }
      songsVec.at(currentSongINdex).play();
    }
    if(ImGui::IsItemHovered()){
      if(currentSongINdex < songsVec.size()-1)
      ImGui::SetTooltip(songsVec.at(currentSongINdex+1).name.c_str());
      else
      ImGui::SetTooltip("This is the last song in the list.");
    }

  }
}

void atClose(){
  if(songsVec.size() > 0)
  songsVec.at(currentSongINdex).stop();
  std::cout << "At Closing :: Music Stops!." << '\n';
}
