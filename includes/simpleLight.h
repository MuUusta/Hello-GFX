#ifndef SIMPLELIGHT_H
#define SIMPLELIGHT_H

/* white ambient light at half intensity (rgba) */
GLfloat LightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
/* super bright, full intensity diffuse light. */
GLfloat LightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
/* super bright, full intensity Specular light. */
GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
/* position of light (x, y, z, (position of light)) */
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
/* material shininess  */
GLfloat shininess[] = {50};
bool lightsOn = true, circularMotion = true, EnableLightTut = false, shininessOn = true;
float lightPosX = 0.0, lightPosY = 0.0, lightPosZ = 0.0;
/* array to turn shininess off */
GLfloat lightSpecOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//vector<string> light_TuT_text;

void initializeLight(){
  EnableLightTut = true;
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);     // add lighting. (ambient)
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);     // add lighting. (diffuse).
  glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);   // add lighting. (specular).
  glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);    // set light position.


  glMaterialfv(GL_FRONT, GL_AMBIENT, LightAmbient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, LightDiffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, LightSpecular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);


}
void resetLight(){
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  EnableLightTut = false;
  shininessOn = true;
  lightsOn = true;
  circularMotion = true;
}
void displayLight(){

  myPerspective();

  if(!show_text){
    glTranslatef(0,0,-5);

    glLightfv(GL_LIGHT0, GL_POSITION,LightPosition); // set light position.
    //render cube as light Source
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(LightPosition[0],LightPosition[1],LightPosition[2]);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(0.2);
    if(lightsOn)
    glEnable(GL_LIGHTING);
    glPopMatrix();

    if(circularMotion){
      //move light source in circular motion
      LightPosition[0] = cos(glutGet(GLUT_ELAPSED_TIME)*0.001) * 2;
      //LightPosition[1] = sin(glutGet(GLUT_ELAPSED_TIME)*0.001) * 2;
      LightPosition[1] = 1.0f;
      LightPosition[2] = sin(glutGet(GLUT_ELAPSED_TIME)*0.001) * 2;
    }


    if(shininessOn){
      glMaterialfv(GL_FRONT, GL_SPECULAR, LightSpecular);
    }else{
      glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpecOff);
    }
    //render solid sphere
    glutSolidSphere(1,50,50);
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}


#endif //SIMPLELIGHT_H
