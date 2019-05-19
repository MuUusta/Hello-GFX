#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <userData.hpp>


UserData::UserData(){
  if(isFirstUsage()){
    for (size_t i = 0; i < tutorialsNumber; i++) {
      allTutsStatus.push_back(TutorialStatus(i, -1));
    }
  }
}

UserData::~UserData(){

}

////////////public functions/////////////
bool UserData::isFirstUsage(){
  if(isUserDataFileOnDisk("Configurations/UserInfo.ser"))
    {
      return false;
    }
  else
    {
      this->very_First_App_Use_Time = calculate_Time_Now();
      return true;
    }
}

//setters
void UserData::setUserName(string name){
  this->userName = name;
}

void UserData::setLastTutDone(int index, int rate){
  this->lastTutDone = this->tutorialsTitles.at(index);
  this->tut_Confidence_Rate = rate;
  this->lastTutDoneIndex = index;
  this->numOfTutsDone++;
  this->done_Tut_Start_Time = this->current_Tut_Start_Time;
  this->done_Tut_Finish_Time = calculate_Time_Now();
  calculate_Duration();
}

void UserData::setLastTutOpened(int index, bool shwTxt){
  if(tutorialsTitles.size() > 0){
    this->lastTutOpened = tutorialsTitles.at(index);
    this->lastTutOpenedIndex = index;
  }
  this->show_Tut_Text = shwTxt;
}
  int tmpInt;
void UserData::setNextTutSuggestion(){
  for (size_t i = 0; i < allTutsStatus.size(); i++) {
    if(allTutsStatus.at(i).status != 1 && tutorialsTitles.size() > 0){
      //tmpInt = i;
      nextTutSuggestion = tutorialsTitles.at(i);
      break;
    }
  }
}

void UserData::setCurrentTut(int index){
  this->currentTut = tutorialsTitles.at(index);
  this->currentTutIndex = index;
}

void UserData::setCurrentTutStatus(int stat){
  this->currentTutStatus = stat;
  allTutsStatus.at(currentTutIndex).status = stat;

  if(stat == 1 && tutorailCompetence < 7){
    Append_To_NeedReviewTuts(lastTutDoneIndex);
    calculate_RemainingTime();
    return;
  }else if(stat == 1){
    calculate_RemainingTime();
    return;
  }

}

void UserData::setTutorialsTitles(vector<string> titles){
  this->tutorialsTitles = titles;
}

void UserData::Append_To_NeedReviewTuts(int index){
  this->needReviewTuts.push_back(tutorialsTitles.at(index));
}

void UserData::set_Current_Tut_Start_Time(){
  this->current_Tut_Start_Time = calculate_Time_Now();
}

void UserData::set_very_First_App_Use_Time(){
  very_First_App_Use_Time = calculate_Time_Now();
}

//getters
string UserData::getUserName(){
  return this->userName;
}

string UserData::getLastTutDone(){
  return this->lastTutDone;
}

string UserData::getLastTutOpened(){
  return this->lastTutOpened;
}

string UserData::getNextTutSuggestion(){
  return this->nextTutSuggestion;
}

string UserData::getCurrentTut(){
  return this->currentTut;
}

string UserData::getCurrentTutStatus(){
  if(this->currentTutStatus == -1)
    return "Inactive";
  else if(this->currentTutStatus == 0)
    return "Started";
  else
    return "Done";
}

vector<string> UserData::getNeedReviewTuts(){
  return this->needReviewTuts;
}

string UserData::get_very_First_App_Use_Time(){
  string s = ctime(&very_First_App_Use_Time);
  return s;
}

string UserData::get_Done_Tut_Start_Time(){
  string s = "";
  if(numOfTutsDone == 0)
    s = "- - - 00:00:00 ----";
  else
    s = ctime(&done_Tut_Start_Time);
  return s;
}

string UserData::get_Current_Tut_Start_Time(){
  string s = ctime(&current_Tut_Start_Time);
  return s;
}

string UserData::get_Done_Tut_Finish_Time(){
  string s = "";
  if(numOfTutsDone == 0)
  s = "- - - 00:00:00 ----";
  else if(numOfTutsDone == 0 && currentTutStatus == 0)
  s = "- - - 00:00:00 ----";
  else
  s = s = ctime(&done_Tut_Finish_Time);
  return s;
}

string UserData::getDoneTutDuration(){
  return this->dontTutDuration;
}

float UserData::getProgressPercent(){
  float p = ((float)numOfTutsDone / (float)tutsNum) ;
  progressPercent = p * 100.0f;
  return p;
}

int UserData::getLastTutOpenedIndex(float &scrWidth, float origScreenWidth, bool &shwTxt){
  text_Or_Output_Adjustment(scrWidth, origScreenWidth);
  shwTxt = show_Tut_Text;
  return this->lastTutOpenedIndex;
}

string UserData::getRemainingDuration(){
  return this->remainingDuration;
}

////////////private functions/////////////
time_t UserData::calculate_Time_Now(){
  auto now = std::chrono::system_clock::now();
  time_t t = std::chrono::system_clock::to_time_t(now);
  return t;
}

void UserData::calculate_Duration(){
  int seconds = (int)difftime( done_Tut_Finish_Time, done_Tut_Start_Time );
  durationInSeconds = seconds;
  int days = seconds / 86400;
  seconds -= days * 86400;
  int hours = seconds / 3600;
  seconds -= hours * 3600;
  int minutes = seconds / 60;
  seconds -= minutes * 60;

  dontTutDuration = to_string(days) + "d - ";
  dontTutDuration += to_string(hours) + "h:";
  dontTutDuration += to_string(minutes) + "m:";
  dontTutDuration += to_string(seconds) + "s.";

  durationsVec.push_back(H_GFX_Duration(days, hours, minutes, seconds));
}

void UserData::calculate_RemainingTime(){
  int tutNumTMP = 0;
  for (int i = 0; i < allTutsStatus.size(); i++) {
    if(allTutsStatus.at(i).status != 1)
    tutNumTMP++;
  }

  if(durationsVec.size() > 0){
    int tmp = 0;
    for (size_t i = 0; i < durationsVec.size(); i++) {
      tmp += durationsVec.at(i).getDurationInSeconds();
    }
    tmp /= durationsVec.size();
    durationInSeconds = tmp;
  }

  durationInSeconds *= tutNumTMP;
  int days = durationInSeconds / 86400;
  durationInSeconds -= days * 86400;
  int hours = durationInSeconds / 3600;
  durationInSeconds -= hours * 3600;
  int minutes = durationInSeconds / 60;
  durationInSeconds -= minutes * 60;

  remainingDuration = "At this rate, you are\ngoing to finish learning\nthese tutorials in: \n";
  remainingDuration += to_string(days) + "d - ";
  remainingDuration += to_string(hours) + "h:";
  remainingDuration += to_string(minutes) + "m:";
  remainingDuration += to_string(durationInSeconds) + "s.";

}

void UserData::text_Or_Output_Adjustment(float &scrWidth, float origScreenWidth){
  if(show_Tut_Text){
    scrWidth = origScreenWidth;
  }else{
    scrWidth = 235;
  }
}

inline bool UserData::isUserDataFileOnDisk(const string& name){
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

int H_GFX_Duration::getDurationInSeconds(){
  int finalSeconds;
  finalSeconds = this->days * 86400;
  finalSeconds += this->hours * 3600;
  finalSeconds += this->minutes * 60;
  finalSeconds += this->seconds;

  return finalSeconds;
}
