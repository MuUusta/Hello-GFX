#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <fog.hpp>
#include <string>
#include <common.h>
using namespace std;

void initializeFog(){

  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogf(GL_FOG_START, 0.0);
  glFogf(GL_FOG_END, 9.0);
  float color[] = {0.6, 0.6, 0.6, 1.0};
  glFogfv(GL_FOG_COLOR, color);
  glEnable(GL_FOG);

}
void resetFog(){
  glDisable(GL_FOG);
}
void displayFog(){
  glClearColor( 0.6, 0.6, 0.6, 1.0 );
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glTranslatef(0,0,-7-sin(glutGet(GLUT_ELAPSED_TIME)*0.0004)*3);
    glRotatef(glutGet(GLUT_ELAPSED_TIME)*0.02,0,1,0);
    glColor3f(0.6, 0.3, 0.0);
    glutSolidTeapot(1);
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
