//ignoring some compilation warnings/////////////////////
#pragma GCC diagnostic ignored "-Wformat-security"     //
#pragma GCC diagnostic ignored "-Wconversion-null"     //
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" //
/////////////////////////////////////////////////////////

///////////////////ImGui/////////////////
#include <imgui/imgui.h>               //
#include <imgui/imgui_impl_freeglut.h> //
#include <imgui/imgui_impl_opengl2.h>  //
/////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif
////

#include <resources.hpp>
#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

string computerGFX[] = {"https://www.tutorialspoint.com/computer_graphics/index.htm",
                        "https://www.wisdomjobs.com/e-university/computer-graphics-tutorial-342.html",
                        "https://www.javatpoint.com/computer-graphics-tutorial"};

string aboutOpenGL[] = { "https://www.codeproject.com/Articles/771225/Learning-Modern-OpenGL",
                         "https://medium.com/@dmitrygz/what-is-opengl-and-how-to-start-learning-it-34f19cfa219f",
                         "https://medium.com/@dmitrygz/opengl-learning-in-2018-d556d96d7e7",
                         "https://en.wikipedia.org/wiki/OpenGL",
                         "https://whatis.techtarget.com/definition/OpenGL-Open-Graphics-Library",
                         "https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs"};

string ytChannelsName[] = {"TheChernoProject","Jamie King","thebennybox","thecplusplusguy","ThinMatrix","MakingGamesWithBen","Anh Huu Pham Minh"};
string youTube[] = {"https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2",
                    "https://www.youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY",
                    "https://www.youtube.com/playlist?list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh",
                    "https://www.youtube.com/playlist?list=PL0AB023E769342AFE",
                    "https://www.youtube.com/playlist?list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP",
                    "https://www.youtube.com/playlist?list=PLSPw4ASQYyymu3PfG9gxywSPghnSMiOAW",
                    "https://www.youtube.com/playlist?list=PLy8AlY2Nj2g5UWgE5r7gPgrLq9YPihxkw"};

string websites[] = {"http://www.lighthouse3d.com/tutorials/glut-tutorial/",
                     "https://learnopengl.com/",
                     "http://ogldev.atspace.co.uk/",
                     "http://www.songho.ca/opengl/index.html",
                     "http://nehe.gamedev.net/",
                     "http://users.polytech.unice.fr/~buffa/cours/synthese_image/DOCS/Tutoriaux/Nehe/opengl.htm",
                     "http://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html",
                     "https://open.gl/",
                     "http://www.opengl-tutorial.org/",
                     "https://www.khronos.org/opengl/wiki/Main_Page",
                     "https://en.wikibooks.org/wiki/OpenGL_Programming",
                     "http://www.davidbishop.org/oglmeta",
                     "http://videotutorialsrock.com/",
                     "https://www.cse.msu.edu/~cse872/",
                     "http://www.real3dtutorials.com/index.php",
                     "http://www.lousodrome.net/opengl/",
                     "https://www.tomdalling.com/blog/modern-opengl/",
                     "http://www.mbsoftworks.sk/tutorials/opengl3/",
                     "https://www.opengl.org/sdk/docs/tutorials/TyphoonLabs/",
                     "http://math.hws.edu/bridgeman/courses/324/s06/doc/opengl.html",
                     "http://www.swiftless.com/",
                     "http://sol.gfxile.net/tutorials.html",
                     "http://antongerdelan.net/opengl/",
                     "https://paroj.github.io/gltut/"};

string books[] = {  "OpenGL Superbible: Comprehensive Tutorial and Reference (7th Edition)",
                    "Graphics Shaders: Theory and Practice, Second Edition",
                    "OpenGL Programming Guide: The Official Guide to Learning OpenGL, Versions 3.0 and 3.1 (7th Edition)",
                    "Computer Graphics: Principles and Practice (3rd Edition)",
                    "Fundamentals of Computer Graphics 3rd Edition",
                    "3D Math Primer For Graphics and Game Development (Wordware Game Math Library) 1st Edition",
                    "Interactive Computer Graphics: A Top-Down Approach With Shader-Based Opengl 6th Edition",
                    "Computer Graphics Programming in OpenGL with JAVA"};

string glutSpecs[] = {"https://www.opengl.org/resources/libraries/glut/glut-3.spec.pdf"};

string openGLfunctions[] = {"https://docs.microsoft.com/en-us/windows/desktop/opengl/gl-functions",
                            "https://www.khronos.org/registry/OpenGL-Refpages/gl4/"};

string glCinstallation[] = {"http://web.eecs.umich.edu/~sugih/courses/eecs487/glut-howto/",
                            "http://kiwwito.com/installing-opengl-glut-libraries-in-ubuntu/"};

string tmpHL="";

