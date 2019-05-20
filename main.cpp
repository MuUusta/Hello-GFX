/****************************************************************************
*                                                                           *
*                                                                           *
*  An OpenGL/ImGui/GLUT program for openGL tutorials                        *
*                                                                           *
*  -----------------------------------------------------------------------  *
*                                                                           *
*  5/19/2019 Mustafa Gamal (mg.mustafagamal@gmail.com)                      *
*                                                                           *
*                                                                           *
****************************************************************************/

///////////ignoring some compilation warnings///////////
#pragma GCC diagnostic ignored "-Wformat-security"    //
#pragma GCC diagnostic ignored "-Wconversion-null"    //
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"//
////////////////////////////////////////////////////////

////////////////////////////////////////////
#include <boost/algorithm/string.hpp>     //
#include <string.h>                       //
#include <thread>                         //
#include <time.h>                         //
#include <vector>                         //
#include <fstream>                        //
#include <iostream>                       //
using namespace std;                      //
////////////////////////////////////////////

//////////////////////////
#include <GL/glew.h>    //
#include <GL/freeglut.h>//
//////////////////////////

//////////////////////////////////////////
#include <glm/glm.hpp>                  //
#include <glm/gtc/matrix_transform.hpp> //
#include <glm/gtc/type_ptr.hpp>         //
//////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#ifdef WINDOWS                                                          //
#include <direct.h>                                                     //
#define GetCurrentDir _getcwd                                           //
#else                                                                   //
#include <unistd.h>                                                     //
#define GetCurrentDir getcwd                                            //
#endif                                                                  //
#include <SFML/Audio.hpp>                                               //
#include <X11/Xlib.h>                                                   //
//////////////////////////////////////////////////////////////////////////

//////////////////ImGui///////////////////
#include <imgui/imgui.h>                //
#include <imgui/imgui_impl_freeglut.h>  //
#include <imgui/imgui_impl_opengl2.h>   //
//////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER                                                                  //
#pragma warning (disable: 4505) // unreferenced local function has been removed  //
#endif                                                                           //
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////
#include <userData.hpp>      //
#include <textureLoading.h>  //
#include <filemanager.hpp>   //
#include <tutorialClass.h>   //
#include <fontLoader.hpp>    //
#include <globals.h>         //
#include <textEditor.h>      //
#include <blending.h>        //
#include <simpleLight.h>     //
#include <ImGui_Ui.h>        //
#include <intro.hpp>         //
#include <functions.h>       //
#include <common.h>          //
///////////////////////////////

int main(int argc, char* argv[])
{
    //Get directories content for the tutorial and set Screen resolution.
    tutorials = new Tutorial("OpenGL Tutorials", Both, tutorialArrayList, (sizeof(tutorialArrayList)/sizeof(*tutorialArrayList)));
    workingDirectory = GetCurrentWorkingDir();
    createTesterDirectories("testerFiles");
    setScrResolution();
    /****************************************/
    /*   Initialize GLUT and create window  */
    /****************************************/
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL );
    //glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( SCR_WIDTH, SCR_HEIGHT );
    main_window = glutCreateWindow( "Hello-GFX" );
    glutFullScreen();
    glutDisplayFunc(myGlutDisplay);
    glutDisplayFunc(intro_Display);
    glutReshapeFunc(myGlutReshape);
    glutMotionFunc(myGlutMotion);
    glutPassiveMotionFunc(myGlutPassiveMotion);
    glutMouseFunc(myGlutMouse);
    glutKeyboardFunc(myGlutKeyboard);
    glutSpecialFunc(processSpecialKeys);
    glutSpecialUpFunc(releaseKey);
    timer(0);
    glewInit();

    //init Pop-up Menus
    createPopupMenus();
    
    //Enable z-buferring
    glEnable(GL_DEPTH_TEST);
    //add fonts
    addFontList(fontListVector);
    //initialize ImGui
    ImGui_Initialization();
    //load models
    logl_modelsLoader();

    //load and play intro sound
    introSound.openFromFile("Sounds/impact.wav");
    playIntroSound();

    //Cleanup
    atexit(removeTesterDirectories);
    atexit(ImGui_CleanUp);
    atexit(de_allocator);
    atexit(atClose);
    atexit(serializeUserData);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}
