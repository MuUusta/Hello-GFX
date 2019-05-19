#ifndef GLOBALS_H
#define GLOBALS_H

/**************************** Intigers ******************************/
//-----------------------------------------------------------------//
int radioButtonIndex=NULL;
int multipleOutputs = 0,multipleOutputsIndex = 1;
int main_window, subWindow1, subWindow2, subWindow3;

// Pop up menu identifiers
int fillMenu, shrinkMenu, mainMenu, colorMenu, fontMenu, strokeFontMenu;
//border between subwindows
int border = 6;
int xOrigin = -1;
// menu status
int menuFlag = 0;
// variables to compute frames per second
int frame, fpsRework;
long timeFPS, timebase;
static float fpsFloat;
/****** Chars *******/
char fps[50] = {"FPS: 00.00"};
/***************************************************************/

/************************ Floats ******************************/
//-----------------------------------------------------------//
float sphere_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float torus_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };
float SCR_HEIGHT,SCR_WIDTH,objRed=1.0,objGreen=1.0,objBlue=1.0,angle=0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f, ly = 0.0f;
// XZ position of the camera
float x=0.0f,z=5.0f, y = 1.75f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
float xy_aspect;
// color for the nose
float red = 1.0f, blue=0.5f, green=0.5f;
// scale of snowman
float scale = 1.0f;
/***********************************************************/

/********** Miscellaneous global variables **********/
//--------------------------------------------------//
GLfloat lights_rotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
bool show_text = true, openTutorialsHeaders = true, renderLOGL_LCwindow=false;
bool useMouseForImGui = true,windowResized = false, firstUseFlag, checkUserData = true;
bool userDataDeserialized = false;
static ImVec4 colorBG = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
string tutorialArrayList[] = {"light-house-3d", "fog-tut", "blending-tut", "light-tut", "pipe-line-tut", "learnOpenGL-tut"};
static char searchStr[512] = {""};
ImVec2 teWindowSize;
vector<string> searchResults;
string searchTMP;
Tutorial *tutorials;
int tutorialsNumber = 68;
UserData userDataObj;
static char usrName[256] = "";
vector<MyFont> fontListVector;
/***************************************************/

/********************************ImGui Variables*************************************/
bool texturesInitFlag=false,wrappedText = false;
bool openMPlayer = false;
bool resetScrollY = false, hyperlinkHovered = false;
static bool showMainWindow = true;
static bool fullScrFlag = true;
static bool open_full_edit_menu = false;
static bool openTEflag = false;
static bool openResourcesFlag;
static bool copyLearnOpenglFolderFlag = false, copyResourcesFolderFlag = false;
static float window_scale = 1.0f;
string errMsg;
ImVec4 stringColor = ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f);
float imGui_width, imGui_height;
/**************************************************************************************/

// default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;
void *strfont = GLUT_STROKE_ROMAN;

/****************** Defines *****************/
//-----------------------------------------//
// Constant definitions for Menus
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2

#define SHRINK 1
#define NORMAL 2

#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7
#define INT_GLUT_STROKE_ROMAN  8
#define INT_GLUT_STROKE_MONO_ROMAN  9

/****** Functions Headers *******/
//-----------------------------//
void timer(int);
std::string GetCurrentWorkingDir( void );
void setScrResolution();
void drawSnowMan();
void computePos(float deltaMove);
void computeDir(float deltaAngle);
void renderBitmapString(float xx,float yy,float zz,void *font,char *string);
void restorePerspectiveProjection();
void setOrthographicProjection();
void fps_counter();
void processMenuStatus(int status, int x, int y);
void processMainMenu(int option);
void processFillMenu(int option);
void processShrinkMenu(int option);
void processColorMenu(int option);
void processFontMenu(int option);
void createPopupMenus();
void destroyPopupMenus();
void myGlutKeyboard(unsigned char Key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void releaseKey(int key, int x, int y);
void myGlutMenu( int value );
void myGlutIdle();
void myGlutMouse(int button, int button_state, int x, int y );
void myGlutMotion(int x, int y );
void myGlutReshape( int x, int y );
void myGlutDisplay();
void setProjection(int w1, int h1);
void renderScene2();
void renderSceneTMP();
void renderScenesw1();
void renderScenesw2();
void renderScenesw3();
void renderSceneAll();
void destroyWindows();
void init_glut();
void create_subWindows();
void reset_mainWindow();
void myPerspective();
void display_tut_1();
void display_tut_2();
void display_tut_3();
void display_tut_4();
void display_tut_5();
void display_tut_6();
void blankDisplay();
void resetSceneVars();
void de_allocator();
void serializeUserData();
void deSerializeUserData();
void applyTutorialsFunc(int index);
void setCursor();
/////imGUi funcs
static void ImGui_ImplFreeGLUT_UpdateKeyboardMods();
void showHotKeysMenu();
void render_Main_Tutorials_Window();
void menuBar_After_MW_Hidden();
void toggleTextModeBT();
void multipleOuts_RBs();
void contorlersWindow();
void searchingMenuItem();
void immediate_Mode_Tutorials_List();
void retained_Mode_Tutorials_List();
void mainWindow_LeftPane();
void mainWindow_RightPane();
void rightPane_CodeTab();
void start_end_Tutorial_Buttons();
void view_Output_Button();
void build_Test_Proj();
void run_Test_Proj();
static void HelpMarker(const char* desc);
void renderTextEditor();
void ShowFontSelector(const char* label, const char* helpMsg);
void Show_Fps_mouse_Pos();
void modalAlert(const char *name, const char* msg);
void ImGui_Initialization();
void ImGui_CleanUp();
void logl_LC_window();
void imGui_display_code();
void render_ImGui();
void simpleLightMenu(bool enable, bool text);
void initializeTextures();
void saveAllFunc(string folder);
void exportAsProject();
void addFuncToTextEditor();
void addFileToTextEditor();
void textEditorConsolLog();
void firstUseModalAlert();
void currentTutRateModal();
void resetFunc();
void viewTutorialImages(int i);
void viewTutorialContent();
void viewUserInfo();
void date_Time_Display();
void handleUserData();
/*******************************/


#endif //GLOBALS_H