ImVec4 cGFXrCol[(sizeof(computerGFX)/sizeof(*computerGFX))];
ImVec4 aOGLrCol[(sizeof(aboutOpenGL)/sizeof(*aboutOpenGL))];
ImVec4 yTrCol[(sizeof(youTube)/sizeof(*youTube))];
ImVec4 wSrCol[(sizeof(websites)/sizeof(*websites))];
ImVec4 bCol[(sizeof(books)/sizeof(*books))];
ImVec4 gSrCol[(sizeof(glutSpecs)/sizeof(*glutSpecs))];
ImVec4 oFrCol[(sizeof(openGLfunctions)/sizeof(*openGLfunctions))];
ImVec4 gLCrCol[(sizeof(glCinstallation)/sizeof(*glCinstallation))];

void resourcesMenu(bool &open){
  ImGuiStyle& style = ImGui::GetStyle();
  if(open){
    ImGui::Begin("Resources##Menu", &open);

    ImGui::BulletText("Computer Graphics Tutoials:");
    ImGui::Text("------------------------------\n");
    for (size_t i = 0; i < (sizeof(computerGFX)/sizeof(*computerGFX)); i++) {
      ImGui::TextColored(cGFXrCol[i],computerGFX[i].c_str());
      if(ImGui::IsItemHovered())
      {
        cGFXrCol[i] = ImVec4(0.3, 1.3, 0.3, 1.0);
      }else{
        cGFXrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + computerGFX[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("Read About OpenGL:");
    ImGui::Text("---------------------\n");
    for (size_t i = 0; i < (sizeof(aboutOpenGL)/sizeof(*aboutOpenGL)); i++) {
      ImGui::TextColored(aOGLrCol[i],aboutOpenGL[i].c_str());
      if(ImGui::IsItemHovered())
      {
        aOGLrCol[i] = ImVec4(0.3, 1.3, 0.3, 1.0);
      }else{
        aOGLrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + aboutOpenGL[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("OpenGl YouTube Tutorials:");
    ImGui::Text("----------------------------\n");
    for (size_t i = 0; i < (sizeof(youTube)/sizeof(*youTube)); i++) {
      ImGui::TextColored(yTrCol[i],(ytChannelsName[i]+"-> "+youTube[i]).c_str());
      if(ImGui::IsItemHovered())
      {
        yTrCol[i] = ImVec4(1.0, 0.3, 0.3, 1.0);
      }else{
        yTrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + youTube[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("OpenGl Website Tutorials:");
    ImGui::Text("----------------------------\n");
    for (size_t i = 0; i < (sizeof(websites)/sizeof(*websites)); i++) {
      ImGui::TextColored(wSrCol[i],websites[i].c_str());
      if(ImGui::IsItemHovered())
      {
        wSrCol[i] = ImVec4(0.3, 0.3, 1.0, 1.0);
      }else{
        wSrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + websites[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("OpenGl Books:");
    ImGui::Text("----------------\n");
    for (size_t i = 0; i < (sizeof(books)/sizeof(*books)); i++) {
      ImGui::TextColored(bCol[i],books[i].c_str());
      if(ImGui::IsItemHovered())
      {
        bCol[i] = ImVec4(0.5, 0.5, 0.5, 1.0);
      }else{
        bCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open https://www.google.com/search?q='" + books[i]+"'";system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("Glut Specs:");
    ImGui::Text("--------------\n");
    for (size_t i = 0; i < (sizeof(glutSpecs)/sizeof(*glutSpecs)); i++) {
      ImGui::TextColored(gSrCol[i],glutSpecs[i].c_str());
      if(ImGui::IsItemHovered())
      {
        gSrCol[i] = ImVec4(0.3, 1.3, 0.3, 1.0);
      }else{
        gSrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + glutSpecs[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("OpenGL Functions:");
    ImGui::Text("--------------------\n");
    for (size_t i = 0; i < (sizeof(openGLfunctions)/sizeof(*openGLfunctions)); i++) {
      ImGui::TextColored(oFrCol[i],openGLfunctions[i].c_str());
      if(ImGui::IsItemHovered())
      {
        oFrCol[i] = ImVec4(0.3, 1.3, 0.3, 1.0);
      }else{
        oFrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + openGLfunctions[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::BulletText("OpenGL/GLUT Installation:");
    ImGui::Text("----------------------------\n");
    for (size_t i = 0; i < (sizeof(glCinstallation)/sizeof(*glCinstallation)); i++) {
      ImGui::TextColored(gLCrCol[i],glCinstallation[i].c_str());
      if(ImGui::IsItemHovered())
      {
        gLCrCol[i] = ImVec4(0.3, 1.3, 0.3, 1.0);
      }else{
        gLCrCol[i] = style.Colors[0];
      }

      if (ImGui::IsItemClicked()){tmpHL = "xdg-open " + glCinstallation[i];system(tmpHL.c_str());}
    }
    ImGui::Text(" ");



    ImGui::End();
  }
}
