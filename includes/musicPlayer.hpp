#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

class Song{
private:
    sf::SoundBuffer buffer;
    sf::Sound soundCo;

public:
  string name;
  string url;
  float duration;
  float pauseTime;
  int seconds=0, minutes=0, tmpInt;
  bool reset;
  Song(string url, string name);
  Song(){}
  ~Song();
  void play();
  void stop();
  void pause();
  void resume();
  void setVolume();
  bool isStatusStopped();
  string getPlayOffset();
};

GLuint loadMPTextures(const char *path);
void loadPLayerImages();
void loadSongs(string msg);
void generateTitles();
void updateSongs();
void convertMp3ToOGG();
void player_Ui(bool &op);
void uiAfterLoading(ImGuiStyle& style, bool &openFlag);
void defPlayerUI(ImGuiStyle& style, bool &openFlag);
void atClose();
void MP_ExternalControls();

#endif //MUSICPLAYER_HPP
