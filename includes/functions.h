#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <imGui_Functions.h>
/***********************************************************************/
void timer(int)
{
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, 0);
}

std::string GetCurrentWorkingDir( void )
{
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

void setScrResolution()
{
  Display* d = XOpenDisplay(NULL);
  Screen*  s = DefaultScreenOfDisplay(d);
  SCR_HEIGHT =  s->height;
  SCR_WIDTH = s->width;
}

void drawSnowMan()
{

  glScalef(scale, scale, scale);
  glColor3f(1.0f, 1.0f, 1.0f);

  // Draw Body
  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);

  // Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);

  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();

  // Draw Nose
  if(radioButtonIndex < 10){
    glColor3f(1.0f, 0.5f , 0.5f);
    glutSolidCone(0.08f,0.5f,10,2);
  }else{
    glColor3f(red, green, blue);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
  }
  glColor3f(1.0f, 1.0f, 1.0f);
}

void computePos(float deltaMove)
{

  x += deltaMove * lx * 0.1f;
  z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle)
{

  angle += deltaAngle;
  lx = sin(angle);
  lz = -cos(angle);
}

void renderBitmapString(float xx,float yy,float zz,void *font,char *string)
{

  char *c;
  glRasterPos3f(xx, yy,zz);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }

}

void renderStrokeFontString(float x,float y,float z,void *font,char *string)
{
  char *c;
  glPushMatrix();
  glTranslatef(x, y,z);
  glScalef(0.002f, 0.002f, 0.002f);
  for (c=string; *c != '\0'; c++) {
    glutStrokeCharacter(font, *c);
  }
  glPopMatrix();
}

void restorePerspectiveProjection()
{

  glMatrixMode(GL_PROJECTION);
  // restore previous projection matrix
  glPopMatrix();

  // get back to modelview mode
  glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection()
{

  // switch to projection mode
  glMatrixMode(GL_PROJECTION);

  // save previous matrix which contains the
  //settings for the perspective projection
  glPushMatrix();

  // reset matrix
  glLoadIdentity();

  // set a 2D orthographic projection
  gluOrtho2D(0, SCR_WIDTH, SCR_HEIGHT, 0);

  // switch back to modelview mode
  glMatrixMode(GL_MODELVIEW);
}

void fps_counter()
{
  // Code to compute frames per second
  frame++;

  timeFPS=glutGet(GLUT_ELAPSED_TIME);
  if (timeFPS - timebase > 1000) {
    sprintf(fps,"FPS:%4.2f",frame*1000.0/(timeFPS-timebase));
    fpsFloat = frame*1000.0/(timeFPS-timebase);
    //framesPerSecond->set_text(fps);
    timebase = timeFPS;
    frame = 0;
  }

  if(radioButtonIndex == 22){
    // Code to display a string (fps) with bitmap fonts
    setOrthographicProjection();

    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.8,0.8,0.8);
    renderBitmapString(SCR_WIDTH-100,30,0,GLUT_BITMAP_HELVETICA_18,fps);
    glPopMatrix();

    restorePerspectiveProjection();
  }
}

// -----------------------------------
//             MENUS
// -----------------------------------

void processMenuStatus(int status, int x, int y)
{

  if (status == GLUT_MENU_IN_USE){
    menuFlag = 1;
  }
  else{
    menuFlag = 0;

  }

}

void processMainMenu(int option)
{
  // nothing to do in here
  // all actions are for submenus
}

void processFillMenu(int option)
{
  switch (option) {
    case FILL: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    case LINE: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);; break;
  }
}

void processShrinkMenu(int option)
{
  switch (option) {
    case SHRINK: scale = 0.5f; break;
    case NORMAL: scale = 1.0f; break;
  }
}

void processColorMenu(int option)
{
  switch (option) {
    case RED :
    red = 1.0f;
    green = 0.0f;
    blue = 0.0f; break;
    case GREEN :
    red = 0.0f;
    green = 1.0f;
    blue = 0.0f; break;
    case BLUE :
    red = 0.0f;
    green = 0.0f;
    blue = 1.0f; break;
    case ORANGE :
    red = 1.0f;
    green = 0.5f;
    blue = 0.5f; break;
  }
}

void processFontMenu(int option)
{
  switch (option) {
    case INT_GLUT_BITMAP_8_BY_13:
    font = GLUT_BITMAP_8_BY_13;
    break;
    case INT_GLUT_BITMAP_9_BY_15:
    font = GLUT_BITMAP_9_BY_15;
    break;
    case INT_GLUT_BITMAP_TIMES_ROMAN_10:
    font = GLUT_BITMAP_TIMES_ROMAN_10;
    break;
    case INT_GLUT_BITMAP_TIMES_ROMAN_24:
    font = GLUT_BITMAP_TIMES_ROMAN_24;
    break;
    case INT_GLUT_BITMAP_HELVETICA_10:
    font = GLUT_BITMAP_HELVETICA_10;
    break;
    case INT_GLUT_BITMAP_HELVETICA_12:
    font = GLUT_BITMAP_HELVETICA_12;
    break;
    case INT_GLUT_BITMAP_HELVETICA_18:
    font = GLUT_BITMAP_HELVETICA_18;
    break;
  }
}

void processStrokeFontMenu(int option)
{
  switch (option) {
    case INT_GLUT_STROKE_ROMAN:
    strfont = GLUT_STROKE_ROMAN;
    break;
    case INT_GLUT_STROKE_MONO_ROMAN:
    strfont = GLUT_STROKE_MONO_ROMAN;
    break;
  }
}

