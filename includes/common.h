#ifndef COMMON_H
#define COMMON_H

//////////////////ImGui///////////////////
#include <imgui/imgui.h>                //
#include <imgui/imgui_impl_freeglut.h>  //
#include <imgui/imgui_impl_opengl2.h>   //
//////////////////////////////////////////
#include <string>
using namespace std;

extern string workingDirectory;
extern float SCR_HEIGHT,SCR_WIDTH;
extern bool show_text;
extern ImVec4 stringColor;
extern void fps_counter();
extern void render_ImGui();
extern int tutorialsNumber;

#endif //COMMON_H
