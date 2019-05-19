#ifndef STYLEEDITOR_H
#define STYLEEDITOR_H

// Play it nice with Windows users. Notepad in 2017 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#define snprintf    _snprintf
#define vsnprintf   _vsnprintf
#else
#define IM_NEWLINE  "\n"
#endif

#include <stdint.h>
#include <assert.h>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <string>
using namespace std;

namespace boost {
  namespace serialization {
    class access;
  }
}

class PreffObj {
public:
  ImGuiStyle styleT;
  int style_idx;
  string font;
  float fontScale;

  // Serialization expects the object to have a default constructor
  PreffObj(ImGuiStyle& style, int sidx, string fnt, float fScale) {
    styleT = style;
    style_idx = sidx;
    font = fnt;
    fontScale = fScale;
  }
  PreffObj() {}

private:
  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<typename Archive>
  void serialize(Archive& ar, const unsigned version) {
    ar & styleT & style_idx & font & fontScale;
  }
};

void setStyleComponents(const char* fileName);
void setFONT();
void serializeDefaultStyle();
static void HelpMarker(const char* desc);
bool ShowStyleSelector(const char* label);
void ShowFontSelector(const char* label);
void ShowStyleEditor(ImGuiStyle* ref = NULL);

#endif //STYLEEDITOR_H