void createPopupMenus()
{

  fontMenu = glutCreateMenu(processFontMenu);
  glutAddMenuEntry("BITMAP_8_BY_13 ",INT_GLUT_BITMAP_8_BY_13 );
  glutAddMenuEntry("BITMAP_9_BY_15",INT_GLUT_BITMAP_9_BY_15 );
  glutAddMenuEntry("BITMAP_TIMES_ROMAN_10 ",INT_GLUT_BITMAP_TIMES_ROMAN_10  );
  glutAddMenuEntry("BITMAP_TIMES_ROMAN_24",INT_GLUT_BITMAP_TIMES_ROMAN_24  );
  glutAddMenuEntry("BITMAP_HELVETICA_10 ",INT_GLUT_BITMAP_HELVETICA_10  );
  glutAddMenuEntry("BITMAP_HELVETICA_12",INT_GLUT_BITMAP_HELVETICA_12  );
  glutAddMenuEntry("BITMAP_HELVETICA_18",INT_GLUT_BITMAP_HELVETICA_18  );

  strokeFontMenu = glutCreateMenu(processStrokeFontMenu);
  glutAddMenuEntry("GLUT_STROKE_ROMAN ",INT_GLUT_STROKE_ROMAN );
  glutAddMenuEntry("GLUT_STROKE_MONO_ROMAN",INT_GLUT_STROKE_MONO_ROMAN );

  shrinkMenu = glutCreateMenu(processShrinkMenu);

  glutAddMenuEntry("Shrink",SHRINK);
  glutAddMenuEntry("NORMAL",NORMAL);

  fillMenu = glutCreateMenu(processFillMenu);

  glutAddMenuEntry("Fill",FILL);
  glutAddMenuEntry("Line",LINE);

  colorMenu = glutCreateMenu(processColorMenu);
  glutAddMenuEntry("Red",RED);
  glutAddMenuEntry("Blue",BLUE);
  glutAddMenuEntry("Green",GREEN);
  glutAddMenuEntry("Orange",ORANGE);

  mainMenu = glutCreateMenu(processMainMenu);

  glutAddSubMenu("Polygon Mode", fillMenu);
  glutAddSubMenu("Color", colorMenu);

  // this will allow us to know if the menu is active
  glutMenuStatusFunc(processMenuStatus);
}

void destroyPopupMenus()
{
  glutDestroyMenu(mainMenu);
  glutDestroyMenu(fillMenu);
  glutDestroyMenu(colorMenu);
  glutDestroyMenu(shrinkMenu);
  glutDestroyMenu(fontMenu);
  glutDestroyMenu(strokeFontMenu);
}

