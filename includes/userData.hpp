#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <common.h>
using namespace std;

//int tutorialsNumber;

namespace boost {
  namespace serialization {
    class access;
  }
}


class TutorialStatus{
public:
  TutorialStatus(){}
  TutorialStatus(int idx, int stat){
    index = idx; status = stat;
  }
  int index, status;

  TutorialStatus& operator=(TutorialStatus other)
  {
    cout << "copy assignment of TutorialStatus\n";
    swap(index, other.index);
    swap(status, other.status);
    return *this;
  }

  bool operator==(const TutorialStatus& o) const {
    return index == o.index && status == o.status;
  }
  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<typename Archive>
  void serialize(Archive& ar, const unsigned version) {
    ar & index & status;  // Simply serialize the data members of Obj
  }
};

class H_GFX_Duration{
public:
  int days,hours,minutes,seconds;
  H_GFX_Duration(){}
  H_GFX_Duration(int d, int h, int m, int s){
    days = d; hours = h; minutes = m; seconds = s;
  }
  int getDurationInSeconds();

  H_GFX_Duration& operator=(H_GFX_Duration other)
  {
    cout << "copy assignment of H_GFX_Duration\n";
    swap(days, other.days);
    swap(hours, other.hours);
    swap(minutes, other.minutes);
    swap(seconds, other.seconds);
    return *this;
  }

  bool operator==(const H_GFX_Duration& o) const {
    return days == o.days && hours == o.hours && minutes == o.minutes && seconds == o.seconds;
  }
  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<typename Archive>
  void serialize(Archive& ar, const unsigned version) {
    ar & days & hours & minutes & seconds;  // Simply serialize the data members of Obj
  }
};

class UserData{
public:
  vector<TutorialStatus> allTutsStatus;
  vector<H_GFX_Duration> durationsVec;
  int tutorailCompetence;
  UserData();
  ~UserData();

  bool isFirstUsage();

  //setters
  void setUserName(string name);
  void setLastTutDone(int index, int rate);
  void setLastTutOpened(int index, bool shwTxt);
  void setNextTutSuggestion();
  void setCurrentTut(int index);
  void setCurrentTutStatus(int stat);
  void setTutorialsTitles(vector<string> titles);
  void Append_To_NeedReviewTuts(int index);
  void set_Current_Tut_Start_Time();
  void set_very_First_App_Use_Time();

  //getters
  string getUserName();
  string getLastTutDone();
  string getLastTutOpened();
  string getNextTutSuggestion();
  string getCurrentTut();
  string getCurrentTutStatus();
  vector<string> getNeedReviewTuts();
  string get_very_First_App_Use_Time();
  string get_Done_Tut_Start_Time();
  string get_Current_Tut_Start_Time();
  string get_Done_Tut_Finish_Time();
  string getDoneTutDuration();
  string getRemainingDuration();
  float getProgressPercent();
  int getLastTutOpenedIndex(float &scrWidth, float origScreenWidth, bool &shwTxt);

  UserData& operator=(UserData other)
  {
    cout << "copy assignment of UserData\n";
    swap(allTutsStatus, other.allTutsStatus);               swap(durationsVec, other.durationsVec);
    swap(tutorailCompetence, other.tutorailCompetence);     swap(userName, other.userName);
    swap(lastTutDone, other.lastTutDone);                   swap(lastTutOpened, other.lastTutOpened);
    swap(nextTutSuggestion, other.nextTutSuggestion);       swap(currentTut, other.currentTut);
    swap(dontTutDuration, other.dontTutDuration);           swap(remainingDuration, other.remainingDuration);
    swap(tutorialsTitles, other.tutorialsTitles);           swap(needReviewTuts, other.needReviewTuts);
    swap(lastTutOpenedIndex, other.lastTutOpenedIndex);     swap(nextTutSuggestionIndex, other.nextTutSuggestionIndex);
    swap(lastTutDoneIndex, other.lastTutDoneIndex);         swap(currentTutIndex, other.currentTutIndex);
    swap(currentTutStatus, other.currentTutStatus);         swap(tut_Confidence_Rate, other.tut_Confidence_Rate);
    swap(numOfTutsDone, other.numOfTutsDone);               swap(tutsNum, other.tutsNum);
    swap(progressPercent, other.progressPercent);           swap(durationInSeconds, other.durationInSeconds);
    swap(show_Tut_Text, other.show_Tut_Text);               swap(very_First_App_Use_Time, other.very_First_App_Use_Time);
    swap(done_Tut_Start_Time, other.done_Tut_Start_Time);   swap(current_Tut_Start_Time, other.current_Tut_Start_Time);
    swap(done_Tut_Finish_Time, other.done_Tut_Finish_Time);

    return *this;
  }

private:
  //Data Members
  string userName = "User";
  string lastTutDone = "None", lastTutOpened = "None", nextTutSuggestion = "None", currentTut = "Nothing Yet!";
  string dontTutDuration = "00.", remainingDuration = "Average estimated learning\nduration is: 68 days.";
  vector<string> tutorialsTitles, needReviewTuts;
  int lastTutOpenedIndex = 0, nextTutSuggestionIndex = 1, lastTutDoneIndex = -1, currentTutIndex = -1, currentTutStatus = -1;
  int tut_Confidence_Rate, numOfTutsDone = 0, tutsNum = 66, progressPercent = 0;
  int durationInSeconds;
  bool show_Tut_Text;
  time_t very_First_App_Use_Time, done_Tut_Start_Time, current_Tut_Start_Time, done_Tut_Finish_Time;

  //Functions
  time_t calculate_Time_Now();
  void calculate_Duration();
  void calculate_RemainingTime();
  void text_Or_Output_Adjustment(float &scrWidth, float origScreenWidth);
  inline bool isUserDataFileOnDisk(const string& name);

  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<typename Archive>
  void serialize(Archive& ar, const unsigned version) {
    ar & allTutsStatus & tutorailCompetence & userName & lastTutDone & lastTutOpened & nextTutSuggestion & currentTut & tutorialsTitles & needReviewTuts
    & lastTutOpenedIndex & nextTutSuggestionIndex & lastTutDoneIndex & currentTutIndex & currentTutStatus & tut_Confidence_Rate & numOfTutsDone & tutsNum
    & progressPercent & very_First_App_Use_Time & done_Tut_Start_Time & current_Tut_Start_Time & done_Tut_Finish_Time & dontTutDuration & durationInSeconds
    & remainingDuration & durationsVec & show_Tut_Text;
  }

};

#endif //USERDATA_HPP