/**************************************** myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
  //glutSetMenu(mainMenu);
  if(radioButtonIndex >= 35 && !show_text){

    if(!useMouseForImGui){
      float cameraSpeed = 0.005 * logl_deltaTime;
      if (Key == 'w')
      logl_cameraPos += cameraSpeed * logl_cameraFront;
      if (Key == 's')
      logl_cameraPos -= cameraSpeed * logl_cameraFront;
      if (Key == 'a')
      logl_cameraPos -= glm::normalize(glm::cross(logl_cameraFront, logl_cameraUp)) * cameraSpeed;
      if (Key == 'd')
      logl_cameraPos += glm::normalize(glm::cross(logl_cameraFront, logl_cameraUp)) * cameraSpeed;
    }

    if(Key == 27){
      glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
      logl_useMouseMov = false;
      useMouseForImGui = true;
    }

  }else{
    switch(Key)
    {
      case 27:
      if(radioButtonIndex == 20 && !show_text){
        reset_mainWindow();
      }
      break;

      if(radioButtonIndex >= 10){
        case 's':
        if (!menuFlag)
        glutChangeToSubMenu(2,"Shrink",shrinkMenu);
        break;
        case 'c':
        if (!menuFlag)
        glutChangeToSubMenu(2,"Color",colorMenu);
        break;
      }

      case 't':
      if(transparency <1.0)
      transparency+=0.1;
      break;

      case 'T':
      if(transparency >0.0)
      transparency-=0.1;
      break;

    };
  }
  // Send character to imgui
  ImGuiIO& io = ImGui::GetIO();
  if (Key >= 32)
  io.AddInputCharacter((unsigned short)Key);

  // Store letters in KeysDown[] array as both uppercase and lowercase + Handle GLUT translating CTRL+A..CTRL+Z as 1..26.
  // This is a hacky mess but GLUT is unable to distinguish e.g. a TAB key from CTRL+I so this is probably the best we can do here.
  if (Key >= 1 && Key <= 26)
  io.KeysDown[Key] = io.KeysDown[Key - 1 + 'a'] = io.KeysDown[Key - 1 + 'A'] = true;
  else if (Key >= 'a' && Key <= 'z')
  io.KeysDown[Key] = io.KeysDown[Key - 'a' + 'A'] = true;
  else if (Key >= 'A' && Key <= 'Z')
  io.KeysDown[Key] = io.KeysDown[Key - 'A' + 'a'] = true;
  else
  io.KeysDown[Key] = true;
  ImGui_ImplFreeGLUT_UpdateKeyboardMods();
  (void)x; (void)y; // Unused
}

void processSpecialKeys(int key, int x, int y)
{
  if(radioButtonIndex == 4 ){
    switch(key) {
      case GLUT_KEY_F1 :
      objRed = 1.0;
      objGreen = 0.0;
      objBlue = 0.0; break;
      case GLUT_KEY_F2 :
      objRed = 0.0;
      objGreen = 1.0;
      objBlue = 0.0; break;
      case GLUT_KEY_F3 :
      objRed = 0.0;
      objGreen = 0.0;
      objBlue = 1.0; break;
    }
  }
  ///
  if(radioButtonIndex == 5 ) {
    float fraction = 0.1f;

    switch (key) {
      case GLUT_KEY_LEFT :
      angle -= 0.01f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
      case GLUT_KEY_RIGHT :
      angle += 0.01f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
      case GLUT_KEY_UP :
      x += lx * fraction;
      z += lz * fraction;
      break;
      case GLUT_KEY_DOWN :
      x -= lx * fraction;
      z -= lz * fraction;
      break;
    }
  }

  ///////
  if(radioButtonIndex == 7){
    switch (key) {
      case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
      case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
      case GLUT_KEY_UP : deltaMove = 0.5f; break;
      case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
    }
  }
  ////
  if(radioButtonIndex >= 9){
    switch (key) {
      case GLUT_KEY_UP : deltaMove = 0.5f; break;
      case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
    }
  }


  //printf("key_down_func %d\n", key);
  ImGuiIO& io = ImGui::GetIO();
  if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
  io.KeysDown[key + 256] = true;
  ImGui_ImplFreeGLUT_UpdateKeyboardMods();
  (void)x; (void)y; // Unused
}

void releaseKey(int key, int x, int y)
{
  if(radioButtonIndex == 7){
    switch (key) {
      case GLUT_KEY_LEFT :
      case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
      case GLUT_KEY_UP :
      case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
  }
  ////
  if(radioButtonIndex >= 9){
    switch (key) {
      case GLUT_KEY_UP :
      case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
  }


  ImGuiIO& io = ImGui::GetIO();
  if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
  io.KeysDown[key + 256] = false;
  ImGui_ImplFreeGLUT_UpdateKeyboardMods();
  (void)x; (void)y; // Unused
}

/***************************************** myGlutMouse() **********/
void myGlutMouse(int button, int button_state, int x, int y )
{
  if(radioButtonIndex >= 9){
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

      // when the button is released
      if (button_state == GLUT_UP) {
        angle += deltaAngle;
        xOrigin = -1;
      }
      else  {// state = GLUT_DOWN
        xOrigin = x;
      }
    }
  }

  if(radioButtonIndex >= 35 && !show_text){

    if(button == GLUT_RIGHT_BUTTON){
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_useMouseMov = true;
      useMouseForImGui = false;
    }

    if(!useMouseForImGui){
      if (logl_fov >= 1.0f && logl_fov <= 45.0f)
      if(button == 3)
      logl_fov -= 1.0f;
      if(button == 4)
      logl_fov += 1.0f;
      if (logl_fov <= 1.0f)
      logl_fov = 1.0f;
      if (logl_fov >= 45.0f)
      logl_fov = 45.0f;
    }

  }

  if(useMouseForImGui){
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
    int button2 = -1;
    if (button == GLUT_LEFT_BUTTON) button2 = 0;
    if (button == GLUT_RIGHT_BUTTON) button2 = 1;
    if (button == GLUT_MIDDLE_BUTTON) button2 = 2;
    if (button2 != -1 && button_state == GLUT_DOWN)
    io.MouseDown[button2] = true;
    if (button2 != -1 && button_state == GLUT_UP)
    io.MouseDown[button2] = false;

    if (button == 3){
      io.MouseWheel += 0.2;
    }

    else if (button == 4){
      io.MouseWheel -= 0.2;
    }
  }




}

/***************************************** myGlutMotion() **********/
void myGlutMotion(int x, int y )
{

  if(radioButtonIndex >= 9){
    // this will only be true when the left button is down
    if (xOrigin >= 0) {

      // update deltaAngle
      deltaAngle = (x - xOrigin) * 0.001f;

      // update camera's direction
      lx = sin(angle + deltaAngle);
      lz = -cos(angle + deltaAngle);
    }
  }

  if(useMouseForImGui){
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
  }

}

void myGlutPassiveMotion(int x, int y)
{
  if(radioButtonIndex >= 35 && !show_text && logl_useMouseMov){
    if (logl_firstMouse)
    {
      logl_lastX = x;
      logl_lastY = y;
      logl_firstMouse = false;
    }

    float xoffset = x - logl_lastX;
    float yoffset = logl_lastY - y; // reversed since y-coordinates go from bottom to top
    logl_lastX = x;
    logl_lastY = y;

    float sensitivity = 0.2f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    logl_yaw += xoffset;
    logl_pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (logl_pitch > 89.0f)
    logl_pitch = 89.0f;
    if (logl_pitch < -89.0f)
    logl_pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(logl_yaw)) * cos(glm::radians(logl_pitch));
    front.y = sin(glm::radians(logl_pitch));
    front.z = sin(glm::radians(logl_yaw)) * cos(glm::radians(logl_pitch));
    logl_cameraFront = glm::normalize(front);


  }

  if(useMouseForImGui){
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
  }

}

/**************************************** myGlutReshape() *************/
void myGlutReshape( int x, int y )
{

  if(radioButtonIndex == 20 && !show_text)
  {
    if(y == 0)
    y = 1;

    // set subwindow 1 as the active window
    glutSetWindow(subWindow1);
    // resize and reposition the sub window
    glutPositionWindow(border,border);
    glutReshapeWindow(x-2*border, y/2 - border*3/2);
    setProjection(x-2*border, y/2 - border*3/2);

    // set subwindow 2 as the active window
    glutSetWindow(subWindow2);
    // resize and reposition the sub window
    glutPositionWindow(border,(y+border)/2);
    glutReshapeWindow(x/2-border*3/2, y/2 - border*3/2);
    setProjection(x/2-border*3/2,y/2 - border*3/2);

    // set subwindow 3 as the active window
    glutSetWindow(subWindow3);
    // resize and reposition the sub window
    glutPositionWindow((x+border)/2,(y+border)/2);
    glutReshapeWindow(x/2-border*3/2,y/2 - border*3/2);
    setProjection(x/2-border*3/2,y/2 - border*3/2);

  }else
  {
    int tx, ty, tw, th;
    glViewport( tx, ty, tw, th );

    xy_aspect = (float)tw / (float)th;

    if (y == 0)
    y = 1;

    float ratio =  x * 1.0 / y;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, x, y);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    //glutPostRedisplay();
  }
  SCR_WIDTH = x;
  SCR_HEIGHT = y;
  if(show_text)
  imGui_width = SCR_WIDTH;
  else
  imGui_width = 235;
  imGui_height = SCR_HEIGHT;
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2((float)x, (float)y);

  windowResized = true;
}

/***************************************** myGlutDisplay() *****************/
void myGlutDisplay()
{

  glClearColor( colorBG.x,colorBG.y, colorBG.z, 1.0f );
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();


  render_ImGui();
  fps_counter();
  glutSwapBuffers();
}

void setProjection(int w1, int h1)
{
  float ratio;
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  ratio = 1.0f * w1 / h1;
  // Reset the coordinate system before modifying
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w1, h1);

  // Set the clipping volume
  gluPerspective(45,ratio,0.1,1000);
  glMatrixMode(GL_MODELVIEW);
}

// Common Render Items for all subwindows
void renderScene2()
{
  // Draw ground
  glColor3f(0.9f, 0.9f, 0.9f);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();

  // Draw 36 SnowMen
  for(int i = -3; i < 3; i++)
  for(int j=-3; j < 3; j++){
    glPushMatrix();
    glTranslatef(i*10.0f, 0.0f, j * 10.0f);
    drawSnowMan();
    glPopMatrix();
  }
}

// Display func for main window
void renderSceneTMP()
{
  glutSetWindow(main_window);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

// Display func for sub window 1
void renderScenesw1()
{
  glutSetWindow(subWindow1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(x, y, z,x + lx,y + ly,z + lz,0.0f,1.0f,0.0f);
  renderScene2();

  // display fps in the top window
  frame++;

  timeFPS=glutGet(GLUT_ELAPSED_TIME);
  if (timeFPS - timebase > 1000) {
    sprintf(fps,"Lighthouse3D - FPS:%4.2f",
    frame*1000.0/(timeFPS-timebase));
    timebase = timeFPS;
    frame = 0;
  }

  setOrthographicProjection();

  glPushMatrix();
  glLoadIdentity();
  renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_12,fps);
  glPopMatrix();

  restorePerspectiveProjection();

  glutSwapBuffers();
}

// Display func for sub window 2
void renderScenesw2()
{
  glutSetWindow(subWindow2);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(x, y+15, z,x ,y - 1,z,lx,0,lz);
  // Draw red cone at the location of the main camera
  glPushMatrix();
  glColor3f(1.0,0.0,0.0);
  glTranslatef(x,y,z);
  glRotatef(180-(angle+deltaAngle)*180.0/3.14,0.0,1.0,0.0);
  glutSolidCone(0.2,0.8f,4,4);
  glPopMatrix();

  renderScene2();

  glutSwapBuffers();
}

// Display func for sub window 3
void renderScenesw3()
{

  glutSetWindow(subWindow3);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(x-lz*10 , y, z+lx*10,x ,y ,z ,0.0f,1.0f,0.0f);

  // Draw red cone at the location of the main camera
  glPushMatrix();
  glColor3f(1.0,0.0,0.0);
  glTranslatef(x,y,z);
  glRotatef(180-(angle+deltaAngle)*180.0/3.14,0.0,1.0,0.0);
  glutSolidCone(0.2,0.8f,4,4);
  glPopMatrix();

  renderScene2();

  glutSwapBuffers();
}

// Global idle func
void renderSceneAll()
{
  // check for keyboard movement
  if (deltaMove)
  computePos(deltaMove);

  renderScenesw1();
  renderScenesw2();
  renderScenesw3();
}

void destroyWindows()
{
  glutDestroyWindow(subWindow1);
  glutDestroyWindow(subWindow2);
  glutDestroyWindow(subWindow3);
  glutDestroyWindow(main_window);
}

void init_glut()
{

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // register callbacks
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(myGlutKeyboard);
  glutSpecialFunc(processSpecialKeys);
  glutSpecialUpFunc(releaseKey);
  glutMouseFunc(myGlutMouse);
  glutMotionFunc(myGlutMotion);

}

void create_subWindows()
{
  //glutDisplayFunc(NULL);
  glutDisplayFunc(renderSceneTMP);
  glutIdleFunc(NULL);
  glutIdleFunc(renderSceneAll);
  //myGlutReshape(SCR_WIDTH,SCR_HEIGHT);

  // sub windows
  subWindow1 = glutCreateSubWindow(main_window, 30,30,(SCR_WIDTH-2*border)/2, SCR_HEIGHT/2 - border*3/2);
  glutDisplayFunc(renderScenesw1);
  init_glut();

  subWindow2 = glutCreateSubWindow(main_window, 30,(SCR_HEIGHT+border)/2,SCR_WIDTH/2-border*3/2, SCR_HEIGHT/2 - border*3/2);
  glutDisplayFunc(renderScenesw2);
  init_glut();

  subWindow3 = glutCreateSubWindow(main_window, (SCR_WIDTH+border)/2,(SCR_HEIGHT+border)/2,SCR_WIDTH/2-border*3/2,SCR_HEIGHT/2 - border*3/2);
  glutDisplayFunc(renderScenesw3);
  init_glut();

  myGlutReshape(SCR_WIDTH,SCR_HEIGHT);
}

void reset_mainWindow()
{
  glutDestroyWindow(subWindow1);
  glutDestroyWindow(subWindow2);
  glutDestroyWindow(subWindow3);

  glutSetWindow(main_window);
  glutDisplayFunc(myGlutDisplay);
  glutIdleFunc(NULL);
  show_text = true;
  imGui_width = SCR_WIDTH;
  //glutIdleFunc(renderSceneAll);
}

void myPerspective()
{
  glClearColor( colorBG.x,colorBG.y, colorBG.z, 1.0f );
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void display_tut_1()
{
  myPerspective();

  if(!show_text){
    gluLookAt(	0.0f, 0.0f, 10.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f);
    glColor3f( 1, 1, 1 );
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5,-0.5,0.0);
    glVertex3f(0.5,0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();

  }else
  {
    //render_tut_text();
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();

}

void display_tut_2()
{
  myPerspective();

  if(!show_text)
  {
    gluLookAt(	0.0f, 0.0f, 10.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f);

    glTranslatef(obj_pos[0]/50,obj_pos[1]/50,-obj_pos[2]/50);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f( 1, 1, 1 );

    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f,-2.0f, 0.0f);
    glVertex3f( 2.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 2.0f, 0.0);
    glEnd();

    angle+=0.9f;
  }else
  {
    //render_tut_text();
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void display_tut_3()
{
  myPerspective();
  if(!show_text)
  {
    gluLookAt(	0.0f, 0.0f, 10.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f);
    glColor3f( objRed, objGreen, objBlue );
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f,-2.0f, 0.0f);
    glVertex3f( 2.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 2.0f, 0.0);
    glEnd();
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void display_tut_4()
{
  myPerspective();
  if(!show_text)
  {
    gluLookAt(	x, 1.0f, z,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    for(int i = -3; i < 3; i++)
    for(int j=-3; j < 3; j++) {
      glPushMatrix();
      glTranslatef(i*10.0,0,j * 10.0);
      drawSnowMan();
      glPopMatrix();
    }
  }else
  {
    //render_tut_text();
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void display_tut_5()
{
  myPerspective();
  if(!show_text)
  {
    if(!menuFlag)
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    if (deltaMove)
    computePos(deltaMove);
    if(radioButtonIndex == 7){
      if (deltaAngle)
      computeDir(deltaAngle);
    }


    gluLookAt(	x, 1.0f, z,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    for(int i = -3; i < 3; i++)
    for(int j=-3; j < 3; j++) {
      glPushMatrix();
      glTranslatef(i*10.0,0,j * 10.0);
      drawSnowMan();
      glPopMatrix();
    }
  }else
  {
    if(!menuFlag)
    glutDetachMenu(GLUT_RIGHT_BUTTON);
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void display_tut_6()
{
  myPerspective();
  if(!show_text)
  {
    if (deltaMove)
    computePos(deltaMove);
    gluLookAt(x, 1.0f, z,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    char number[3];
    for(int i = -3; i < 3; i++)
    for(int j=-3; j < 3; j++) {
      glPushMatrix();
      glTranslatef(i*10.0f, 0.0f, j * 10.0f);
      drawSnowMan();
      sprintf(number,"%d",(i+3)*6+(j+3));
      if(radioButtonIndex == 16 || radioButtonIndex == 22)
      renderStrokeFontString(0.0f, 0.5f, 0.0f, (void *)strfont ,number);
      else
      renderBitmapString(0.0f, 0.5f, 0.0f, (void *)font ,number);
      glPopMatrix();
    }
  }else
  {
    //render_tut_text();
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void blankDisplay()
{

  myPerspective();
  if(!show_text)
  {

  }else
  {
    //render_tut_text();
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();

}

void resetSceneVars()
{
  x=0.0;z=5.0;lx=0.0;lz=-1.0;angle=0.0;deltaAngle=0.0;deltaMove=0;
}

void setCursor()
{
  for (size_t i = 0; i < isHyprLinkHoveredVec.size(); i++) {
    hyperlinkHovered = false;
    if(isHyprLinkHoveredVec.at(i)){
      hyperlinkHovered = true;
      break;
    }
  }
  if(hyperlinkHovered && show_text){
    glutSetCursor(GLUT_CURSOR_INFO);
  }else if(!hyperlinkHovered && show_text){
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
  }
}

void de_allocator()
{
  glDeleteVertexArrays(1, &logl_Colors_cubeVAO);
  glDeleteVertexArrays(1, &logl_Colors_lightVAO);
  glDeleteBuffers(1, &logl_Colors_VBO);
  ///
  glDeleteVertexArrays(1, &logl_BasicLighting_cubeVAO);
  glDeleteVertexArrays(1, &logl_BasicLighting_lightVAO);
  glDeleteBuffers(1, &logl_BasicLighting_VBO);
  ///
  glDeleteVertexArrays(1, &logl_Materials_cubeVAO);
  glDeleteVertexArrays(1, &logl_Materials_lightVAO);
  glDeleteBuffers(1, &logl_Materials_VBO);
  ///
  glDeleteVertexArrays(1, &logl_LightingMaps_cubeVAO);
  glDeleteVertexArrays(1, &logl_LightingMaps_lightVAO);
  glDeleteBuffers(1, &logl_LightingMaps_VBO);
  ///
  glDeleteVertexArrays(1, &logl_LightCasters_cubeVAO);
  glDeleteVertexArrays(1, &logl_LightCasters_lightVAO);
  glDeleteBuffers(1, &logl_LightCasters_VBO);
  ///
  glDeleteVertexArrays(1, &logl_MultipleLights_lightVAO);
  glDeleteVertexArrays(1, &logl_MultipleLights_cubeVAO);
  glDeleteBuffers(1, &logl_MultipleLights_VBO);
  ///
  glDeleteVertexArrays(1, &logl_DepthTesting_cubeVAO);
  glDeleteVertexArrays(1, &logl_DepthTesting_planeVAO);
  glDeleteBuffers(1, &logl_DepthTesting_cubeVBO);
  glDeleteBuffers(1, &logl_DepthTesting_planeVBO);
  ///
  glDeleteVertexArrays(1, &logl_StencilTesting_cubeVAO);
  glDeleteVertexArrays(1, &logl_StencilTesting_planeVAO);
  glDeleteBuffers(1, &logl_StencilTesting_cubeVBO);
  glDeleteBuffers(1, &logl_StencilTesting_planeVBO);
  ///
  glDeleteVertexArrays(1, &logl_Blending_cubeVAO);
  glDeleteVertexArrays(1, &logl_Blending_planeVAO);
  glDeleteBuffers(1, &logl_Blending_cubeVBO);
  glDeleteBuffers(1, &logl_Blending_planeVBO);
  ///
  glDeleteVertexArrays(1, &logl_FaceCulling_VAO);
  glDeleteVertexArrays(1, &logl_FaceCulling_VBO);
  ///
  glDeleteVertexArrays(1, &logl_Framebuffers_cubeVAO);
  glDeleteVertexArrays(1, &logl_Framebuffers_planeVAO);
  glDeleteVertexArrays(1, &logl_Framebuffers_quadVAO);
  glDeleteBuffers(1, &logl_Framebuffers_cubeVBO);
  glDeleteBuffers(1, &logl_Framebuffers_planeVBO);
  glDeleteBuffers(1, &logl_Framebuffers_quadVBO);
  ///
  glDeleteVertexArrays(1, &logl_Cubemaps_cubeVAO);
  glDeleteVertexArrays(1, &logl_Cubemaps_skyboxVAO);
  glDeleteBuffers(1, &logl_Cubemaps_cubeVBO);
  glDeleteBuffers(1, &logl_Cubemaps_skyboxVAO);
  ///
  glDeleteVertexArrays(1, &logl_AdvancedGLSL_cubeVAO);
  glDeleteBuffers(1, &logl_AdvancedGLSL_cubeVBO);
  ///
  glDeleteVertexArrays(1, &logl_GeometryShader_VAO);
  glDeleteBuffers(1, &logl_GeometryShader_VBO);
  ///
  glDeleteVertexArrays(1, &logl_Instancing_quadVAO);
  glDeleteBuffers(1, &logl_Instancing_quadVBO);
  ///
  glDeleteVertexArrays(1, &logl_AntiAliasing_cubeVAO);
  glDeleteBuffers(1, &logl_AntiAliasing_cubeVBO);
  glDeleteVertexArrays(1, &logl_AntiAliasing_quadVAO);
  glDeleteBuffers(1, &logl_AntiAliasing_quadVBO);
  ///
  glDeleteVertexArrays(1, &logl_AdvancedLighting_planeVAO);
  glDeleteBuffers(1, &logl_AdvancedLighting_planeVBO);
  ///
  glDeleteVertexArrays(1, &logl_GammaCorrection_planeVAO);
  glDeleteBuffers(1, &logl_GammaCorrection_planeVBO);
  ///
  glDeleteVertexArrays(1, &logl_ShadowMapping_planeVAO);
  glDeleteBuffers(1, &logl_ShadowMapping_planeVBO);

}

void serializeUserData()
{

  if(!checkUserData){
    const char* fileName = "Configurations/UserInfo.ser";
    // Create an output archive
    std::ofstream ofs(fileName);
    boost::archive::text_oarchive ar(ofs);

    // Write data
    ar << userDataObj;
    return;
  }
}

void deSerializeUserData()
{
  if(!userDataDeserialized){
    const char* fileName = "Configurations/UserInfo.ser";
    // Create and input archive
    std::ifstream ifs(fileName);
    boost::archive::text_iarchive ar(ifs);

    // Load data
    ar & userDataObj;
    radioButtonIndex = userDataObj.getLastTutOpenedIndex(imGui_width, SCR_WIDTH, show_text);
    applyTutorialsFunc(radioButtonIndex);
    checkUserData = false;
    userDataDeserialized = true;
  }
}

void applyTutorialsFunc(int index)
{

  if(index == 0){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 1){
    resetFunc();
    glutDisplayFunc(display_tut_1);resetSceneVars();
  }
  if(index == 2){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 3){
    resetFunc();
    glutDisplayFunc(display_tut_2);
  }

  if(index == 4){
    resetFunc();
    glutDisplayFunc(display_tut_3);
  }
  if(index == 5){
    resetFunc();
    glutDisplayFunc(display_tut_4);
  }
  if(index == 6){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 7){
    resetFunc();
    glutDisplayFunc(display_tut_5);
  }
  if(index == 8){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 9){
    resetFunc();
    glutDisplayFunc(display_tut_5);
  }

  if(index == 10){
    resetScrollY = true;
    resetLight();resetFog();
    glutDisplayFunc(display_tut_5);resetSceneVars();
    if(!menuFlag && glutGet(GLUT_MENU_NUM_ITEMS) >=3)
    glutRemoveMenuItem(3);
  }
  if(index == 11){
    resetScrollY = true;
    resetLight();resetFog();
    glutDisplayFunc(display_tut_5);resetSceneVars();
    if(!menuFlag && glutGet(GLUT_MENU_NUM_ITEMS) >=3)
    glutRemoveMenuItem(3);
  }
  if(index == 12){
    resetScrollY = true;
    resetLight();resetFog();
    glutDisplayFunc(display_tut_5);resetSceneVars();
    if(!menuFlag && glutGet(GLUT_MENU_NUM_ITEMS) >=3)
    glutRemoveMenuItem(3);
  }
  if(index == 13){
    resetScrollY = true;
    resetLight();resetFog();
    glutDisplayFunc(display_tut_5);resetSceneVars();
    if(!menuFlag && glutGet(GLUT_MENU_NUM_ITEMS) >=3)
    glutRemoveMenuItem(3);
  }

  if(index == 14){
    resetScrollY = true;
    resetLight();resetFog();
    glutDisplayFunc(display_tut_6);resetSceneVars();
    if(!menuFlag)
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    if(!menuFlag && glutGet(GLUT_MENU_NUM_ITEMS) ==3)
    glutRemoveMenuItem(3);
    if(!menuFlag &&  glutGet(GLUT_MENU_NUM_ITEMS) <3)
    glutAddSubMenu("Font",fontMenu);
  }
  if(index == 15){
    resetScrollY = true;
    resetLight();resetFog();resetSceneVars();
    if(!menuFlag)
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 16){
    resetFunc();
    glutDisplayFunc(display_tut_6);
    if(!menuFlag)
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    if(!menuFlag && glutGet(GLUT_MENU_NUM_ITEMS) ==3)
    glutRemoveMenuItem(3);
    if(!menuFlag &&  glutGet(GLUT_MENU_NUM_ITEMS) <3)
    glutAddSubMenu("Font",strokeFontMenu);
  }

  if(index == 17){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 18){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 19){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 20){
    resetScrollY = true;
    resetLight();resetFog();
    resetSceneVars();
    if(!show_text)
    create_subWindows();
  }

  if(index == 21){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }

  if(index == 22){
    resetFunc();
    glutDisplayFunc(display_tut_6);
  }
  if(index == 23){
    resetFunc();
    initializeFog();
    glutDisplayFunc(displayFog);

  }
  if(index == 24){
    resetFunc();
    //loadBlendingTutText();
    glutDisplayFunc(blendingDisplay);

  }
  if(index == 25){
    resetFunc();
    initializeLight();
    glutDisplayFunc( displayLight );

  }
  if(index == 26){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }

  if(index == 27){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 28){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 29){
    resetFunc();
    glutDisplayFunc(logl_Hello_Dindow_Display);
  }
  if(index == 30){
    resetFunc();
    glutDisplayFunc(logl_Hello_Triangle_Display);
  }
  if(index == 31){
    resetFunc();
    glutDisplayFunc(logl_Shaders_Display);
  }
  if(index == 32){
    resetFunc();
    glutDisplayFunc(logl_Textures_Display);
  }
  if(index == 33){
    resetFunc();
    glutDisplayFunc(logl_Transformation_Display);
  }
  if(index == 34){
    resetFunc();
    glutDisplayFunc(logl_CoordinateSystem_Display);
  }
  if(index == 35){
    resetFunc();
    glutDisplayFunc(logl_Camera_Display);
  }
  if(index == 36){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }

  if(index == 37){
    resetFunc();
    logl_cameraPos = glm::vec3(-.5, -.16, 4.4);
    logl_pitch = 9; logl_yaw = -77;
    logl_Colors_Init();
    glutDisplayFunc(logl_Colors_Display);
  }
  if(index == 38){
    resetFunc();
    logl_cameraPos = glm::vec3(-.5, .75, -.83);
    logl_pitch = -11.5; logl_yaw = 57;
    logl_BasicLighting_Init();
    glutDisplayFunc(logl_BasicLighting_Display);
  }
  if(index == 39){
    resetFunc();
    logl_cameraPos = glm::vec3(-1.6, -1.0, 2.5);
    logl_pitch = 24; logl_yaw = -48.5;
    logl_Materials_Init();
    glutDisplayFunc(logl_Materials_Display);
  }
  if(index == 40){
    resetFunc();
    logl_cameraPos = glm::vec3(-1.6, -0.6, 3.4);
    logl_pitch = 15; logl_yaw = -62;
    logl_LightingMaps_Init();
    glutDisplayFunc(logl_LightingMaps_Display);
  }
  if(index == 41){
    resetFunc();
    logl_LightCasters_Init();
    glutDisplayFunc(logl_LightCasters_Display);
  }
  if(index == 42){
    resetFunc();
    logl_MultipleLights_Init();
    glutDisplayFunc(logl_MultipleLights_Display);
  }
  if(index == 43){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 44){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 45){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 46){
    resetFunc();
    multipleOutputs = 2;
    logl_Model_Init();
    glutDisplayFunc(logl_Model_Display);
  }

  if(index == 47){
    resetFunc();
    logl_cameraPos = glm::vec3(.87, 2.26, 7.1);
    logl_pitch = -19; logl_yaw = -96;
    logl_DepthTesting_Init();
    glutDisplayFunc(logl_DepthTesting_Display);
  }
  if(index == 48){
    resetFunc();
    logl_StencilTesting_Init();
    glutDisplayFunc(logl_StencilTesting_Display);
  }
  if(index == 49){
    resetFunc();
    multipleOutputs = 2;
    logl_Blending_Init();
    glutDisplayFunc(logl_Blending_Display);
  }
  if(index == 50){
    resetFunc();
    logl_cameraPos = glm::vec3(1.7, 0.6, 1.7);
    logl_pitch = -19; logl_yaw = -134.2;
    logl_FaceCulling_Init();
    glutDisplayFunc(logl_FaceCulling_Display);
  }
  if(index == 51){
    resetFunc();
    multipleOutputs = 6;
    logl_Framebuffers_Init();
    glutDisplayFunc(logl_Framebuffers_Display);
  }
  if(index == 52){
    resetFunc();
    multipleOutputs = 3;
    logl_cameraPos.z = 4.15f;
    logl_Cubemaps_Init();
    glutDisplayFunc(logl_Cubemaps_Display);
  }
  if(index == 53){
    resetFunc();
    show_text = true;
    imGui_width = SCR_WIDTH;
  }
  if(index == 54){
    resetFunc();
    logl_AdvancedGLSL_Init();
    glutDisplayFunc(logl_AdvancedGLSL_Display);
  }
  if(index == 55){
    resetFunc();
    multipleOutputs = 3;
    logl_GeometryShader_Init();
    glutDisplayFunc(logl_GeometryShader_Display);
  }
  if(index == 56){
    resetFunc();
    multipleOutputs = 4;
    logl_Instancing_Init();
    glutDisplayFunc(logl_Instancing_Display);
  }
  if(index == 57){
    resetFunc();
    logl_AntiAliasing_Init();
    glutDisplayFunc(logl_AntiAliasing_Display);
  }
  if(index == 58){
    resetFunc();
    multipleOutputs = 2;
    logl_AdvancedLighting_Init();
    glutDisplayFunc(logl_AdvancedLighting_Display);
  }
  if(index == 59){
    resetFunc();
    multipleOutputs = 2;
    logl_GammaCorrection_Init();
    glutDisplayFunc(logl_GammaCorrection_Display);
  }
  if(index == 60){
    resetFunc();
    logl_ShadowMapping_Init();
    glutDisplayFunc(logl_ShadowMapping_Display);
  }
  if(index == 61){
    resetFunc();
    logl_PointShadows_Init();
    glutDisplayFunc(logl_PointShadows_Display);
  }
  if(index == 62){
    resetFunc();
    logl_NormalMapping_Init();
    glutDisplayFunc(logl_NormalMapping_Display);
  }
  if(index == 63){
    resetFunc();
    multipleOutputs = 2;
    logl_ParallaxMapping_Init();
    glutDisplayFunc(logl_ParallaxMapping_Display);
  }
  if(index == 64){
    resetFunc();
    multipleOutputs = 3;
    logl_cameraPos = glm::vec3(0.373899 , -0.739711, -2.49186);
    logl_pitch = -2.19993; logl_yaw = 92.5998;
    logl_HDR_Init();
    glutDisplayFunc(logl_HDR_Display);
  }
  if(index == 65){
    resetFunc();
    logl_cameraPos = glm::vec3(5.84636 , 0.0483801, 5.52349);
    logl_pitch = 8; logl_yaw = -147.199;
    logl_Bloom_Init();
    glutDisplayFunc(logl_Bloom_Display);
  }
  if(index == 66){
    resetFunc();
    logl_cameraPos = glm::vec3(3.7 , 2.5, 5.92349);
    logl_pitch = -24; logl_yaw = -128.399;
    logl_DeferredShading_Init();
    glutDisplayFunc(logl_DeferredShading_Display);
  }
  if(index == 67){
    resetFunc();
    logl_cameraPos = glm::vec3(6.5982 , 4.5199, -4.23074);
    logl_pitch = -31.5999; logl_yaw = -227.598;
    logl_SSAO_Init();
    glutDisplayFunc(logl_SSAO_Display);
  }

}


/***********************************************************************/

#endif //FUNCTIONS_H
