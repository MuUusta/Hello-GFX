#ifndef LEARNOGL_HPP
#define LEARNOGL_HPP

#include <shader.h>
#include <model.h>

// camera
glm::vec3 logl_cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 logl_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 logl_cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool logl_firstMouse = true;
float logl_yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float logl_pitch =  0.0f;
float logl_lastX =  SCR_WIDTH / 2.0;
float logl_lastY =  SCR_HEIGHT / 2.0;
float logl_fov   =  45.0f;

// timing
float logl_deltaTime = 0.0f;	// time between current frame and last frame
float logl_lastFrame = 0.0f;

bool logl_resetMousePos = false, logl_useMouseMov = true;

Model nanosuit, rock, planet;

void logl_Hello_Dindow_Display(){
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);


  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void logl_Hello_Triangle_Display(){
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glPushMatrix();

    glTranslatef(-2,0,0);
    glColor3f(1.0f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glVertex3f(0.0f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();
    ////////////////////////////
    glPushMatrix();

    glColor3f(1.0f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f,  0.5f, -6.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();
    ////////////////////////////
    glPushMatrix();

    glTranslatef(2,0,0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f,  0.5f, -6.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();
    ////////////////////////////
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void logl_Shaders_Display(){
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glPushMatrix();

    glTranslatef(-2,0,0);
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glVertex3f(0.0f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();

    {
      //////////////////////////////
      glPushMatrix();

      float timeValue = glutGet(GLUT_ELAPSED_TIME)*0.001;
      float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
      glColor3f(0.0, greenValue, 0.0);
      glBegin(GL_TRIANGLES);
      glVertex3f(-0.5f, -0.5f, -6.0f);
      glVertex3f(0.5f, -0.5f, -6.0f);
      glVertex3f(0.0f,  0.5f, -6.0f);
      glEnd();

      glPopMatrix();
    }
    //////////////////////////////
    glPushMatrix();

    glTranslatef(2,0,0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();
  }



  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

bool loadLoglTextures = true;
unsigned int containerTexId, combinedTexId;


void logl_Textures_Display(){
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-2,0,0);

    glBindTexture(GL_TEXTURE_2D, containerTexId);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f,  0.5f,-6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();

    ////////////////////////////////////

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, containerTexId);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f,  0.5f,-6.0f);
    glTexCoord2f(1.0f, 0.0f);glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glTexCoord2f(0.0f, 0.0f);glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glTexCoord2f(0.0f, 1.0f);glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();

    ////////////////////////////////////

    glPushMatrix();

    glTranslatef(2,0,0);
    glBindTexture(GL_TEXTURE_2D, combinedTexId);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f,  0.5f,-6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -6.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -6.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f, -6.0f);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
  }



  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void logl_Transformation_Display(){
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(2.2,-0.8,0);
    glRotatef(glutGet(GLUT_ELAPSED_TIME)*0.1,0,0,1);
    glBindTexture(GL_TEXTURE_2D, combinedTexId);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f,  0.5f,-4.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -4.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -4.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f, -4.0f);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
  }



  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void renderCube(){
  glBegin(GL_QUADS);
  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, 1.0f);//front
  glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5f,  0.5f,0.5f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5f, -0.5f, 0.5f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, -0.5f, 0.5f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5f,  0.5f, 0.5f);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, -1.0f);//back
  glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5f,  0.5f,-0.5f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5f, -0.5f, -0.5f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f,-0.5f,-0.5f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5f, 0.5f,-0.5f);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, -1.0f);//right
  glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5f,  0.5f,-0.5f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5f, -0.5f,-0.5f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5f, -0.5f, 0.5f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(0.5f,  0.5f, 0.5f);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, -1.0f);//left
  glTexCoord2f(1.0f, 1.0f);glVertex3f(-0.5f,  0.5f,-0.5f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(-0.5f, -0.5f,-0.5f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, -0.5f, 0.5f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5f,  0.5f, 0.5f);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, -1.0f);//top
  glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5f,  0.5f,-0.5f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5f,  0.5f, 0.5f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, 0.5f, 0.5f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5f, 0.5f,-0.5f);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, -1.0f);//top
  glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5f,  -0.5f,-0.5f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5f,  -0.5f, 0.5f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, -0.5f, 0.5f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5f, -0.5f, -0.5f);
  glEnd();
}
glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

void logl_CoordinateSystem_Display(){
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();



    glBindTexture(GL_TEXTURE_2D, combinedTexId);
    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0,0,-3);
    for (size_t i = 0; i < 10; i++) {
      glPushMatrix();
      glTranslatef(cubePositions[i].x,cubePositions[i].y,cubePositions[i].z);
      glRotatef(20.0f * i,1.0f,0.3f,0.5f);
      renderCube();
      glPopMatrix();
    }


    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
  }



  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void logl_Camera_Display(){

  // per-frame time logic
  // --------------------
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;


  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(logl_fov, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }
    gluLookAt(logl_cameraPos.x, logl_cameraPos.y, logl_cameraPos.z , logl_cameraPos.x + logl_cameraFront.x, logl_cameraPos.y + logl_cameraFront.y, logl_cameraPos.z + logl_cameraFront.z, logl_cameraUp.x, logl_cameraUp.y, logl_cameraUp.z);

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();



    glBindTexture(GL_TEXTURE_2D, combinedTexId);
    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0,0,-3);
    for (size_t i = 0; i < 10; i++) {
      glPushMatrix();
      glTranslatef(cubePositions[i].x,cubePositions[i].y,cubePositions[i].z);
      glRotatef(20.0f * i,1.0f,0.3f,0.5f);
      renderCube();
      glPopMatrix();
    }


    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

  }


  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

void logl_reset_Camera(){
  // camera
  logl_cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
  logl_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  logl_cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

  logl_firstMouse = true;
  logl_yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
  logl_pitch =  0.0f;
  logl_lastX =  SCR_WIDTH / 2.0;
  logl_lastY =  SCR_HEIGHT / 2.0;
  logl_fov   =  45.0f;

  // timing
  logl_deltaTime = 0.0f;	// time between current frame and last frame
  logl_lastFrame = 0.0f;

  logl_resetMousePos = false, logl_useMouseMov = true;

  glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

/////////////// LearnOpenGL - Colors ////////////
glm::vec3 logl_Colors_lightPos(1.2f, 1.0f, 2.0f);
LoglShader logl_Colors_lightingShader;
LoglShader logl_Colors_lampShader;
float logl_Colors_vertices[] = {
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f, -0.5f,  0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,

  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,

  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,

  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f,  0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
};
unsigned int logl_Colors_VBO, logl_Colors_cubeVAO;
unsigned int logl_Colors_lightVAO;
bool logl_Colors_ifInitOnce = false;

void logl_Colors_Init(){
  if(!logl_Colors_ifInitOnce){

    logl_Colors_lightingShader = LoglShader("learnOpenGL-tut/shaders/1.colors.vs", "learnOpenGL-tut/shaders/1.colors.fs");
    logl_Colors_lampShader = LoglShader("learnOpenGL-tut/shaders/1.lamp.vs", "learnOpenGL-tut/shaders/1.lamp.fs");

    glGenVertexArrays(1, &logl_Colors_cubeVAO);
    glGenBuffers(1, &logl_Colors_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_Colors_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Colors_vertices), logl_Colors_vertices, GL_STATIC_DRAW);
    //glDeleteBuffers(1, &VBO);



    glBindVertexArray(logl_Colors_cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    //unsigned int lightVAO;
    glGenVertexArrays(1, &logl_Colors_lightVAO);
    glBindVertexArray(logl_Colors_lightVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, logl_Colors_VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    logl_Colors_ifInitOnce = true;
  }
}

void logl_Colors_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }
    logl_Colors_lightingShader.use();
    logl_Colors_lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    logl_Colors_lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_Colors_lightingShader.setMat4("projection", projection);
    logl_Colors_lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    logl_Colors_lightingShader.setMat4("model", model);

    // render the cube
    glBindVertexArray(logl_Colors_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    logl_Colors_lampShader.use();
    logl_Colors_lampShader.setMat4("projection", projection);
    logl_Colors_lampShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, logl_Colors_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    logl_Colors_lampShader.setMat4("model", model);

    glBindVertexArray(logl_Colors_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Colors ////////////

/////////////// LearnOpenGL - Basic Lighting ////////////
glm::vec3 logl_BasicLighting_lightPos(1.2f, 1.0f, 2.0f);
LoglShader logl_BasicLighting_lightingShader;
LoglShader logl_BasicLighting_lampShader;
float logl_BasicLighting_vertices[] = {
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
unsigned int logl_BasicLighting_VBO, logl_BasicLighting_cubeVAO;
unsigned int logl_BasicLighting_lightVAO;
bool logl_BasicLighting_ifInitOnce = false;

void logl_BasicLighting_Init(){
  if(!logl_BasicLighting_ifInitOnce){

    logl_BasicLighting_lightingShader = LoglShader("learnOpenGL-tut/shaders/2.2.basic_lighting.vs", "learnOpenGL-tut/shaders/2.2.basic_lighting.fs");
    logl_BasicLighting_lampShader = LoglShader("learnOpenGL-tut/shaders/2.2.lamp.vs", "learnOpenGL-tut/shaders/2.2.lamp.fs");

    glGenVertexArrays(1, &logl_BasicLighting_cubeVAO);
    glGenBuffers(1, &logl_BasicLighting_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_BasicLighting_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_BasicLighting_vertices), logl_BasicLighting_vertices, GL_STATIC_DRAW);

    glBindVertexArray(logl_BasicLighting_cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &logl_BasicLighting_lightVAO);
    glBindVertexArray(logl_BasicLighting_lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_BasicLighting_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    logl_BasicLighting_ifInitOnce = true;
  }
}

void logl_BasicLighting_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    logl_BasicLighting_lightingShader.use();
    logl_BasicLighting_lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    logl_BasicLighting_lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    logl_BasicLighting_lightingShader.setVec3("lightPos", logl_BasicLighting_lightPos);
    logl_BasicLighting_lightingShader.setVec3("viewPos", logl_cameraPos);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_BasicLighting_lightingShader.setMat4("projection", projection);
    logl_BasicLighting_lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    logl_BasicLighting_lightingShader.setMat4("model", model);

    // render the cube
    glBindVertexArray(logl_BasicLighting_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    logl_BasicLighting_lampShader.use();
    logl_BasicLighting_lampShader.setMat4("projection", projection);
    logl_BasicLighting_lampShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, logl_BasicLighting_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    logl_BasicLighting_lampShader.setMat4("model", model);

    glBindVertexArray(logl_BasicLighting_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Basic Lighting ////////////

/////////////// LearnOpenGL - Materials ////////////
glm::vec3 logl_Materials_lightPos(1.2f, 1.0f, 2.0f);
LoglShader logl_Materials_lightingShader;
LoglShader logl_Materials_lampShader;
float logl_Materials_vertices[] = {
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
unsigned int logl_Materials_VBO, logl_Materials_cubeVAO;
unsigned int logl_Materials_lightVAO;
bool logl_Materials_ifInitOnce = false;

void logl_Materials_Init(){
  if(!logl_Materials_ifInitOnce){

    logl_Materials_lightingShader = LoglShader("learnOpenGL-tut/shaders/3.1.materials.vs", "learnOpenGL-tut/shaders/3.1.materials.fs");
    logl_Materials_lampShader = LoglShader("learnOpenGL-tut/shaders/3.1.lamp.vs", "learnOpenGL-tut/shaders/3.1.lamp.fs");

    glGenVertexArrays(1, &logl_Materials_cubeVAO);
    glGenBuffers(1, &logl_Materials_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_Materials_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Materials_vertices), logl_Materials_vertices, GL_STATIC_DRAW);

    glBindVertexArray(logl_Materials_cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &logl_Materials_lightVAO);
    glBindVertexArray(logl_Materials_lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_Materials_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    logl_Materials_ifInitOnce = true;
  }
}

void logl_Materials_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    logl_Materials_lightingShader.use();
    logl_Materials_lightingShader.setVec3("light.position", logl_Materials_lightPos);
    logl_Materials_lightingShader.setVec3("viewPos", logl_cameraPos);

    // light properties
    glm::vec3 lightColor;
    lightColor.x = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001 * 2.0f);
    lightColor.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001 * 0.7f);
    lightColor.z = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001 * 1.3f);
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    logl_Materials_lightingShader.setVec3("light.ambient", ambientColor);
    logl_Materials_lightingShader.setVec3("light.diffuse", diffuseColor);
    logl_Materials_lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // material properties
    logl_Materials_lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    logl_Materials_lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    logl_Materials_lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
    logl_Materials_lightingShader.setFloat("material.shininess", 32.0f);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_Materials_lightingShader.setMat4("projection", projection);
    logl_Materials_lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    logl_Materials_lightingShader.setMat4("model", model);

    // render the cube
    glBindVertexArray(logl_Materials_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    logl_Materials_lampShader.use();
    logl_Materials_lampShader.setMat4("projection", projection);
    logl_Materials_lampShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, logl_Materials_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    logl_Materials_lampShader.setMat4("model", model);

    glBindVertexArray(logl_Materials_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Materials ////////////

/////////////// LearnOpenGL - Lighting maps ////////////
glm::vec3 logl_LightingMaps_lightPos(1.2f, 1.0f, 2.0f);
LoglShader logl_LightingMaps_lightingShader;
LoglShader logl_LightingMaps_lampShader;
float logl_LightingMaps_vertices[] = {
  // positions          // normals           // texture coords
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
unsigned int logl_LightingMaps_VBO, logl_LightingMaps_cubeVAO;
unsigned int logl_LightingMaps_lightVAO, logl_LightingMaps_diffuseMap, logl_LightingMaps_specularMap;
bool logl_LightingMaps_ifInitOnce = false;

void logl_LightingMaps_Init(){
  if(!logl_LightingMaps_ifInitOnce){

    logl_LightingMaps_lightingShader = LoglShader("learnOpenGL-tut/shaders/4.2.lighting_maps.vs", "learnOpenGL-tut/shaders/4.2.lighting_maps.fs");
    logl_LightingMaps_lampShader = LoglShader("learnOpenGL-tut/shaders/4.2.lamp.vs", "learnOpenGL-tut/shaders/4.2.lamp.fs");

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_LightingMaps_diffuseMap = loadTex_stb("textures/container2.png");
    logl_LightingMaps_specularMap = loadTex_stb("textures/container2_specular.png");

    // shader configuration
    // --------------------
    logl_LightingMaps_lightingShader.use();
    logl_LightingMaps_lightingShader.setInt("material.diffuse", 1);
    logl_LightingMaps_lightingShader.setInt("material.specular", 2);

    glGenVertexArrays(1, &logl_LightingMaps_cubeVAO);
    glGenBuffers(1, &logl_LightingMaps_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_LightingMaps_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_LightingMaps_vertices), logl_LightingMaps_vertices, GL_STATIC_DRAW);

    glBindVertexArray(logl_LightingMaps_cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &logl_LightingMaps_lightVAO);
    glBindVertexArray(logl_LightingMaps_lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_LightingMaps_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_LightingMaps_ifInitOnce = true;
  }
}

void logl_LightingMaps_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    // be sure to activate shader when setting uniforms/drawing objects
    logl_LightingMaps_lightingShader.use();
    logl_LightingMaps_lightingShader.setVec3("light.position", logl_LightingMaps_lightPos);
    logl_LightingMaps_lightingShader.setVec3("viewPos", logl_cameraPos);

    // light properties
    logl_LightingMaps_lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    logl_LightingMaps_lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    logl_LightingMaps_lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // material properties
    logl_LightingMaps_lightingShader.setFloat("material.shininess", 64.0f);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_LightingMaps_lightingShader.setMat4("projection", projection);
    logl_LightingMaps_lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    logl_LightingMaps_lightingShader.setMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_LightingMaps_diffuseMap);
    // bind specular map
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_LightingMaps_specularMap);

    // render the cube
    glBindVertexArray(logl_LightingMaps_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // also draw the lamp object
    logl_LightingMaps_lampShader.use();
    logl_LightingMaps_lampShader.setMat4("projection", projection);
    logl_LightingMaps_lampShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, logl_LightingMaps_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    logl_LightingMaps_lampShader.setMat4("model", model);

    glBindVertexArray(logl_LightingMaps_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Lighting maps ////////////

/////////////// LearnOpenGL - Light casters ////////////
glm::vec3 logl_LightCasters_lightPos(1.2f, 1.0f, 2.0f);
LoglShader logl_LightCasters_lightingShader;
LoglShader logl_LightCasters_lampShader;
float logl_LightCasters_vertices[] = {
  // positions          // normals           // texture coords
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
unsigned int logl_LightCasters_VBO, logl_LightCasters_cubeVAO;
unsigned int logl_LightCasters_lightVAO, logl_LightCasters_diffuseMap, logl_LightCasters_specularMap;
bool logl_LightCasters_ifInitOnce = false;
static bool logl_LightCasters_dLightOn = true, logl_LightCasters_pLightOn = false, logl_LightCasters_sLightOn = false;
int logl_LC_RBpointer;

void logl_LightCasters_Init(){
  if(!logl_LightCasters_ifInitOnce){

    logl_LightCasters_lightingShader = LoglShader("learnOpenGL-tut/shaders/5.light_casters.vs", "learnOpenGL-tut/shaders/5.light_casters.fs");
    logl_LightCasters_lampShader = LoglShader("learnOpenGL-tut/shaders/5.lamp.vs", "learnOpenGL-tut/shaders/5.lamp.fs");

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_LightCasters_diffuseMap = loadTex_stb("textures/container2.png");
    logl_LightCasters_specularMap = loadTex_stb("textures/container2_specular.png");

    // shader configuration
    // --------------------
    logl_LightCasters_lightingShader.use();
    logl_LightCasters_lightingShader.setInt("material.diffuse", 1);
    logl_LightCasters_lightingShader.setInt("material.specular", 2);
    logl_LightCasters_lightingShader.setInt("dLightOn", 1);

    glGenVertexArrays(1, &logl_LightCasters_cubeVAO);
    glGenBuffers(1, &logl_LightCasters_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_LightCasters_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_LightCasters_vertices), logl_LightCasters_vertices, GL_STATIC_DRAW);

    glBindVertexArray(logl_LightCasters_cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &logl_LightCasters_lightVAO);
    glBindVertexArray(logl_LightCasters_lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_LightCasters_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_LightCasters_ifInitOnce = true;
  }
}

void logl_LightCasters_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    // be sure to activate shader when setting uniforms/drawing objects
    logl_LightCasters_lightingShader.use();
    logl_LightCasters_lightingShader.setFloat("material.shininess", 32.0f);
    logl_LightCasters_lightingShader.setVec3("viewPos", logl_cameraPos);


    // directional light
    logl_LightCasters_lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    logl_LightCasters_lightingShader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    logl_LightCasters_lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    logl_LightCasters_lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light
    logl_LightCasters_lightingShader.setVec3("pointLight.position", logl_LightCasters_lightPos);
    logl_LightCasters_lightingShader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    logl_LightCasters_lightingShader.setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
    logl_LightCasters_lightingShader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
    logl_LightCasters_lightingShader.setFloat("pointLight.constant", 1.0f);
    logl_LightCasters_lightingShader.setFloat("pointLight.linear", 0.09);
    logl_LightCasters_lightingShader.setFloat("pointLight.quadratic", 0.032);
    // spotLight
    logl_LightCasters_lightingShader.setVec3("spotLight.position", logl_cameraPos);
    logl_LightCasters_lightingShader.setVec3("spotLight.direction", logl_cameraFront);
    logl_LightCasters_lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    logl_LightCasters_lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    logl_LightCasters_lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    logl_LightCasters_lightingShader.setFloat("spotLight.constant", 1.0f);
    logl_LightCasters_lightingShader.setFloat("spotLight.linear", 0.09);
    logl_LightCasters_lightingShader.setFloat("spotLight.quadratic", 0.032);
    logl_LightCasters_lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    logl_LightCasters_lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_LightCasters_lightingShader.setMat4("projection", projection);
    logl_LightCasters_lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    logl_LightCasters_lightingShader.setMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_LightCasters_diffuseMap);
    // bind specular map
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_LightCasters_specularMap);

    // render the cube
    glBindVertexArray(logl_LightCasters_cubeVAO);
    for (unsigned int i = 0; i < 10; i++)
    {
      // calculate the model matrix for each object and pass it to shader before drawing
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      logl_LightCasters_lightingShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // also draw the lamp object
    logl_LightCasters_lampShader.use();
    logl_LightCasters_lampShader.setMat4("projection", projection);
    logl_LightCasters_lampShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, logl_LightCasters_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    logl_LightCasters_lampShader.setMat4("model", model);

    glBindVertexArray(logl_LightCasters_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);

    renderLOGL_LCwindow = true;
  }else{
    renderLOGL_LCwindow = false;
  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Light casters ////////////

/////////////// LearnOpenGL - Multiple lights ////////////
glm::vec3 logl_MultipleLights_lightPos(1.2f, 1.0f, 2.0f);
LoglShader logl_MultipleLights_lightingShader;
LoglShader logl_MultipleLights_lampShader;
float logl_MultipleLights_vertices[] = {
  // positions          // normals           // texture coords
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
// positions all containers
glm::vec3 logl_MultipleLights_cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
// positions of the point lights
glm::vec3 logl_MultipleLights_pointLightPositions[] = {
  glm::vec3( 0.7f,  0.2f,  2.0f),
  glm::vec3( 2.3f, -3.3f, -4.0f),
  glm::vec3(-4.0f,  2.0f, -12.0f),
  glm::vec3( 0.0f,  0.0f, -3.0f)
};
unsigned int logl_MultipleLights_VBO, logl_MultipleLights_cubeVAO;
unsigned int logl_MultipleLights_lightVAO, logl_MultipleLights_diffuseMap, logl_MultipleLights_specularMap;
bool logl_MultipleLights_ifInitOnce = false;

void logl_MultipleLights_Init(){
  if(!logl_MultipleLights_ifInitOnce){

    logl_MultipleLights_lightingShader = LoglShader("learnOpenGL-tut/shaders/6.multiple_lights.vs", "learnOpenGL-tut/shaders/6.multiple_lights.fs");
    logl_MultipleLights_lampShader = LoglShader("learnOpenGL-tut/shaders/6.lamp.vs", "learnOpenGL-tut/shaders/6.lamp.fs");

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_MultipleLights_diffuseMap = loadTex_stb("textures/container2.png");
    logl_MultipleLights_specularMap = loadTex_stb("textures/container2_specular.png");

    // shader configuration
    // --------------------
    logl_MultipleLights_lightingShader.use();
    logl_MultipleLights_lightingShader.setInt("material.diffuse", 1);
    logl_MultipleLights_lightingShader.setInt("material.specular", 2);

    glGenVertexArrays(1, &logl_MultipleLights_cubeVAO);
    glGenBuffers(1, &logl_MultipleLights_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_MultipleLights_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_MultipleLights_vertices), logl_MultipleLights_vertices, GL_STATIC_DRAW);

    glBindVertexArray(logl_MultipleLights_cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &logl_MultipleLights_lightVAO);
    glBindVertexArray(logl_MultipleLights_lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, logl_MultipleLights_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_MultipleLights_ifInitOnce = true;
  }
}

void logl_MultipleLights_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    // be sure to activate shader when setting uniforms/drawing objects
    logl_MultipleLights_lightingShader.use();
    logl_MultipleLights_lightingShader.setFloat("material.shininess", 32.0f);
    logl_MultipleLights_lightingShader.setVec3("viewPos", logl_cameraPos);


    // directional light
    logl_MultipleLights_lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    logl_MultipleLights_lightingShader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    logl_MultipleLights_lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    logl_MultipleLights_lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    logl_MultipleLights_lightingShader.setVec3("pointLights[0].position", logl_MultipleLights_pointLightPositions[0]);
    logl_MultipleLights_lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[0].constant", 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[0].linear", 0.09);
    logl_MultipleLights_lightingShader.setFloat("pointLights[0].quadratic", 0.032);
    // point light 2
    logl_MultipleLights_lightingShader.setVec3("pointLights[1].position", logl_MultipleLights_pointLightPositions[1]);
    logl_MultipleLights_lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[1].constant", 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[1].linear", 0.09);
    logl_MultipleLights_lightingShader.setFloat("pointLights[1].quadratic", 0.032);
    // point light 3
    logl_MultipleLights_lightingShader.setVec3("pointLights[2].position", logl_MultipleLights_pointLightPositions[2]);
    logl_MultipleLights_lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[2].constant", 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[2].linear", 0.09);
    logl_MultipleLights_lightingShader.setFloat("pointLights[2].quadratic", 0.032);
    // point light 4
    logl_MultipleLights_lightingShader.setVec3("pointLights[3].position", logl_MultipleLights_pointLightPositions[3]);
    logl_MultipleLights_lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    logl_MultipleLights_lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[3].constant", 1.0f);
    logl_MultipleLights_lightingShader.setFloat("pointLights[3].linear", 0.09);
    logl_MultipleLights_lightingShader.setFloat("pointLights[3].quadratic", 0.032);
    // spotLight
    logl_MultipleLights_lightingShader.setVec3("spotLight.position", logl_cameraPos);
    logl_MultipleLights_lightingShader.setVec3("spotLight.direction", logl_cameraFront);
    logl_MultipleLights_lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    logl_MultipleLights_lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    logl_MultipleLights_lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    logl_MultipleLights_lightingShader.setFloat("spotLight.constant", 1.0f);
    logl_MultipleLights_lightingShader.setFloat("spotLight.linear", 0.09);
    logl_MultipleLights_lightingShader.setFloat("spotLight.quadratic", 0.032);
    logl_MultipleLights_lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    logl_MultipleLights_lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_MultipleLights_lightingShader.setMat4("projection", projection);
    logl_MultipleLights_lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    logl_MultipleLights_lightingShader.setMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_MultipleLights_diffuseMap);
    // bind specular map
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_MultipleLights_specularMap);

    // render the cube
    glBindVertexArray(logl_MultipleLights_cubeVAO);
    for (unsigned int i = 0; i < 10; i++)
    {
      // calculate the model matrix for each object and pass it to shader before drawing
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      logl_MultipleLights_lightingShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // also draw the lamp object
    logl_MultipleLights_lampShader.use();
    logl_MultipleLights_lampShader.setMat4("projection", projection);
    logl_MultipleLights_lampShader.setMat4("view", view);


    // we now draw as many light bulbs as we have point lights.
    glBindVertexArray(logl_MultipleLights_lightVAO);
    for (unsigned int i = 0; i < 4; i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, logl_MultipleLights_pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
      logl_MultipleLights_lampShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Multiple lights ////////////

/////////////// LearnOpenGL - Model ////////////
LoglShader logl_Model_modelShader;
bool logl_Model_ifInitOnce = false;

void logl_Model_Init(){
  if(!logl_Model_ifInitOnce){

    logl_Model_modelShader = LoglShader("learnOpenGL-tut/shaders/1.model_loading.vs", "learnOpenGL-tut/shaders/1.model_loading.fs");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_Model_ifInitOnce = true;
  }
}
void logl_Model_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    if(multipleOutputsIndex == 1){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }else{
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // view/projection transformations
    logl_Model_modelShader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =  glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_Model_modelShader.setMat4("projection", projection);
    logl_Model_modelShader.setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
    logl_Model_modelShader.setMat4("model", model);
    nanosuit.Draw(logl_Model_modelShader);



    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Model ////////////

/////////////// LearnOpenGL - Depth testing ////////////
LoglShader logl_DepthTesting_shader;
float logl_DepthTesting_cubeVertices[] = {
  // positions          // texture Coords
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float logl_DepthTesting_planeVertices[] = {
  // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
  5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
  -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

  5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
  5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};
unsigned int logl_DepthTesting_cubeVAO, logl_DepthTesting_cubeVBO;
unsigned int logl_DepthTesting_planeVAO, logl_DepthTesting_planeVBO, logl_DepthTesting_cubeTexture, logl_DepthTesting_floorTexture;
bool logl_DepthTesting_ifInitOnce = false;

void logl_DepthTesting_Init(){
  if(!logl_DepthTesting_ifInitOnce){

    logl_DepthTesting_shader = LoglShader("learnOpenGL-tut/shaders/1.1.depth_testing.vs", "learnOpenGL-tut/shaders/1.1.depth_testing.fs");

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_DepthTesting_cubeTexture = loadTex_stb("textures/marble.jpg");
    logl_DepthTesting_floorTexture = loadTex_stb("textures/metal.png");

    // shader configuration
    // --------------------
    logl_DepthTesting_shader.use();
    logl_DepthTesting_shader.setInt("texture1", 1);

    glGenVertexArrays(1, &logl_DepthTesting_cubeVAO);
    glGenBuffers(1, &logl_DepthTesting_cubeVBO);
    glBindVertexArray(logl_DepthTesting_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_DepthTesting_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_DepthTesting_cubeVertices), &logl_DepthTesting_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    glGenVertexArrays(1, &logl_DepthTesting_planeVAO);
    glGenBuffers(1, &logl_DepthTesting_planeVBO);
    glBindVertexArray(logl_DepthTesting_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_DepthTesting_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_DepthTesting_planeVertices), &logl_DepthTesting_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_DepthTesting_ifInitOnce = true;
  }
}

void logl_DepthTesting_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    logl_DepthTesting_shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    logl_DepthTesting_shader.setMat4("view", view);
    logl_DepthTesting_shader.setMat4("projection", projection);

    //glDepthFunc(GL_ALWAYS);
    // cubes
    glBindVertexArray(logl_DepthTesting_cubeVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_DepthTesting_cubeTexture);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    logl_DepthTesting_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    logl_DepthTesting_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // floor
    glBindVertexArray(logl_DepthTesting_planeVAO);
    glBindTexture(GL_TEXTURE_2D, logl_DepthTesting_floorTexture);
    logl_DepthTesting_shader.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Depth testing ////////////

/////////////// LearnOpenGL - Stencil testing ////////////
LoglShader logl_StencilTesting_shader,logl_StencilTesting_shaderSingleColor;
float logl_StencilTesting_cubeVertices[] = {
  // positions          // texture Coords
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float logl_StencilTesting_planeVertices[] = {
  // positions          // texture Coords
  5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
  -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

  5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
  5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};
unsigned int logl_StencilTesting_cubeVAO, logl_StencilTesting_cubeVBO;
unsigned int logl_StencilTesting_planeVAO, logl_StencilTesting_planeVBO, logl_StencilTesting_cubeTexture, logl_StencilTesting_floorTexture;
bool logl_StencilTesting_ifInitOnce = false;

void logl_StencilTesting_Init(){
  if(!logl_StencilTesting_ifInitOnce){

    logl_StencilTesting_shader = LoglShader("learnOpenGL-tut/shaders/2.stencil_testing.vs", "learnOpenGL-tut/shaders/2.stencil_testing.fs");
    logl_StencilTesting_shaderSingleColor = LoglShader("learnOpenGL-tut/shaders/2.stencil_testing.vs", "learnOpenGL-tut/shaders/2.stencil_single_color.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_StencilTesting_cubeTexture = loadTex_stb("textures/marble.jpg");
    logl_StencilTesting_floorTexture = loadTex_stb("textures/metal.png");

    // shader configuration
    // --------------------
    logl_StencilTesting_shader.use();
    logl_StencilTesting_shader.setInt("texture1", 0);

    glGenVertexArrays(1, &logl_StencilTesting_cubeVAO);
    glGenBuffers(1, &logl_StencilTesting_cubeVBO);
    glBindVertexArray(logl_StencilTesting_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_StencilTesting_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_StencilTesting_cubeVertices), &logl_StencilTesting_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    // plane VAO

    glGenVertexArrays(1, &logl_StencilTesting_planeVAO);
    glGenBuffers(1, &logl_StencilTesting_planeVBO);
    glBindVertexArray(logl_StencilTesting_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_StencilTesting_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_StencilTesting_planeVertices), &logl_StencilTesting_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_StencilTesting_ifInitOnce = true;
  }
}

void logl_StencilTesting_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;


  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // don't forget to clear the stencil buffer!

    // set uniforms
    logl_StencilTesting_shaderSingleColor.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    logl_StencilTesting_shaderSingleColor.setMat4("view", view);
    logl_StencilTesting_shaderSingleColor.setMat4("projection", projection);

    logl_StencilTesting_shader.use();
    logl_StencilTesting_shader.setMat4("view", view);
    logl_StencilTesting_shader.setMat4("projection", projection);

    // draw floor as normal, but don't write the floor to the stencil buffer, we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
    glStencilMask(0x00);
    // floor
    glBindVertexArray(logl_StencilTesting_planeVAO);
    glBindTexture(GL_TEXTURE_2D, logl_StencilTesting_floorTexture);
    logl_StencilTesting_shader.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // 1st. render pass, draw objects as normal, writing to the stencil buffer
    // --------------------------------------------------------------------
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    // cubes
    glBindVertexArray(logl_StencilTesting_cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_StencilTesting_cubeTexture);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    logl_StencilTesting_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    logl_StencilTesting_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
    // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
    // the objects' size differences, making it look like borders.
    // -----------------------------------------------------------------------------------------------------------------------------
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    logl_StencilTesting_shaderSingleColor.use();
    float scale = 1.1;
    // cubes
    glBindVertexArray(logl_StencilTesting_cubeVAO);
    glBindTexture(GL_TEXTURE_2D, logl_StencilTesting_cubeTexture);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    logl_StencilTesting_shaderSingleColor.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    logl_StencilTesting_shaderSingleColor.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);


    glDisable(GL_STENCIL_TEST);
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Stencil testing ////////////

/////////////// LearnOpenGL - Blending ////////////
LoglShader logl_Blending_shader;
float logl_Blending_cubeVertices[] = {
  // positions          // texture Coords
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float logl_Blending_planeVertices[] = {
  // positions          // texture Coords
  5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
  -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

  5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
  5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};
float logl_Blending_transparentVertices[] = {
  // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
  0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
  0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
  1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

  0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
  1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
  1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};
unsigned int logl_Blending_cubeVAO, logl_Blending_cubeVBO;
unsigned int logl_Blending_planeVAO, logl_Blending_planeVBO;
unsigned int logl_Blending_transparentVAO, logl_Blending_transparentVBO;
unsigned int logl_Blending_cubeTexture,logl_Blending_floorTexture,logl_Blending_transparentTexture1,logl_Blending_transparentTexture2;
vector<glm::vec3> logl_Blending_vegetation
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3( 1.5f, 0.0f, 0.51f),
        glm::vec3( 0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3 (0.5f, 0.0f, -0.6f)
    };
vector<glm::vec3> logl_Blending_windows
{
  glm::vec3(-1.5f, 0.0f, -0.48f),
  glm::vec3( 1.5f, 0.0f, 0.51f),
  glm::vec3( 0.0f, 0.0f, 0.7f),
  glm::vec3(-0.3f, 0.0f, -2.3f),
  glm::vec3( 0.5f, 0.0f, -0.6f)
};
bool logl_Blending_ifInitOnce = false;

void logl_Blending_Init(){
  if(!logl_Blending_ifInitOnce){

    logl_Blending_shader = LoglShader("learnOpenGL-tut/shaders/3.2.blending.vs", "learnOpenGL-tut/shaders/3.2.blending.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_Blending_cubeTexture = logl_loadTex_stb("textures/marble.jpg", false);
    logl_Blending_floorTexture = logl_loadTex_stb("textures/metal.png", false);
    logl_Blending_transparentTexture1 = logl_loadTex_stb("textures/grass.png", false);
    logl_Blending_transparentTexture2 = logl_loadTex_stb("textures/window.png", false);

    // shader configuration
    // --------------------
    logl_Blending_shader.use();
    logl_Blending_shader.setInt("texture1", 1);

    glGenVertexArrays(1, &logl_Blending_cubeVAO);
    glGenBuffers(1, &logl_Blending_cubeVBO);
    glBindVertexArray(logl_Blending_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Blending_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Blending_cubeVertices), &logl_Blending_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glGenVertexArrays(1, &logl_Blending_planeVAO);
    glGenBuffers(1, &logl_Blending_planeVBO);
    glBindVertexArray(logl_Blending_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Blending_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Blending_planeVertices), &logl_Blending_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glGenVertexArrays(1, &logl_Blending_transparentVAO);
    glGenBuffers(1, &logl_Blending_transparentVBO);
    glBindVertexArray(logl_Blending_transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Blending_transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Blending_transparentVertices), logl_Blending_transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_Blending_ifInitOnce = true;
  }
}

void logl_Blending_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;
  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    // sort the transparent windows before rendering
    // ---------------------------------------------
    std::map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < logl_Blending_windows.size(); i++)
    {
      float distance = glm::length(logl_cameraPos - logl_Blending_windows[i]);
      sorted[distance] = logl_Blending_windows[i];
    }


    logl_Blending_shader.use();
    logl_Blending_shader.setInt("outPutNum", multipleOutputsIndex);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    logl_Blending_shader.setMat4("projection", projection);
    logl_Blending_shader.setMat4("view", view);
    // cubes
    glBindVertexArray(logl_Blending_cubeVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_Blending_cubeTexture);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    logl_Blending_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    logl_Blending_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // floor
    glBindVertexArray(logl_Blending_planeVAO);
    glBindTexture(GL_TEXTURE_2D, logl_Blending_floorTexture);
    model = glm::mat4(1.0f);
    logl_Blending_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // windows (from furthest to nearest)
    if(multipleOutputsIndex == 1){
      // vegetation
        glBindVertexArray(logl_Blending_transparentVAO);
        glBindTexture(GL_TEXTURE_2D, logl_Blending_transparentTexture1);
        for (GLuint i = 0; i < logl_Blending_vegetation.size(); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, logl_Blending_vegetation[i]);
            logl_Blending_shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }else{
      glBindVertexArray(logl_Blending_transparentVAO);
      glBindTexture(GL_TEXTURE_2D, logl_Blending_transparentTexture2);
      for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
      {
        model = glm::mat4(1.0f);
        model = glm::translate(model, it->second);
        logl_Blending_shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
      }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Blending ////////////

/////////////// LearnOpenGL - Face culling ////////////
LoglShader logl_FaceCulling_shader;
unsigned int logl_FaceCulling_VAO, logl_FaceCulling_VBO, logl_FaceCulling_CubeTexture;
float logl_FaceCulling_cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
};

bool logl_FaceCulling_ifInitOnce = false;

void logl_FaceCulling_Init(){
  if(!logl_FaceCulling_ifInitOnce){

    logl_FaceCulling_shader = LoglShader("learnOpenGL-tut/shaders/face_culling.vs", "learnOpenGL-tut/shaders/face_culling.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_FaceCulling_CubeTexture = loadTex_stb("textures/uvPanel.png");

    // shader configuration
    // --------------------
    logl_FaceCulling_shader.use();
    logl_FaceCulling_shader.setInt("texture1", 0);

    glGenVertexArrays(1, &logl_FaceCulling_VAO);
    glGenBuffers(1, &logl_FaceCulling_VBO);
    glBindVertexArray(logl_FaceCulling_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_FaceCulling_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_FaceCulling_cubeVertices), &logl_FaceCulling_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    logl_FaceCulling_ifInitOnce = true;
  }
}
void logl_FaceCulling_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    logl_FaceCulling_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    logl_FaceCulling_shader.setMat4("projection", projection);
    logl_FaceCulling_shader.setMat4("view", view);
    logl_FaceCulling_shader.setMat4("model", model);

    // cube
    glBindVertexArray(logl_FaceCulling_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_FaceCulling_CubeTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisable(GL_CULL_FACE);

    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}

/////////////// LearnOpenGL - Face culling ////////////

/////////////// LearnOpenGL - Framebuffers ////////////
LoglShader logl_Framebuffers_shader, logl_Framebuffers_screenShader;
float logl_Framebuffers_cubeVertices[] = {
  // positions          // texture Coords
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float logl_Framebuffers_planeVertices[] = {
  // positions          // texture Coords
  5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
  -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

  5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
  -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
  5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};
float logl_Framebuffers_quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
  // positions   // texCoords
  -1.0f,  1.0f,  0.0f, 1.0f,
  -1.0f, -1.0f,  0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 0.0f,

  -1.0f,  1.0f,  0.0f, 1.0f,
  1.0f, -1.0f,  1.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f
};
unsigned int logl_Framebuffers_cubeVAO, logl_Framebuffers_cubeVBO;
unsigned int logl_Framebuffers_planeVAO, logl_Framebuffers_planeVBO;
unsigned int logl_Framebuffers_quadVAO, logl_Framebuffers_quadVBO;
unsigned int logl_Framebuffers_cubeTexture,logl_Framebuffers_floorTexture;
unsigned int logl_Framebuffers_framebuffer, logl_Framebuffers_textureColorbuffer, logl_Framebuffers_rbo;

bool logl_Framebuffers_ifInitOnce = false;

void logl_Framebuffers_Init(){
  if(!logl_Framebuffers_ifInitOnce){

    logl_Framebuffers_shader = LoglShader("learnOpenGL-tut/shaders/5.1.framebuffers.vs", "learnOpenGL-tut/shaders/5.1.framebuffers.fs");
    logl_Framebuffers_screenShader = LoglShader("learnOpenGL-tut/shaders/5.1.framebuffers_screen.vs", "learnOpenGL-tut/shaders/5.1.framebuffers_screen.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_Framebuffers_cubeTexture = loadTex_stb("textures/container.jpg");
    logl_Framebuffers_floorTexture = loadTex_stb("textures/metal.png");

    // shader configuration
    // --------------------
    logl_Framebuffers_shader.use();
    logl_Framebuffers_shader.setInt("texture1", 1);

    logl_Framebuffers_screenShader.use();
    logl_Framebuffers_screenShader.setInt("screenTexture", 1);

    glGenVertexArrays(1, &logl_Framebuffers_cubeVAO);
    glGenBuffers(1, &logl_Framebuffers_cubeVBO);
    glBindVertexArray(logl_Framebuffers_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Framebuffers_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Framebuffers_cubeVertices), &logl_Framebuffers_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    ///
    glGenVertexArrays(1, &logl_Framebuffers_planeVAO);
    glGenBuffers(1, &logl_Framebuffers_planeVBO);
    glBindVertexArray(logl_Framebuffers_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Framebuffers_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Framebuffers_planeVertices), &logl_Framebuffers_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    ///
    glGenVertexArrays(1, &logl_Framebuffers_quadVAO);
    glGenBuffers(1, &logl_Framebuffers_quadVBO);
    glBindVertexArray(logl_Framebuffers_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Framebuffers_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Framebuffers_quadVertices), &logl_Framebuffers_quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &logl_Framebuffers_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_Framebuffers_framebuffer);
    // create a color attachment texture
    glGenTextures(1, &logl_Framebuffers_textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, logl_Framebuffers_textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_Framebuffers_textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &logl_Framebuffers_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, logl_Framebuffers_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, logl_Framebuffers_rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_Framebuffers_ifInitOnce = true;
  }
}

void logl_Framebuffers_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    // render
    // ------
    // bind to framebuffer and draw scene as we normally would to color texture
    glBindFramebuffer(GL_FRAMEBUFFER, logl_Framebuffers_framebuffer);
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
    glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    logl_Framebuffers_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    logl_Framebuffers_shader.setMat4("projection", projection);
    logl_Framebuffers_shader.setMat4("view", view);

    // cubes
    glBindVertexArray(logl_Framebuffers_cubeVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_Framebuffers_cubeTexture);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    logl_Framebuffers_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    logl_Framebuffers_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // floor
    glBindVertexArray(logl_Framebuffers_planeVAO);
    glBindTexture(GL_TEXTURE_2D, logl_Framebuffers_floorTexture);
    logl_Framebuffers_shader.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    logl_Framebuffers_screenShader.use();
    logl_Framebuffers_screenShader.setFloat("outputNumber", multipleOutputsIndex);
    glBindVertexArray(logl_Framebuffers_quadVAO);
    glBindTexture(GL_TEXTURE_2D, logl_Framebuffers_textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Framebuffers ////////////

/////////////// LearnOpenGL - Cubemaps ////////////
LoglShader logl_Cubemaps_shader, logl_Cubemaps_skyboxShader;
float logl_Cubemaps_cubeVertices[] = {
  // positions          // normals
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f

};
float logl_Cubemaps_skyboxVertices[] = {
  // positions
  -1.0f,  1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,

  -1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,

  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,

  -1.0f, -1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,

  -1.0f,  1.0f, -1.0f,
  1.0f,  1.0f, -1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f, -1.0f,

  -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
  1.0f, -1.0f,  1.0f
};
unsigned int logl_Cubemaps_cubeVAO, logl_Cubemaps_cubeVBO;
unsigned int logl_Cubemaps_skyboxVAO, logl_Cubemaps_skyboxVBO;
unsigned int logl_Cubemaps_cubeTexture,logl_Cubemaps_cubemapTexture;

bool logl_Cubemaps_ifInitOnce = false;

void logl_Cubemaps_Init(){
  if(!logl_Cubemaps_ifInitOnce){

    logl_Cubemaps_shader = LoglShader("learnOpenGL-tut/shaders/6.1.cubemaps.vs", "learnOpenGL-tut/shaders/6.1.cubemaps.fs");
    logl_Cubemaps_skyboxShader = LoglShader("learnOpenGL-tut/shaders/6.1.skybox.vs", "learnOpenGL-tut/shaders/6.1.skybox.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    logl_Cubemaps_cubeTexture = loadTex_stb("textures/container.jpg");

    // shader configuration
    // --------------------
    logl_Cubemaps_shader.use();
    logl_Cubemaps_shader.setInt("texture1", 1);
    logl_Cubemaps_shader.setInt("skybox", 2);

    logl_Cubemaps_skyboxShader.use();
    logl_Cubemaps_skyboxShader.setInt("skybox", 2);

    glGenVertexArrays(1, &logl_Cubemaps_cubeVAO);
    glGenBuffers(1, &logl_Cubemaps_cubeVBO);
    glBindVertexArray(logl_Cubemaps_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Cubemaps_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Cubemaps_cubeVertices), &logl_Cubemaps_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    ///
    glGenVertexArrays(1, &logl_Cubemaps_skyboxVAO);
    glGenBuffers(1, &logl_Cubemaps_skyboxVBO);
    glBindVertexArray(logl_Cubemaps_skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Cubemaps_skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Cubemaps_skyboxVertices), &logl_Cubemaps_skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_Cubemaps_ifInitOnce = true;
  }
}

void logl_Cubemaps_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }


    glEnable(GL_DEPTH_TEST);

    logl_Cubemaps_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    if(multipleOutputsIndex > 1)
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    logl_Cubemaps_shader.setMat4("model", model);
    logl_Cubemaps_shader.setMat4("projection", projection);
    logl_Cubemaps_shader.setMat4("view", view);
    logl_Cubemaps_shader.setVec3("cameraPos", logl_cameraPos);
    logl_Cubemaps_shader.setFloat("outputNumber", multipleOutputsIndex);

    // cubes
    glBindVertexArray(logl_Cubemaps_cubeVAO);

    if(multipleOutputsIndex == 1){
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, logl_Cubemaps_cubeTexture);
    }
    if(multipleOutputsIndex == 2){
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_CUBE_MAP, logl_Cubemaps_cubeTexture);
    }
    if(multipleOutputsIndex == 3){
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_CUBE_MAP, logl_Cubemaps_cubeTexture);
    }
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    if(multipleOutputsIndex > 1){
      // render the loaded model
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(2.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
      model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
      logl_Cubemaps_shader.setMat4("model", model);
      nanosuit.Draw(logl_Cubemaps_shader);
    }

    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    logl_Cubemaps_skyboxShader.use();
    view = glm::mat4(glm::mat3(glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp))); // remove translation from the view matrix
    logl_Cubemaps_skyboxShader.setMat4("view", view);
    logl_Cubemaps_skyboxShader.setMat4("projection", projection);

    // skybox cube
    glBindVertexArray(logl_Cubemaps_skyboxVAO);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, logl_Cubemaps_cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Cubemaps ////////////

/////////////// LearnOpenGL - Advanced GLSL ////////////
LoglShader logl_AdvancedGLSL_shaderRed, logl_AdvancedGLSL_shaderGreen, logl_AdvancedGLSL_shaderBlue, logl_AdvancedGLSL_shaderYellow;
float logl_AdvancedGLSL_cubeVertices[] = {
  // positions
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f, -0.5f,  0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,

  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,

  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,

  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f,  0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
};
unsigned int logl_AdvancedGLSL_cubeVAO, logl_AdvancedGLSL_cubeVBO;
unsigned int logl_AdvancedGLSL_uniformBlockIndexRed, logl_AdvancedGLSL_uniformBlockIndexGreen, logl_AdvancedGLSL_uniformBlockIndexBlue, logl_AdvancedGLSL_uniformBlockIndexYellow;
unsigned int logl_AdvancedGLSL_uboMatrices;

bool logl_AdvancedGLSL_ifInitOnce = false;

void logl_AdvancedGLSL_Init(){
  if(!logl_AdvancedGLSL_ifInitOnce){

    logl_AdvancedGLSL_shaderRed = LoglShader("learnOpenGL-tut/shaders/8.advanced_glsl.vs", "learnOpenGL-tut/shaders/8.red.fs");
    logl_AdvancedGLSL_shaderGreen = LoglShader("learnOpenGL-tut/shaders/8.advanced_glsl.vs", "learnOpenGL-tut/shaders/8.green.fs");
    logl_AdvancedGLSL_shaderBlue = LoglShader("learnOpenGL-tut/shaders/8.advanced_glsl.vs", "learnOpenGL-tut/shaders/8.blue.fs");
    logl_AdvancedGLSL_shaderYellow = LoglShader("learnOpenGL-tut/shaders/8.advanced_glsl.vs", "learnOpenGL-tut/shaders/8.yellow.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);



    glGenVertexArrays(1, &logl_AdvancedGLSL_cubeVAO);
    glGenBuffers(1, &logl_AdvancedGLSL_cubeVBO);
    glBindVertexArray(logl_AdvancedGLSL_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_AdvancedGLSL_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_AdvancedGLSL_cubeVertices), &logl_AdvancedGLSL_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // configure a uniform buffer object
    // ---------------------------------
    // first. We get the relevant block indices
    logl_AdvancedGLSL_uniformBlockIndexRed = glGetUniformBlockIndex(logl_AdvancedGLSL_shaderRed.ID, "Matrices");
    logl_AdvancedGLSL_uniformBlockIndexGreen = glGetUniformBlockIndex(logl_AdvancedGLSL_shaderGreen.ID, "Matrices");
    logl_AdvancedGLSL_uniformBlockIndexBlue = glGetUniformBlockIndex(logl_AdvancedGLSL_shaderBlue.ID, "Matrices");
    logl_AdvancedGLSL_uniformBlockIndexYellow = glGetUniformBlockIndex(logl_AdvancedGLSL_shaderYellow.ID, "Matrices");
    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(logl_AdvancedGLSL_shaderRed.ID, logl_AdvancedGLSL_uniformBlockIndexRed, 0);
    glUniformBlockBinding(logl_AdvancedGLSL_shaderGreen.ID, logl_AdvancedGLSL_uniformBlockIndexGreen, 0);
    glUniformBlockBinding(logl_AdvancedGLSL_shaderBlue.ID, logl_AdvancedGLSL_uniformBlockIndexBlue, 0);
    glUniformBlockBinding(logl_AdvancedGLSL_shaderYellow.ID, logl_AdvancedGLSL_uniformBlockIndexYellow, 0);

    glGenBuffers(1, &logl_AdvancedGLSL_uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, logl_AdvancedGLSL_uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, logl_AdvancedGLSL_uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, logl_AdvancedGLSL_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_AdvancedGLSL_ifInitOnce = true;
  }
}

void logl_AdvancedGLSL_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }


    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glBindBuffer(GL_UNIFORM_BUFFER, logl_AdvancedGLSL_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // draw 4 cubes
    // RED
    glBindVertexArray(logl_AdvancedGLSL_cubeVAO);
    logl_AdvancedGLSL_shaderRed.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
    logl_AdvancedGLSL_shaderRed.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // GREEN
    logl_AdvancedGLSL_shaderGreen.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
    logl_AdvancedGLSL_shaderGreen.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // YELLOW
    logl_AdvancedGLSL_shaderYellow.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
    logl_AdvancedGLSL_shaderYellow.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // BLUE
    logl_AdvancedGLSL_shaderBlue.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
    logl_AdvancedGLSL_shaderBlue.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Advanced GLSL ////////////

/////////////// LearnOpenGL - Geometry Shader ////////////
LoglShader logl_GeometryShader_shader,logl_GeometryShader_mShader, logl_GeometryShader_defShader, logl_GeometryShader_normalShader;
float logl_GeometryShader_points[] = {
  -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
  -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
};
unsigned int logl_GeometryShader_VAO, logl_GeometryShader_VBO;

bool logl_GeometryShader_ifInitOnce = false;

void logl_GeometryShader_Init(){
  if(!logl_GeometryShader_ifInitOnce){

    logl_GeometryShader_shader = LoglShader("learnOpenGL-tut/shaders/9.1.geometry_shader.vs", "learnOpenGL-tut/shaders/9.1.geometry_shader.fs", "learnOpenGL-tut/shaders/9.1.geometry_shader.gs");
    logl_GeometryShader_mShader = LoglShader("learnOpenGL-tut/shaders/9.2.geometry_shader.vs", "learnOpenGL-tut/shaders/9.2.geometry_shader.fs", "learnOpenGL-tut/shaders/9.2.geometry_shader.gs");
    logl_GeometryShader_defShader = LoglShader("learnOpenGL-tut/shaders/9.3.default.vs", "learnOpenGL-tut/shaders/9.3.default.fs");
    logl_GeometryShader_normalShader = LoglShader("learnOpenGL-tut/shaders/9.3.normal_visualization.vs", "learnOpenGL-tut/shaders/9.3.normal_visualization.fs", "learnOpenGL-tut/shaders/9.3.normal_visualization.gs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glGenBuffers(1, &logl_GeometryShader_VBO);
    glGenVertexArrays(1, &logl_GeometryShader_VAO);
    glBindVertexArray(logl_GeometryShader_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_GeometryShader_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_GeometryShader_points), &logl_GeometryShader_points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    logl_GeometryShader_ifInitOnce = true;
  }
}

void logl_GeometryShader_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }


    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 100.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);

    if(multipleOutputsIndex == 1){
      // draw points
      logl_GeometryShader_shader.use();
      logl_GeometryShader_shader.setMat4("projection", projection);
      logl_GeometryShader_shader.setMat4("view", view);
      glBindVertexArray(logl_GeometryShader_VAO);
      glDrawArrays(GL_POINTS, 0, 4);
    }

    if(multipleOutputsIndex == 2){
      // configure transformation matrices
      model = glm::translate(model, glm::vec3(0.0f, -1.75f, -1.0f)); // translate it down so it's at the center of the scene
      model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
      logl_GeometryShader_mShader.use();
      logl_GeometryShader_mShader.setMat4("projection", projection);
      logl_GeometryShader_mShader.setMat4("view", view);
      logl_GeometryShader_mShader.setMat4("model", model);
      // add time component to geometry shader in the form of a uniform
      logl_GeometryShader_mShader.setFloat("time", glutGet(GLUT_ELAPSED_TIME)*0.001);
      // draw model
      nanosuit.Draw(logl_GeometryShader_mShader);
    }

    if(multipleOutputsIndex == 3){
      model = glm::translate(model, glm::vec3(0.0f, -1.75f, -1.0f)); // translate it down so it's at the center of the scene
      model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
      logl_GeometryShader_defShader.use();
      logl_GeometryShader_defShader.setMat4("projection", projection);
      logl_GeometryShader_defShader.setMat4("view", view);
      logl_GeometryShader_defShader.setMat4("model", model);
      // draw model
      nanosuit.Draw(logl_GeometryShader_defShader);

      logl_GeometryShader_normalShader.use();
      logl_GeometryShader_normalShader.setMat4("projection", projection);
      logl_GeometryShader_normalShader.setMat4("view", view);
      logl_GeometryShader_normalShader.setMat4("model", model);

      nanosuit.Draw(logl_GeometryShader_normalShader);
    }

    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Geometry Shader ////////////

/////////////// LearnOpenGL - Instancing ////////////
LoglShader logl_Instancing_shader, logl_Instancing_mShader,logl_Instancing_mShader2;
glm::vec2 translations[100];
int logl_Instancing_index = 0;
float logl_Instancing_offset = 0.1f;
float logl_Instancing_quadVertices[] = {
  // positions     // colors
  -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
  0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
  -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

  -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
  0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
  0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};
unsigned int logl_Instancing_quadVAO, logl_Instancing_quadVBO, logl_Instancing_instanceVBO;
unsigned int logl_Instancing_amount = 1000, logl_Instancing_amount2 = 100000, logl_Instancing_buffer;
glm::mat4* logl_Instancing_modelMatrices;
glm::mat4* logl_Instancing_modelMatrices2;

bool logl_Instancing_ifInitOnce = false;

void logl_Instancing_Init(){
  if(!logl_Instancing_ifInitOnce){

    for (int y = -10; y < 10; y += 2)
    {
      for (int x = -10; x < 10; x += 2)
      {
        glm::vec2 translation;
        translation.x = (float)x / 10.0f + logl_Instancing_offset;
        translation.y = (float)y / 10.0f + logl_Instancing_offset;
        translations[logl_Instancing_index++] = translation;
      }
    }

    logl_Instancing_shader = LoglShader("learnOpenGL-tut/shaders/10.1.instancing.vs", "learnOpenGL-tut/shaders/10.1.instancing.fs");
    logl_Instancing_mShader = LoglShader("learnOpenGL-tut/shaders/10.2.instancing.vs", "learnOpenGL-tut/shaders/10.2.instancing.fs");
    logl_Instancing_mShader2 = LoglShader("learnOpenGL-tut/shaders/10.3.asteroids.vs", "learnOpenGL-tut/shaders/10.3.asteroids.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glGenBuffers(1, &logl_Instancing_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Instancing_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &logl_Instancing_quadVAO);
    glGenBuffers(1, &logl_Instancing_quadVBO);
    glBindVertexArray(logl_Instancing_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Instancing_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_Instancing_quadVertices), logl_Instancing_quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    // also set instance data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Instancing_instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.


    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    logl_Instancing_modelMatrices = new glm::mat4[logl_Instancing_amount];
    srand(glutGet(GLUT_ELAPSED_TIME)* 0.002); // initialize random seed
    float radius = 12.5;
    float offset = 1.25f;
    for (unsigned int i = 0; i < logl_Instancing_amount; i++)
    {
      glm::mat4 model = glm::mat4(1.0f);
      // 1. translation: displace along circle with 'radius' in range [-offset, offset]
      float angle = (float)i / (float)logl_Instancing_amount * 360.0f;
      float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float x = sin(angle) * radius + displacement;
      displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
      displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float z = cos(angle) * radius + displacement;
      model = glm::translate(model, glm::vec3(x, y-3, z-20));

      // 2. scale: Scale between 0.05 and 0.25f
      float scale = (rand() % 20) / 100.0f + 0.05;
      model = glm::scale(model, glm::vec3(scale/4));

      // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
      float rotAngle = (rand() % 360);
      model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

      // 4. now add to list of matrices
      logl_Instancing_modelMatrices[i] = model;
    }

    logl_Instancing_modelMatrices2 = new glm::mat4[logl_Instancing_amount2];
    radius *= 4;
    offset *= 10;
    for (unsigned int i = 0; i < logl_Instancing_amount2; i++)
    {
      glm::mat4 model = glm::mat4(1.0f);
      // 1. translation: displace along circle with 'radius' in range [-offset, offset]
      float angle = (float)i / (float)logl_Instancing_amount2 * 360.0f;
      float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float x = sin(angle) * radius + displacement;
      displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
      displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float z = cos(angle) * radius + displacement;
      model = glm::translate(model, glm::vec3(x, y-10, z-60));

      // 2. scale: Scale between 0.05 and 0.25f
      float scale = (rand() % 20) / 100.0f + 0.05;
      model = glm::scale(model, glm::vec3(scale/3));

      // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
      float rotAngle = (rand() % 360);
      model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

      // 4. now add to list of matrices
      logl_Instancing_modelMatrices2[i] = model;
    }
    // configure instanced array
    // -------------------------
    glGenBuffers(1, &logl_Instancing_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Instancing_buffer);
    glBufferData(GL_ARRAY_BUFFER, logl_Instancing_amount2 * sizeof(glm::mat4), &logl_Instancing_modelMatrices2[0], GL_STATIC_DRAW);

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // -----------------------------------------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < rock.meshes.size(); i++)
    {
      unsigned int VAO = rock.meshes[i].VAOm;
      glBindVertexArray(VAO);
      // set attribute pointers for matrix (4 times vec4)
      glEnableVertexAttribArray(3);
      glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
      glEnableVertexAttribArray(4);
      glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
      glEnableVertexAttribArray(5);
      glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
      glEnableVertexAttribArray(6);
      glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

      glVertexAttribDivisor(3, 1);
      glVertexAttribDivisor(4, 1);
      glVertexAttribDivisor(5, 1);
      glVertexAttribDivisor(6, 1);

      glBindVertexArray(0);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_Instancing_ifInitOnce = true;
  }
}

void logl_Instancing_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;


  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);


    if(multipleOutputsIndex == 1 || multipleOutputsIndex == 2 ){
      // draw 100 instanced quads
      logl_Instancing_shader.use();
      logl_Instancing_shader.setFloat("outputNumVs", multipleOutputsIndex);
      logl_Instancing_shader.setMat4("projection", projection);
      logl_Instancing_shader.setMat4("view", view);
      glBindVertexArray(logl_Instancing_quadVAO);
      glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
      glBindVertexArray(0);
    }

    if(multipleOutputsIndex == 3){
      logl_Instancing_mShader.use();
      logl_Instancing_mShader.setMat4("projection", projection);
      logl_Instancing_mShader.setMat4("view", view);

      // draw planet
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, -4.0f, -20.0f));
      model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
      logl_Instancing_mShader.setMat4("model", model);
      planet.Draw(logl_Instancing_mShader);

      // draw meteorites
      for (unsigned int i = 0; i < logl_Instancing_amount; i++)
      {
        logl_Instancing_mShader.setMat4("model", logl_Instancing_modelMatrices[i]);
        rock.Draw(logl_Instancing_mShader);
      }
    }

    if(multipleOutputsIndex == 4){
      logl_Instancing_mShader2.use();
      logl_Instancing_mShader2.setMat4("projection", projection);
      logl_Instancing_mShader2.setMat4("view", view);
      logl_Instancing_mShader.use();
      logl_Instancing_mShader.setMat4("projection", projection);
      logl_Instancing_mShader.setMat4("view", view);

      // draw planet
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, -11.0f, -60.0f));
      model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
      logl_Instancing_mShader.setMat4("model", model);
      planet.Draw(logl_Instancing_mShader);

      // draw meteorites
      logl_Instancing_mShader2.use();
      logl_Instancing_mShader2.setInt("texture_diffuse1", 1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
      for (unsigned int i = 0; i < rock.meshes.size(); i++)
      {
        glBindVertexArray(rock.meshes[i].VAOm);
        glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indicesm.size(), GL_UNSIGNED_INT, 0, logl_Instancing_amount2);
        glBindVertexArray(0);
      }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Instancing ////////////

/////////////// LearnOpenGL - Anti Aliasing ////////////
LoglShader logl_AntiAliasing_shader, logl_AntiAliasing_screenShader;
// Set the object data (buffers, vertex attributes)
float logl_AntiAliasing_cubeVertices[] = {
  // positions
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f, -0.5f,  0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,

  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,

  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,

  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f,  0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f
};
float logl_AntiAliasing_quadVertices[] = {   // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
  // positions   // texCoords
  -1.0f,  1.0f,  0.0f, 1.0f,
  -1.0f, -1.0f,  0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 0.0f,

  -1.0f,  1.0f,  0.0f, 1.0f,
  1.0f, -1.0f,  1.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f
};
unsigned int logl_AntiAliasing_cubeVAO, logl_AntiAliasing_cubeVBO;
unsigned int logl_AntiAliasing_quadVAO, logl_AntiAliasing_quadVBO;
unsigned int logl_AntiAliasing_framebuffer;
unsigned int logl_AntiAliasing_textureColorBufferMultiSampled;
unsigned int logl_AntiAliasing_rbo, logl_AntiAliasing_intermediateFBO, logl_AntiAliasing_screenTexture;

bool logl_AntiAliasing_ifInitOnce = false;

void logl_AntiAliasing_Init(){
  if(!logl_AntiAliasing_ifInitOnce){

    logl_AntiAliasing_shader = LoglShader("learnOpenGL-tut/shaders/11.anti_aliasing.vs", "learnOpenGL-tut/shaders/11.anti_aliasing.fs");
    logl_AntiAliasing_screenShader = LoglShader("learnOpenGL-tut/shaders/11.aa_post.vs", "learnOpenGL-tut/shaders/11.aa_post.fs");

    // shader configuration
    // --------------------
    logl_AntiAliasing_screenShader.use();
    logl_AntiAliasing_screenShader.setInt("screenTexture", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // setup cube VAO
    glGenVertexArrays(1, &logl_AntiAliasing_cubeVAO);
    glGenBuffers(1, &logl_AntiAliasing_cubeVBO);
    glBindVertexArray(logl_AntiAliasing_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_AntiAliasing_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_AntiAliasing_cubeVertices), &logl_AntiAliasing_cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // setup screen VAO
    glGenVertexArrays(1, &logl_AntiAliasing_quadVAO);
    glGenBuffers(1, &logl_AntiAliasing_quadVBO);
    glBindVertexArray(logl_AntiAliasing_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_AntiAliasing_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_AntiAliasing_quadVertices), &logl_AntiAliasing_quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // configure MSAA framebuffer
    // --------------------------
    glGenFramebuffers(1, &logl_AntiAliasing_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_AntiAliasing_framebuffer);
    // create a multisampled color attachment texture
    glGenTextures(1, &logl_AntiAliasing_textureColorBufferMultiSampled);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, logl_AntiAliasing_textureColorBufferMultiSampled);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, SCR_WIDTH, SCR_HEIGHT, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, logl_AntiAliasing_textureColorBufferMultiSampled, 0);
    // create a (also multisampled) renderbuffer object for depth and stencil attachments
    glGenRenderbuffers(1, &logl_AntiAliasing_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, logl_AntiAliasing_rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, logl_AntiAliasing_rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure second post-processing framebuffer
    glGenFramebuffers(1, &logl_AntiAliasing_intermediateFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_AntiAliasing_intermediateFBO);
    // create a color attachment texture
    glGenTextures(1, &logl_AntiAliasing_screenTexture);
    glBindTexture(GL_TEXTURE_2D, logl_AntiAliasing_screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_AntiAliasing_screenTexture, 0);	// we only need a color buffer

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_AntiAliasing_ifInitOnce = true;
  }
}

void logl_AntiAliasing_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }



    // 1. draw scene as normal in multisampled buffers
    glBindFramebuffer(GL_FRAMEBUFFER, logl_AntiAliasing_framebuffer);
    glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);

    logl_AntiAliasing_shader.use();
    logl_AntiAliasing_shader.setMat4("projection", projection);
    logl_AntiAliasing_shader.setMat4("view", view);
    logl_AntiAliasing_shader.setMat4("model", model);

    glBindVertexArray(logl_AntiAliasing_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // 2. now blit multisampled buffer(s) to normal colorbuffer of intermediate FBO. Image is stored in screenTexture
    glBindFramebuffer(GL_READ_FRAMEBUFFER, logl_AntiAliasing_framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, logl_AntiAliasing_intermediateFBO);
    glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // 3. now render quad with scene's visuals as its texture image
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    // draw Screen quad
    logl_AntiAliasing_screenShader.use();
    glBindVertexArray(logl_AntiAliasing_quadVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_AntiAliasing_screenTexture); // use the now resolved color attachment as the quad's texture
    glDrawArrays(GL_TRIANGLES, 0, 6);


    glActiveTexture(GL_TEXTURE0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Anti Aliasing ////////////

/////////////// LearnOpenGL - Advanced Lighting ////////////
LoglShader logl_AdvancedLighting_shader;
float logl_AdvancedLighting_planeVertices[] = {
  // positions            // normals         // texcoords
  10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
  -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
  -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

  10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
  -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
  10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
};
unsigned int logl_AdvancedLighting_planeVAO, logl_AdvancedLighting_planeVBO, logl_AdvancedLighting_floorTexture;
glm::vec3 logl_AdvancedLighting_lightPos(0.0f, 0.0f, 0.0f);

bool logl_AdvancedLighting_ifInitOnce = false;

void logl_AdvancedLighting_Init(){
  if(!logl_AdvancedLighting_ifInitOnce){

    logl_AdvancedLighting_shader = LoglShader("learnOpenGL-tut/shaders/1.advanced_lighting.vs", "learnOpenGL-tut/shaders/1.advanced_lighting.fs");
    logl_AdvancedLighting_floorTexture = logl_loadTex_stb("textures/wood.png", false);
    // shader configuration
    // --------------------
    logl_AdvancedLighting_shader.use();
    logl_AdvancedLighting_shader.setInt("floorTexture", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setup floor VAO
    glGenVertexArrays(1, &logl_AdvancedLighting_planeVAO);
    glGenBuffers(1, &logl_AdvancedLighting_planeVBO);
    glBindVertexArray(logl_AdvancedLighting_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_AdvancedLighting_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_AdvancedLighting_planeVertices), logl_AdvancedLighting_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_AdvancedLighting_ifInitOnce = true;
  }
}

void logl_AdvancedLighting_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);

    logl_AdvancedLighting_shader.use();
    logl_AdvancedLighting_shader.setMat4("projection", projection);
    logl_AdvancedLighting_shader.setMat4("view", view);
    logl_AdvancedLighting_shader.setMat4("model", model);
    // set light uniforms
    logl_AdvancedLighting_shader.setVec3("viewPos", logl_cameraPos);
    logl_AdvancedLighting_shader.setVec3("lightPos", logl_AdvancedLighting_lightPos);
    if(multipleOutputsIndex == 1)
    logl_AdvancedLighting_shader.setInt("blinn", 0);
    if(multipleOutputsIndex == 2)
    logl_AdvancedLighting_shader.setInt("blinn", 1);
    // floor
    glBindVertexArray(logl_AdvancedLighting_planeVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_AdvancedLighting_floorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Advanced Lighting ////////////

/////////////// LearnOpenGL - Gamma Correction ////////////
LoglShader logl_GammaCorrection_shader;
float logl_GammaCorrection_planeVertices[] = {
  // positions            // normals         // texcoords
  10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
  -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
  -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

  10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
  -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
  10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
};
unsigned int logl_GammaCorrection_planeVAO, logl_GammaCorrection_planeVBO, logl_GammaCorrection_floorTexture, logl_GammaCorrection_floorTextureGammaCorrected;
glm::vec3 logl_GammaCorrection_lightPositions[] = {
  glm::vec3(-3.0f, 0.0f, 0.0f),
  glm::vec3(-1.0f, 0.0f, 0.0f),
  glm::vec3 (1.0f, 0.0f, 0.0f),
  glm::vec3 (3.0f, 0.0f, 0.0f)
};
glm::vec3 logl_GammaCorrection_lightColors[] = {
  glm::vec3(0.25),
  glm::vec3(0.50),
  glm::vec3(0.75),
  glm::vec3(1.00)
};
bool gammaEnabled;

bool logl_GammaCorrection_ifInitOnce = false;

void logl_GammaCorrection_Init(){
  if(!logl_GammaCorrection_ifInitOnce){

    logl_GammaCorrection_shader = LoglShader("learnOpenGL-tut/shaders/2.gamma_correction.vs", "learnOpenGL-tut/shaders/2.gamma_correction.fs");
    logl_GammaCorrection_floorTexture = logl_loadTex_stb("textures/wood.png", false);
    logl_GammaCorrection_floorTextureGammaCorrected = logl_loadTex_stb("textures/wood.png", true);
    // shader configuration
    // --------------------
    logl_GammaCorrection_shader.use();
    logl_GammaCorrection_shader.setInt("floorTexture", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setup floor VAO
    glGenVertexArrays(1, &logl_GammaCorrection_planeVAO);
    glGenBuffers(1, &logl_GammaCorrection_planeVBO);
    glBindVertexArray(logl_GammaCorrection_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_GammaCorrection_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_GammaCorrection_planeVertices), logl_GammaCorrection_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_GammaCorrection_ifInitOnce = true;
  }
}

void logl_GammaCorrection_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }


    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);

    logl_GammaCorrection_shader.use();
    logl_GammaCorrection_shader.setMat4("projection", projection);
    logl_GammaCorrection_shader.setMat4("view", view);
    logl_GammaCorrection_shader.setMat4("model", model);
    if(multipleOutputsIndex == 1)
    gammaEnabled = false;
    if(multipleOutputsIndex == 2)
    gammaEnabled = true;
    // set light uniforms
    glUniform3fv(glGetUniformLocation(logl_GammaCorrection_shader.ID, "lightPositions"), 4, &logl_GammaCorrection_lightPositions[0][0]);
    glUniform3fv(glGetUniformLocation(logl_GammaCorrection_shader.ID, "lightColors"), 4, &logl_GammaCorrection_lightColors[0][0]);
    logl_GammaCorrection_shader.setVec3("viewPos", logl_cameraPos);
    logl_GammaCorrection_shader.setInt("gamma", gammaEnabled);
    // floor
    glBindVertexArray(logl_GammaCorrection_planeVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gammaEnabled ? logl_GammaCorrection_floorTextureGammaCorrected : logl_GammaCorrection_floorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
/////////////// LearnOpenGL - Gamma Correction ////////////

/////////////// LearnOpenGL - Shadow Mapping ////////////
void logl_ShadowMapping_renderScene(const LoglShader &shader);
void logl_ShadowMapping_renderCube();
void logl_ShadowMapping_renderQuad();
LoglShader logl_ShadowMapping_shader,logl_ShadowMapping_simpleDepthShader,logl_ShadowMapping_debugDepthQuad;
float logl_ShadowMapping_planeVertices[] = {
  // positions            // normals         // texcoords
  25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
  -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
  -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

  25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
  -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
  25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
};
unsigned int logl_ShadowMapping_planeVBO,logl_ShadowMapping_planeVAO, logl_ShadowMapping_woodTexture, logl_ShadowMapping_depthMap,logl_ShadowMapping_depthMapFBO;
const unsigned int logl_ShadowMapping_SHADOW_WIDTH = 1024, logl_ShadowMapping_SHADOW_HEIGHT = 1024;
glm::vec3 logl_ShadowMapping_lightPos(-2.0f, 4.0f, -1.0f);

bool logl_ShadowMapping_ifInitOnce = false;

void logl_ShadowMapping_Init(){
  if(!logl_ShadowMapping_ifInitOnce){

    logl_ShadowMapping_shader = LoglShader("learnOpenGL-tut/shaders/3.1.3.shadow_mapping.vs", "learnOpenGL-tut/shaders/3.1.3.shadow_mapping.fs");
    logl_ShadowMapping_simpleDepthShader = LoglShader("learnOpenGL-tut/shaders/3.1.3.shadow_mapping_depth.vs", "learnOpenGL-tut/shaders/3.1.3.shadow_mapping_depth.fs");
    logl_ShadowMapping_debugDepthQuad = LoglShader("learnOpenGL-tut/shaders/3.1.3.debug_quad.vs", "learnOpenGL-tut/shaders/3.1.3.debug_quad_depth.fs");

    logl_ShadowMapping_woodTexture = logl_loadTex_stb("textures/wood.png");
    // shader configuration
    // --------------------
    logl_ShadowMapping_shader.use();
    logl_ShadowMapping_shader.setInt("diffuseTexture", 1);
    logl_ShadowMapping_shader.setInt("shadowMap", 2);
    logl_ShadowMapping_debugDepthQuad.use();
    logl_ShadowMapping_debugDepthQuad.setInt("depthMap", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &logl_ShadowMapping_planeVAO);
    glGenBuffers(1, &logl_ShadowMapping_planeVBO);
    glBindVertexArray(logl_ShadowMapping_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_ShadowMapping_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logl_ShadowMapping_planeVertices), logl_ShadowMapping_planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    // configure depth map FBO
    // -----------------------
    glGenFramebuffers(1, &logl_ShadowMapping_depthMapFBO);
    // create depth texture
    glGenTextures(1, &logl_ShadowMapping_depthMap);
    glBindTexture(GL_TEXTURE_2D, logl_ShadowMapping_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, logl_ShadowMapping_SHADOW_WIDTH, logl_ShadowMapping_SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, logl_ShadowMapping_depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, logl_ShadowMapping_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_ShadowMapping_ifInitOnce = true;
  }
}

void logl_ShadowMapping_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. render depth of scene to texture (from light's perspective)
    // --------------------------------------------------------------
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    //lightProjection = glm::perspective(glm::radians(logl_fov), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(logl_ShadowMapping_lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    logl_ShadowMapping_simpleDepthShader.use();
    logl_ShadowMapping_simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, logl_ShadowMapping_SHADOW_WIDTH, logl_ShadowMapping_SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_ShadowMapping_depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_ShadowMapping_woodTexture);
    logl_ShadowMapping_renderScene(logl_ShadowMapping_simpleDepthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // reset viewport
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. render scene as normal using the generated depth/shadow map
    // --------------------------------------------------------------
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    logl_ShadowMapping_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_ShadowMapping_shader.setMat4("projection", projection);
    logl_ShadowMapping_shader.setMat4("view", view);
    // set light uniforms
    logl_ShadowMapping_shader.setVec3("viewPos", logl_cameraPos);
    logl_ShadowMapping_shader.setVec3("lightPos", logl_ShadowMapping_lightPos);
    logl_ShadowMapping_shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_ShadowMapping_woodTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_ShadowMapping_depthMap);
    logl_ShadowMapping_renderScene(logl_ShadowMapping_shader);

    // render Depth map to quad for visual debugging
    // ---------------------------------------------
    logl_ShadowMapping_debugDepthQuad.use();
    logl_ShadowMapping_debugDepthQuad.setFloat("near_plane", near_plane);
    logl_ShadowMapping_debugDepthQuad.setFloat("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_ShadowMapping_depthMap);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renders the 3D scene
// --------------------
void logl_ShadowMapping_renderScene(const LoglShader &shader)
{
  // floor
  glm::mat4 model = glm::mat4(1.0f);
  shader.setMat4("model", model);
  glBindVertexArray(logl_ShadowMapping_planeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  // cubes
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
  model = glm::scale(model, glm::vec3(0.5f));
  shader.setMat4("model", model);
  logl_ShadowMapping_renderCube();
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
  model = glm::scale(model, glm::vec3(0.5f));
  shader.setMat4("model", model);
  logl_ShadowMapping_renderCube();
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
  model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
  model = glm::scale(model, glm::vec3(0.25));
  shader.setMat4("model", model);
  logl_ShadowMapping_renderCube();
}
// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int logl_ShadowMapping_cubeVAO = 0;
unsigned int logl_ShadowMapping_cubeVBO = 0;
void logl_ShadowMapping_renderCube()
{
  // initialize (if necessary)
  if (logl_ShadowMapping_cubeVAO == 0)
  {
    float vertices[] = {
      // back face
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
      // front face
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      // left face
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      // right face
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
      // bottom face
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      // top face
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
    };
    glGenVertexArrays(1, &logl_ShadowMapping_cubeVAO);
    glGenBuffers(1, &logl_ShadowMapping_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, logl_ShadowMapping_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(logl_ShadowMapping_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  // render Cube
  glBindVertexArray(logl_ShadowMapping_cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int logl_ShadowMapping_quadVAO = 0;
unsigned int logl_ShadowMapping_quadVBO;
void logl_ShadowMapping_renderQuad()
{
  if (logl_ShadowMapping_quadVAO == 0)
  {
    float quadVertices[] = {
      // positions        // texture Coords
      -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &logl_ShadowMapping_quadVAO);
    glGenBuffers(1, &logl_ShadowMapping_quadVBO);
    glBindVertexArray(logl_ShadowMapping_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_ShadowMapping_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  }
  glBindVertexArray(logl_ShadowMapping_quadVAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}
/////////////// LearnOpenGL - Shadow Mapping ////////////

/////////////// LearnOpenGL - Point Shadows ////////////
void logl_PointShadows_renderScene(const LoglShader &shader);
void logl_PointShadows_renderCube();
LoglShader logl_PointShadows_shader,logl_PointShadows_simpleDepthShader;
unsigned int logl_PointShadows_woodTexture, logl_PointShadows_depthMapFBO,logl_PointShadows_depthCubemap;
const unsigned int logl_PointShadows_SHADOW_WIDTH = 1024, logl_PointShadows_SHADOW_HEIGHT = 1024;
glm::vec3 logl_PointShadows_lightPos(0.0f, 0.0f, 0.0f);

bool logl_PointShadows_ifInitOnce = false;

void logl_PointShadows_Init(){
  if(!logl_PointShadows_ifInitOnce){

    logl_PointShadows_shader = LoglShader("learnOpenGL-tut/shaders/3.2.2.point_shadows.vs", "learnOpenGL-tut/shaders/3.2.2.point_shadows.fs");
    logl_PointShadows_simpleDepthShader = LoglShader("learnOpenGL-tut/shaders/3.2.2.point_shadows_depth.vs", "learnOpenGL-tut/shaders/3.2.2.point_shadows_depth.fs", "learnOpenGL-tut/shaders/3.2.2.point_shadows_depth.gs");

    logl_PointShadows_woodTexture = logl_loadTex_stb("textures/wood.png");
    // shader configuration
    // --------------------
    logl_PointShadows_shader.use();
    logl_PointShadows_shader.setInt("diffuseTexture", 1);
    logl_PointShadows_shader.setInt("depthMap", 2);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glGenFramebuffers(1, &logl_PointShadows_depthMapFBO);
    // create depth cubemap texture
    glGenTextures(1, &logl_PointShadows_depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, logl_PointShadows_depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, logl_PointShadows_SHADOW_WIDTH, logl_PointShadows_SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, logl_PointShadows_depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, logl_PointShadows_depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_PointShadows_ifInitOnce = true;
  }
}

void logl_PointShadows_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // move light position over time
    logl_PointShadows_lightPos.z = sin(glutGet(GLUT_ELAPSED_TIME)*0.002 * 0.5) * 3.0;

    // 0. create depth cubemap transformation matrices
    // -----------------------------------------------
    float near_plane = 1.0f;
    float far_plane = 25.0f;
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)logl_PointShadows_SHADOW_WIDTH / (float)logl_PointShadows_SHADOW_HEIGHT, near_plane, far_plane);
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(shadowProj * glm::lookAt(logl_PointShadows_lightPos, logl_PointShadows_lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(logl_PointShadows_lightPos, logl_PointShadows_lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(logl_PointShadows_lightPos, logl_PointShadows_lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(logl_PointShadows_lightPos, logl_PointShadows_lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(logl_PointShadows_lightPos, logl_PointShadows_lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(logl_PointShadows_lightPos, logl_PointShadows_lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    // 1. render scene to depth cubemap
    // --------------------------------
    glViewport(0, 0, logl_PointShadows_SHADOW_WIDTH, logl_PointShadows_SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_PointShadows_depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    logl_PointShadows_simpleDepthShader.use();
    for (unsigned int i = 0; i < 6; ++i)
    logl_PointShadows_simpleDepthShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    logl_PointShadows_simpleDepthShader.setFloat("far_plane", far_plane);
    logl_PointShadows_simpleDepthShader.setVec3("lightPos", logl_PointShadows_lightPos);
    logl_PointShadows_renderScene(logl_PointShadows_simpleDepthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. render scene as normal
    // -------------------------
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    logl_PointShadows_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_PointShadows_shader.setMat4("projection", projection);
    logl_PointShadows_shader.setMat4("view", view);
    // set lighting uniforms
    logl_PointShadows_shader.setVec3("lightPos", logl_PointShadows_lightPos);
    logl_PointShadows_shader.setVec3("viewPos", logl_cameraPos);
    logl_PointShadows_shader.setInt("shadows", true); // enable/disable shadows by pressing 'SPACE'
    logl_PointShadows_shader.setFloat("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_PointShadows_woodTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, logl_PointShadows_depthCubemap);
    logl_PointShadows_renderScene(logl_PointShadows_shader);



    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renders the 3D scene
// --------------------
void logl_PointShadows_renderScene(const LoglShader &shader)
{
  // room cube
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(5.0f));
  shader.setMat4("model", model);
  glDisable(GL_CULL_FACE); // note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
  shader.setInt("reverse_normals", 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
  logl_PointShadows_renderCube();
  shader.setInt("reverse_normals", 0); // and of course disable it
  glEnable(GL_CULL_FACE);
  // cubes
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
  model = glm::scale(model, glm::vec3(0.5f));
  shader.setMat4("model", model);
  logl_PointShadows_renderCube();
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
  model = glm::scale(model, glm::vec3(0.75f));
  shader.setMat4("model", model);
  logl_PointShadows_renderCube();
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
  model = glm::scale(model, glm::vec3(0.5f));
  shader.setMat4("model", model);
  logl_PointShadows_renderCube();
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
  model = glm::scale(model, glm::vec3(0.5f));
  shader.setMat4("model", model);
  logl_PointShadows_renderCube();
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
  model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
  model = glm::scale(model, glm::vec3(0.75f));
  shader.setMat4("model", model);
  logl_PointShadows_renderCube();
}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int logl_PointShadows_cubeVAO = 0;
unsigned int logl_PointShadows_cubeVBO = 0;
void logl_PointShadows_renderCube()
{
  // initialize (if necessary)
  if (logl_PointShadows_cubeVAO == 0)
  {
    float vertices[] = {
      // back face
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
      // front face
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      // left face
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      // right face
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
      // bottom face
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      // top face
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
    };
    glGenVertexArrays(1, &logl_PointShadows_cubeVAO);
    glGenBuffers(1, &logl_PointShadows_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, logl_PointShadows_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(logl_PointShadows_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  // render Cube
  glBindVertexArray(logl_PointShadows_cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}
/////////////// LearnOpenGL - Point Shadows ////////////

/////////////// LearnOpenGL - Normal Mapping ////////////
void logl_NormalMapping_renderQuad();
LoglShader logl_NormalMapping_shader;
unsigned int logl_NormalMapping_diffuseMap, logl_NormalMapping_normalMap;
glm::vec3 logl_NormalMapping_lightPos(0.5f, 1.0f, 0.3f);

bool logl_NormalMapping_ifInitOnce = false;

void logl_NormalMapping_Init(){
  if(!logl_NormalMapping_ifInitOnce){

    logl_NormalMapping_shader = LoglShader("learnOpenGL-tut/shaders/4.normal_mapping.vs", "learnOpenGL-tut/shaders/4.normal_mapping.fs");

    logl_NormalMapping_diffuseMap = logl_loadTex_stb("textures/brickwall.jpg");
    logl_NormalMapping_normalMap = logl_loadTex_stb("textures/brickwall_normal.jpg");
    // shader configuration
    // --------------------
    logl_NormalMapping_shader.use();
    logl_NormalMapping_shader.setInt("diffuseMap", 0);
    logl_NormalMapping_shader.setInt("normalMap", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_NormalMapping_ifInitOnce = true;
  }
}
void logl_NormalMapping_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }



    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_NormalMapping_shader.use();
    logl_NormalMapping_shader.setMat4("projection", projection);
    logl_NormalMapping_shader.setMat4("view", view);

    // render normal-mapped quad
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians((float)glutGet(GLUT_ELAPSED_TIME) * 0.002f * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
    logl_NormalMapping_shader.setMat4("model", model);
    logl_NormalMapping_shader.setVec3("viewPos", logl_cameraPos);
    logl_NormalMapping_shader.setVec3("lightPos", logl_NormalMapping_lightPos);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_NormalMapping_diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_NormalMapping_normalMap);
    logl_NormalMapping_renderQuad();




    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
unsigned int logl_NormalMapping_quadVAO = 0;
unsigned int logl_NormalMapping_quadVBO;
void logl_NormalMapping_renderQuad()
{
  if (logl_NormalMapping_quadVAO == 0)
  {
    // positions
    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);


    float quadVertices[] = {
      // positions            // normal         // texcoords  // tangent                          // bitangent
      pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
      pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
      pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

      pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
      pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
      pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };
    // configure plane VAO
    glGenVertexArrays(1, &logl_NormalMapping_quadVAO);
    glGenBuffers(1, &logl_NormalMapping_quadVBO);
    glBindVertexArray(logl_NormalMapping_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_NormalMapping_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(logl_NormalMapping_quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  //glBindVertexArray(0);
}
/////////////// LearnOpenGL - Normal Mapping ////////////

/////////////// LearnOpenGL - Parallax Mapping ////////////
void logl_ParallaxMapping_renderQuad();
LoglShader logl_ParallaxMapping_shader;
float logl_ParallaxMapping_heightScale = 0.1;
unsigned int logl_ParallaxMapping_diffuseMap, logl_ParallaxMapping_normalMap, logl_ParallaxMapping_heightMap;
unsigned int logl_ParallaxMapping_diffuseMap2, logl_ParallaxMapping_normalMap2, logl_ParallaxMapping_heightMap2;
glm::vec3 logl_ParallaxMapping_lightPos(0.0f, 1.0f, 1.0f);

bool logl_ParallaxMapping_ifInitOnce = false;

void logl_ParallaxMapping_Init(){
  if(!logl_ParallaxMapping_ifInitOnce){

    logl_ParallaxMapping_shader = LoglShader("learnOpenGL-tut/shaders/5.3.parallax_mapping.vs", "learnOpenGL-tut/shaders/5.3.parallax_mapping.fs");

    logl_ParallaxMapping_diffuseMap = logl_loadTex_stb("textures/bricks2.jpg");
    logl_ParallaxMapping_normalMap = logl_loadTex_stb("textures/bricks2_normal.jpg");
    logl_ParallaxMapping_heightMap = logl_loadTex_stb("textures/bricks2_disp.jpg");
    //
    logl_ParallaxMapping_diffuseMap2 = logl_loadTex_stb("textures/toy_box_diffuse.png");
    logl_ParallaxMapping_normalMap2 = logl_loadTex_stb("textures/toy_box_normal.png");
    logl_ParallaxMapping_heightMap2 = logl_loadTex_stb("textures/toy_box_disp.png");
    // shader configuration
    // --------------------
    logl_ParallaxMapping_shader.use();
    logl_ParallaxMapping_shader.setInt("diffuseMap", 0);
    logl_ParallaxMapping_shader.setInt("normalMap", 1);
    logl_ParallaxMapping_shader.setInt("depthMap", 2);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    logl_ParallaxMapping_ifInitOnce = true;
  }
}
void logl_ParallaxMapping_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }


    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_ParallaxMapping_shader.use();
    logl_ParallaxMapping_shader.setMat4("projection", projection);
    logl_ParallaxMapping_shader.setMat4("view", view);

    // render parallax-mapped quad
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians((float)glutGet(GLUT_ELAPSED_TIME) * 0.002f * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
    logl_ParallaxMapping_shader.setMat4("model", model);
    logl_ParallaxMapping_shader.setVec3("viewPos", logl_cameraPos);
    logl_ParallaxMapping_shader.setVec3("lightPos", logl_ParallaxMapping_lightPos);
    logl_ParallaxMapping_shader.setFloat("heightScale", logl_ParallaxMapping_heightScale);
    if(multipleOutputsIndex == 1){
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, logl_ParallaxMapping_diffuseMap);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, logl_ParallaxMapping_normalMap);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, logl_ParallaxMapping_heightMap);
    }
    if(multipleOutputsIndex == 2){
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, logl_ParallaxMapping_diffuseMap2);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, logl_ParallaxMapping_normalMap2);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, logl_ParallaxMapping_heightMap2);
    }
    logl_ParallaxMapping_renderQuad();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
unsigned int logl_ParallaxMapping_quadVAO = 0;
unsigned int logl_ParallaxMapping_quadVBO;
void logl_ParallaxMapping_renderQuad()
{
  if (logl_ParallaxMapping_quadVAO == 0)
  {
    // positions
    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);


    float quadVertices[] = {
      // positions            // normal         // texcoords  // tangent                          // bitangent
      pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
      pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
      pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

      pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
      pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
      pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };
    // configure plane VAO
    glGenVertexArrays(1, &logl_ParallaxMapping_quadVAO);
    glGenBuffers(1, &logl_ParallaxMapping_quadVBO);
    glBindVertexArray(logl_ParallaxMapping_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_ParallaxMapping_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(logl_ParallaxMapping_quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  //glBindVertexArray(0);
}
/////////////// LearnOpenGL - Parallax Mapping ////////////

/////////////// LearnOpenGL - HDR ////////////
void logl_HDR_renderQuad();
void logl_HDR_renderCube();
LoglShader logl_HDR_shader, logl_HDR_hdrShader;
float logl_HDR_exposure = 1.0;
unsigned int logl_HDR_woodTexture, logl_HDR_hdrFBO, logl_HDR_colorBuffer, logl_HDR_rboDepth;
std::vector<glm::vec3> logl_HDR_lightPositions;
std::vector<glm::vec3> logl_HDR_lightColors;

bool logl_HDR_ifInitOnce = false;

void logl_HDR_Init(){
  if(!logl_HDR_ifInitOnce){

    logl_HDR_shader = LoglShader("learnOpenGL-tut/shaders/6.lighting.vs", "learnOpenGL-tut/shaders/6.lighting.fs");
    logl_HDR_hdrShader = LoglShader("learnOpenGL-tut/shaders/6.hdr.vs", "learnOpenGL-tut/shaders/6.hdr.fs");

    logl_HDR_woodTexture = logl_loadTex_stb("textures/wood.png", true);
    // shader configuration
    // --------------------
    logl_HDR_shader.use();
    logl_HDR_shader.setInt("diffuseTexture", 1);
    logl_HDR_hdrShader.use();
    logl_HDR_hdrShader.setInt("hdrBuffer", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // configure floating point framebuffer
    // ------------------------------------
    glGenFramebuffers(1, &logl_HDR_hdrFBO);
    // create floating point color buffer
    glGenTextures(1, &logl_HDR_colorBuffer);
    glBindTexture(GL_TEXTURE_2D, logl_HDR_colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // create depth buffer (renderbuffer)
    glGenRenderbuffers(1, &logl_HDR_rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, logl_HDR_rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    // attach buffers
    glBindFramebuffer(GL_FRAMEBUFFER, logl_HDR_hdrFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_HDR_colorBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, logl_HDR_rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    logl_HDR_lightPositions.push_back(glm::vec3( 0.0f,  0.0f, 49.5f)); // back light
    logl_HDR_lightPositions.push_back(glm::vec3(-1.4f, -1.9f, 9.0f));
    logl_HDR_lightPositions.push_back(glm::vec3( 0.0f, -1.8f, 4.0f));
    logl_HDR_lightPositions.push_back(glm::vec3( 0.8f, -1.7f, 6.0f));
    // colors
    logl_HDR_lightColors.push_back(glm::vec3(200.0f, 200.0f, 200.0f));
    logl_HDR_lightColors.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
    logl_HDR_lightColors.push_back(glm::vec3(0.0f, 0.0f, 0.2f));
    logl_HDR_lightColors.push_back(glm::vec3(0.0f, 0.1f, 0.0f));

    logl_HDR_ifInitOnce = true;
  }
}
void logl_HDR_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }



    // 1. render scene into floating point framebuffer
    // -----------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, logl_HDR_hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    logl_HDR_shader.use();
    logl_HDR_shader.setMat4("projection", projection);
    logl_HDR_shader.setMat4("view", view);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_HDR_woodTexture);
    // set lighting uniforms
    for (unsigned int i = 0; i < logl_HDR_lightPositions.size(); i++)
    {
      logl_HDR_shader.setVec3("lights[" + std::to_string(i) + "].Position", logl_HDR_lightPositions[i]);
      logl_HDR_shader.setVec3("lights[" + std::to_string(i) + "].Color", logl_HDR_lightColors[i]);
    }
    logl_HDR_shader.setVec3("viewPos", logl_cameraPos);
    // render tunnel
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 25.0));
    model = glm::scale(model, glm::vec3(2.5f, 2.5f, 27.5f));
    logl_HDR_shader.setMat4("model", model);
    logl_HDR_shader.setInt("inverse_normals", true);
    logl_HDR_renderCube();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // 2. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
    // --------------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    logl_HDR_hdrShader.use();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_HDR_colorBuffer);
    logl_HDR_hdrShader.setInt("hdr", true);
    if(multipleOutputsIndex == 1)
    logl_HDR_exposure = 1.0;
    if(multipleOutputsIndex == 2)
    logl_HDR_exposure = 5.0;
    if(multipleOutputsIndex == 3)
    logl_HDR_exposure = 0.1;
    logl_HDR_hdrShader.setFloat("exposure", logl_HDR_exposure);
    logl_HDR_renderQuad();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int logl_HDR_cubeVAO = 0;
unsigned int logl_HDR_cubeVBO = 0;
void logl_HDR_renderCube()
{
  // initialize (if necessary)
  if (logl_HDR_cubeVAO == 0)
  {
    float vertices[] = {
      // back face
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
      // front face
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      // left face
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      // right face
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
      // bottom face
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      // top face
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
    };
    glGenVertexArrays(1, &logl_HDR_cubeVAO);
    glGenBuffers(1, &logl_HDR_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, logl_HDR_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(logl_HDR_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  // render Cube
  glBindVertexArray(logl_HDR_cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}
// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
unsigned int logl_HDR_quadVAO = 0;
unsigned int logl_HDR_quadVBO;
void logl_HDR_renderQuad()
{
  if (logl_HDR_quadVAO == 0)
  {
    float quadVertices[] = {
      // positions        // texture Coords
      -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &logl_HDR_quadVAO);
    glGenBuffers(1, &logl_HDR_quadVBO);
    glBindVertexArray(logl_HDR_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_HDR_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(logl_HDR_quadVAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
/////////////// LearnOpenGL - HDR ////////////

/////////////// LearnOpenGL - Bloom ////////////
void logl_Bloom_renderQuad();
void logl_Bloom_renderCube();
LoglShader logl_Bloom_shader,logl_Bloom_shaderLight,logl_Bloom_shaderBlur,logl_Bloom_shaderBloomFinal;
unsigned int logl_Bloom_woodTexture ,logl_Bloom_containerTexture;
unsigned int logl_Bloom_hdrFBO, logl_Bloom_colorBuffers[2],logl_Bloom_rboDepth, logl_Bloom_attachments[2];
unsigned int logl_Bloom_pingpongFBO[2], logl_Bloom_pingpongColorbuffers[2];
std::vector<glm::vec3> logl_Bloom_lightPositions;
std::vector<glm::vec3> logl_Bloom_lightColors;
float logl_Bloom_exposure = 1.0;


bool logl_Bloom_ifInitOnce = false;

void logl_Bloom_Init(){
  if(!logl_Bloom_ifInitOnce){

    logl_Bloom_shader = LoglShader("learnOpenGL-tut/shaders/7.bloom.vs", "learnOpenGL-tut/shaders/7.bloom.fs");
    logl_Bloom_shaderLight = LoglShader("learnOpenGL-tut/shaders/7.bloom.vs", "learnOpenGL-tut/shaders/7.light_box.fs");
    logl_Bloom_shaderBlur = LoglShader("learnOpenGL-tut/shaders/7.blur.vs", "learnOpenGL-tut/shaders/7.blur.fs");
    logl_Bloom_shaderBloomFinal = LoglShader("learnOpenGL-tut/shaders/7.bloom_final.vs", "learnOpenGL-tut/shaders/7.bloom_final.fs");

    logl_Bloom_woodTexture = logl_loadTex_stb("textures/wood.png", true);
    logl_Bloom_containerTexture = logl_loadTex_stb("textures/container2.png", true);
    // shader configuration
    // --------------------
    logl_Bloom_shader.use();
    logl_Bloom_shader.setInt("diffuseTexture", 0);
    logl_Bloom_shaderBlur.use();
    logl_Bloom_shaderBlur.setInt("image", 0);
    logl_Bloom_shaderBloomFinal.use();
    logl_Bloom_shaderBloomFinal.setInt("scene", 0);
    logl_Bloom_shaderBloomFinal.setInt("bloomBlur", 1);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // configure (floating point) framebuffers
    // ---------------------------------------
    glGenFramebuffers(1, &logl_Bloom_hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_Bloom_hdrFBO);
    // create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
    glGenTextures(2, logl_Bloom_colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
      glBindTexture(GL_TEXTURE_2D, logl_Bloom_colorBuffers[i]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      // attach texture to framebuffer
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, logl_Bloom_colorBuffers[i], 0);
    }
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &logl_Bloom_rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, logl_Bloom_rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, logl_Bloom_rboDepth);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    logl_Bloom_attachments[0] = GL_COLOR_ATTACHMENT0;
    logl_Bloom_attachments[1] = GL_COLOR_ATTACHMENT1;
    glDrawBuffers(2, logl_Bloom_attachments);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ping-pong-framebuffer for blurring
    glGenFramebuffers(2, logl_Bloom_pingpongFBO);
    glGenTextures(2, logl_Bloom_pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
      glBindFramebuffer(GL_FRAMEBUFFER, logl_Bloom_pingpongFBO[i]);
      glBindTexture(GL_TEXTURE_2D, logl_Bloom_pingpongColorbuffers[i]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_Bloom_pingpongColorbuffers[i], 0);
      // also check if framebuffers are complete (no need for depth buffer)
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Framebuffer not complete!" << std::endl;
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // lighting info
    // -------------
    // positions
    logl_Bloom_lightPositions.push_back(glm::vec3( 0.0f, 0.5f,  1.5f));
    logl_Bloom_lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
    logl_Bloom_lightPositions.push_back(glm::vec3( 3.0f, 0.5f,  1.0f));
    logl_Bloom_lightPositions.push_back(glm::vec3(-.8f,  2.4f, -1.0f));
    // colors
    logl_Bloom_lightColors.push_back(glm::vec3(5.0f,   5.0f,  5.0f));
    logl_Bloom_lightColors.push_back(glm::vec3(10.0f,  0.0f,  0.0f));
    logl_Bloom_lightColors.push_back(glm::vec3(0.0f,   0.0f,  15.0f));
    logl_Bloom_lightColors.push_back(glm::vec3(0.0f,   5.0f,  0.0f));


    colorBG.x = 0.0;
    colorBG.y = 0.0;
    colorBG.z = 0.0;

    logl_Bloom_ifInitOnce = true;
  }
}
void logl_Bloom_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }

    if(windowResized){
      for (unsigned int i = 0; i < 2; i++)
      {
        glBindTexture(GL_TEXTURE_2D, logl_Bloom_colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, logl_Bloom_colorBuffers[i], 0);
      }
      // create and attach depth buffer (renderbuffer)
      glBindRenderbuffer(GL_RENDERBUFFER, logl_Bloom_rboDepth);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, logl_Bloom_rboDepth);
      // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
      logl_Bloom_attachments[0] = GL_COLOR_ATTACHMENT0;
      logl_Bloom_attachments[1] = GL_COLOR_ATTACHMENT1;
      glDrawBuffers(2, logl_Bloom_attachments);
      // finally check if framebuffer is complete
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Framebuffer not complete!" << std::endl;
      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      // ping-pong-framebuffer for blurring
      for (unsigned int i = 0; i < 2; i++)
      {
        glBindFramebuffer(GL_FRAMEBUFFER, logl_Bloom_pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, logl_Bloom_pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_Bloom_pingpongColorbuffers[i], 0);
        // also check if framebuffers are complete (no need for depth buffer)
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }

      windowResized = false;
    }




    // 1. render scene into floating point framebuffer
    // -----------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, logl_Bloom_hdrFBO);
    glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    logl_Bloom_shader.use();
    logl_Bloom_shader.setMat4("projection", projection);
    logl_Bloom_shader.setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_Bloom_woodTexture);
    // set lighting uniforms
    for (unsigned int i = 0; i < logl_Bloom_lightPositions.size(); i++)
    {
      logl_Bloom_shader.setVec3("lights[" + std::to_string(i) + "].Position", logl_Bloom_lightPositions[i]);
      logl_Bloom_shader.setVec3("lights[" + std::to_string(i) + "].Color", logl_Bloom_lightColors[i]);
    }
    logl_Bloom_shader.setVec3("viewPos", logl_cameraPos);
    // create one large cube that acts as the floor
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
    model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();
    // then create multiple cubes as the scenery
    glBindTexture(GL_TEXTURE_2D, logl_Bloom_containerTexture);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
    model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(1.25));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
    model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    logl_Bloom_shader.setMat4("model", model);
    logl_Bloom_renderCube();

    // finally show all the light sources as bright cubes
    logl_Bloom_shaderLight.use();
    logl_Bloom_shaderLight.setMat4("projection", projection);
    logl_Bloom_shaderLight.setMat4("view", view);

    for (unsigned int i = 0; i < logl_Bloom_lightPositions.size(); i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(logl_Bloom_lightPositions[i]));
      model = glm::scale(model, glm::vec3(0.25f));
      logl_Bloom_shaderLight.setMat4("model", model);
      logl_Bloom_shaderLight.setVec3("lightColor", logl_Bloom_lightColors[i]);
      logl_Bloom_renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. blur bright fragments with two-pass Gaussian Blur
    // --------------------------------------------------
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 10;
    logl_Bloom_shaderBlur.use();
    for (unsigned int i = 0; i < amount; i++)
    {
      glBindFramebuffer(GL_FRAMEBUFFER, logl_Bloom_pingpongFBO[horizontal]);
      logl_Bloom_shaderBlur.setInt("horizontal", horizontal);
      glBindTexture(GL_TEXTURE_2D, first_iteration ? logl_Bloom_colorBuffers[1] : logl_Bloom_pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
      logl_Bloom_renderQuad();
      horizontal = !horizontal;
      if (first_iteration)
      first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
    // --------------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    logl_Bloom_shaderBloomFinal.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_Bloom_colorBuffers[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_Bloom_pingpongColorbuffers[!horizontal]);
    logl_Bloom_shaderBloomFinal.setInt("bloom", true);
    logl_Bloom_shaderBloomFinal.setFloat("exposure", logl_Bloom_exposure);
    logl_Bloom_renderQuad();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int logl_Bloom_cubeVAO = 0;
unsigned int logl_Bloom_cubeVBO = 0;
void logl_Bloom_renderCube()
{
  // initialize (if necessary)
  if (logl_Bloom_cubeVAO == 0)
  {
    float vertices[] = {
      // back face
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
      // front face
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      // left face
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      // right face
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
      // bottom face
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      // top face
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
    };
    glGenVertexArrays(1, &logl_Bloom_cubeVAO);
    glGenBuffers(1, &logl_Bloom_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, logl_Bloom_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(logl_Bloom_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  // render Cube
  glBindVertexArray(logl_Bloom_cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int logl_Bloom_quadVAO = 0;
unsigned int logl_Bloom_quadVBO;
void logl_Bloom_renderQuad()
{
  if (logl_Bloom_quadVAO == 0)
  {
    float quadVertices[] = {
      // positions        // texture Coords
      -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &logl_Bloom_quadVAO);
    glGenBuffers(1, &logl_Bloom_quadVBO);
    glBindVertexArray(logl_Bloom_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_Bloom_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(logl_Bloom_quadVAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}

/////////////// LearnOpenGL - Bloom ////////////

/////////////// LearnOpenGL - Deferred Shading ////////////
void logl_DeferredShading_renderQuad();
void logl_DeferredShading_renderCube();
LoglShader logl_DeferredShading_shaderGeometryPass, logl_DeferredShading_shaderLightingPass, logl_DeferredShading_shaderLightBox;
std::vector<glm::vec3> logl_DeferredShading_objectPositions;
unsigned int logl_DeferredShading_gBuffer, logl_DeferredShading_gPosition, logl_DeferredShading_gNormal, logl_DeferredShading_gAlbedoSpec;
unsigned int logl_DeferredShading_attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
unsigned int logl_DeferredShading_rboDepth;
const unsigned int logl_DeferredShading_NR_LIGHTS = 32;
std::vector<glm::vec3> logl_DeferredShading_lightPositions;
std::vector<glm::vec3> logl_DeferredShading_lightColors;


bool logl_DeferredShading_ifInitOnce = false;

void logl_DeferredShading_Init(){
  if(!logl_DeferredShading_ifInitOnce){

    logl_DeferredShading_shaderGeometryPass = LoglShader("learnOpenGL-tut/shaders/8.2.g_buffer.vs", "learnOpenGL-tut/shaders/8.2.g_buffer.fs");
    logl_DeferredShading_shaderLightingPass = LoglShader("learnOpenGL-tut/shaders/8.2.deferred_shading.vs", "learnOpenGL-tut/shaders/8.2.deferred_shading.fs");
    logl_DeferredShading_shaderLightBox = LoglShader("learnOpenGL-tut/shaders/8.2.deferred_light_box.vs", "learnOpenGL-tut/shaders/8.2.deferred_light_box.fs");


    logl_DeferredShading_objectPositions.push_back(glm::vec3(-3.0,  -3.0, -3.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3( 0.0,  -3.0, -3.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3( 3.0,  -3.0, -3.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3(-3.0,  -3.0,  0.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3( 0.0,  -3.0,  0.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3( 3.0,  -3.0,  0.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3(-3.0,  -3.0,  3.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3( 0.0,  -3.0,  3.0));
    logl_DeferredShading_objectPositions.push_back(glm::vec3( 3.0,  -3.0,  3.0));
    // shader configuration
    // --------------------
    logl_DeferredShading_shaderLightingPass.use();
    logl_DeferredShading_shaderLightingPass.setInt("gPosition", 1);
    logl_DeferredShading_shaderLightingPass.setInt("gNormal", 2);
    logl_DeferredShading_shaderLightingPass.setInt("gAlbedoSpec", 3);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // configure g-buffer framebuffer
    // ------------------------------
    glGenFramebuffers(1, &logl_DeferredShading_gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_DeferredShading_gBuffer);
    // position color buffer
    glGenTextures(1, &logl_DeferredShading_gPosition);
    glBindTexture(GL_TEXTURE_2D, logl_DeferredShading_gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_DeferredShading_gPosition, 0);
    // normal color buffer
    glGenTextures(1, &logl_DeferredShading_gNormal);
    glBindTexture(GL_TEXTURE_2D, logl_DeferredShading_gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, logl_DeferredShading_gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &logl_DeferredShading_gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, logl_DeferredShading_gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, logl_DeferredShading_gAlbedoSpec, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    glDrawBuffers(3, logl_DeferredShading_attachments);
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &logl_DeferredShading_rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, logl_DeferredShading_rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, logl_DeferredShading_rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // lighting info
    // -------------
    srand(13);
    for (unsigned int i = 0; i < logl_DeferredShading_NR_LIGHTS; i++)
    {
      // calculate slightly random offsets
      float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
      float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
      float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
      logl_DeferredShading_lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
      // also calculate random color
      float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
      float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
      float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
      logl_DeferredShading_lightColors.push_back(glm::vec3(rColor, gColor, bColor));
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    logl_DeferredShading_ifInitOnce = true;
  }
}
void logl_DeferredShading_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }


    // 1. render scene into floating point framebuffer
    // -----------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, logl_DeferredShading_gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    logl_DeferredShading_shaderGeometryPass.use();
    logl_DeferredShading_shaderGeometryPass.setMat4("projection", projection);
    logl_DeferredShading_shaderGeometryPass.setMat4("view", view);
    for (unsigned int i = 0; i < logl_DeferredShading_objectPositions.size(); i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, logl_DeferredShading_objectPositions[i]);
      model = glm::scale(model, glm::vec3(0.25f));
      logl_DeferredShading_shaderGeometryPass.setMat4("model", model);
      nanosuit.Draw(logl_DeferredShading_shaderGeometryPass);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
    // -----------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    logl_DeferredShading_shaderLightingPass.use();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_DeferredShading_gPosition);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_DeferredShading_gNormal);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, logl_DeferredShading_gAlbedoSpec);
    // send light relevant uniforms
    for (unsigned int i = 0; i < logl_DeferredShading_lightPositions.size(); i++)
    {
      logl_DeferredShading_shaderLightingPass.setVec3("lights[" + std::to_string(i) + "].Position", logl_DeferredShading_lightPositions[i]);
      logl_DeferredShading_shaderLightingPass.setVec3("lights[" + std::to_string(i) + "].Color", logl_DeferredShading_lightColors[i]);
      // update attenuation parameters and calculate radius
      const float constant = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
      const float linear = 0.7;
      const float quadratic = 1.8;
      logl_DeferredShading_shaderLightingPass.setFloat("lights[" + std::to_string(i) + "].Linear", linear);
      logl_DeferredShading_shaderLightingPass.setFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
      // then calculate radius of light volume/sphere
      const float maxBrightness = std::fmaxf(std::fmaxf(logl_DeferredShading_lightColors[i].r, logl_DeferredShading_lightColors[i].g), logl_DeferredShading_lightColors[i].b);
      float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
      logl_DeferredShading_shaderLightingPass.setFloat("lights[" + std::to_string(i) + "].Radius", radius);
    }
    logl_DeferredShading_shaderLightingPass.setVec3("viewPos", logl_cameraPos);
    // finally render quad
    logl_DeferredShading_renderQuad();

    // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
    // ----------------------------------------------------------------------------------
    glBindFramebuffer(GL_READ_FRAMEBUFFER, logl_DeferredShading_gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
    // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
    // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the
    // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
    glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. render lights on top of scene
    // --------------------------------
    logl_DeferredShading_shaderLightBox.use();
    logl_DeferredShading_shaderLightBox.setMat4("projection", projection);
    logl_DeferredShading_shaderLightBox.setMat4("view", view);
    for (unsigned int i = 0; i < logl_DeferredShading_lightPositions.size(); i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, logl_DeferredShading_lightPositions[i]);
      model = glm::scale(model, glm::vec3(0.125f));
      logl_DeferredShading_shaderLightBox.setMat4("model", model);
      logl_DeferredShading_shaderLightBox.setVec3("lightColor", logl_DeferredShading_lightColors[i]);
      logl_DeferredShading_renderCube();
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int logl_DeferredShading_cubeVAO = 0;
unsigned int logl_DeferredShading_cubeVBO = 0;
void logl_DeferredShading_renderCube()
{
  // initialize (if necessary)
  if (logl_DeferredShading_cubeVAO == 0)
  {
    float vertices[] = {
      // back face
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
      // front face
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      // left face
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      // right face
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
      // bottom face
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      // top face
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
    };
    glGenVertexArrays(1, &logl_DeferredShading_cubeVAO);
    glGenBuffers(1, &logl_DeferredShading_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, logl_DeferredShading_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(logl_DeferredShading_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  // render Cube
  glBindVertexArray(logl_DeferredShading_cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}


// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int logl_DeferredShading_quadVAO = 0;
unsigned int logl_DeferredShading_quadVBO;
void logl_DeferredShading_renderQuad()
{
  if (logl_DeferredShading_quadVAO == 0)
  {
    float quadVertices[] = {
      // positions        // texture Coords
      -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &logl_DeferredShading_quadVAO);
    glGenBuffers(1, &logl_DeferredShading_quadVBO);
    glBindVertexArray(logl_DeferredShading_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_DeferredShading_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(logl_DeferredShading_quadVAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}

/////////////// LearnOpenGL - Deferred Shading ////////////

/////////////// LearnOpenGL - SSAO ////////////
void logl_SSAO_renderQuad();
void logl_SSAO_renderCube();
float lerp(float a, float b, float f)
{
  return a + f * (b - a);
}
LoglShader logl_SSAO_shaderGeometryPass, logl_SSAO_shaderLightingPass, logl_SSAO_shaderSSAO, logl_SSAO_shaderSSAOBlur;
unsigned int logl_SSAO_gBuffer;
unsigned int logl_SSAO_gPosition, logl_SSAO_gNormal, logl_SSAO_gAlbedo;
unsigned int logl_SSAO_attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
unsigned int logl_SSAO_rboDepth;
unsigned int logl_SSAO_ssaoFBO, logl_SSAO_ssaoBlurFBO;
unsigned int logl_SSAO_ssaoColorBuffer, logl_SSAO_ssaoColorBufferBlur;
std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
std::default_random_engine generator;
std::vector<glm::vec3> ssaoKernel;
std::vector<glm::vec3> ssaoNoise;
unsigned int logl_SSAO_noiseTexture;

glm::vec3 logl_SSAO_lightPos;
glm::vec3 logl_SSAO_lightColor;


bool logl_SSAO_ifInitOnce = false;

void logl_SSAO_Init(){
  if(!logl_SSAO_ifInitOnce){

    logl_SSAO_shaderGeometryPass = LoglShader("learnOpenGL-tut/shaders/9.ssao_geometry.vs", "learnOpenGL-tut/shaders/9.ssao_geometry.fs");
    logl_SSAO_shaderLightingPass = LoglShader("learnOpenGL-tut/shaders/9.ssao.vs", "learnOpenGL-tut/shaders/9.ssao_lighting.fs");
    logl_SSAO_shaderSSAO = LoglShader("learnOpenGL-tut/shaders/9.ssao.vs", "learnOpenGL-tut/shaders/9.ssao.fs");
    logl_SSAO_shaderSSAOBlur = LoglShader("learnOpenGL-tut/shaders/9.ssao.vs", "learnOpenGL-tut/shaders/9.ssao_blur.fs");


    // shader configuration
    // --------------------
    logl_SSAO_shaderLightingPass.use();
    logl_SSAO_shaderLightingPass.setInt("gPosition", 0);
    logl_SSAO_shaderLightingPass.setInt("gNormal", 1);
    logl_SSAO_shaderLightingPass.setInt("gAlbedo", 2);
    logl_SSAO_shaderLightingPass.setInt("ssao", 3);
    logl_SSAO_shaderSSAO.use();
    logl_SSAO_shaderSSAO.setInt("gPosition", 0);
    logl_SSAO_shaderSSAO.setInt("gNormal", 1);
    logl_SSAO_shaderSSAO.setInt("texNoise", 2);
    logl_SSAO_shaderSSAOBlur.use();
    logl_SSAO_shaderSSAOBlur.setInt("ssaoInput", 0);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // configure g-buffer framebuffer
    // ------------------------------
    glGenFramebuffers(1, &logl_SSAO_gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_gBuffer);
    // position color buffer
    glGenTextures(1, &logl_SSAO_gPosition);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_SSAO_gPosition, 0);
    // normal color buffer
    glGenTextures(1, &logl_SSAO_gNormal);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, logl_SSAO_gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &logl_SSAO_gAlbedo);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, logl_SSAO_gAlbedo, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    glDrawBuffers(3, logl_SSAO_attachments);
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &logl_SSAO_rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, logl_SSAO_rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, logl_SSAO_rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // also create framebuffer to hold SSAO processing stage
    // -----------------------------------------------------
    glGenFramebuffers(1, &logl_SSAO_ssaoFBO);  glGenFramebuffers(1, &logl_SSAO_ssaoBlurFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_ssaoFBO);
    // SSAO color buffer
    glGenTextures(1, &logl_SSAO_ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_SSAO_ssaoColorBuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "SSAO Framebuffer not complete!" << std::endl;
    // and blur stage
    glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_ssaoBlurFBO);
    glGenTextures(1, &logl_SSAO_ssaoColorBufferBlur);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_ssaoColorBufferBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_SSAO_ssaoColorBufferBlur, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // generate sample kernel
    // ----------------------
    for (unsigned int i = 0; i < 64; ++i)
    {
      glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
      sample = glm::normalize(sample);
      sample *= randomFloats(generator);
      float scale = float(i) / 64.0;

      // scale samples s.t. they're more aligned to center of kernel
      scale = lerp(0.1f, 1.0f, scale * scale);
      sample *= scale;
      ssaoKernel.push_back(sample);
    }
    // generate noise texture
    // ----------------------
    std::vector<glm::vec3> ssaoNoise;
    for (unsigned int i = 0; i < 16; i++)
    {
      glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
      ssaoNoise.push_back(noise);
    }
    glGenTextures(1, &logl_SSAO_noiseTexture);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // lighting info
    // -------------
    logl_SSAO_lightPos = glm::vec3(2.0, 4.0, -2.0);
    logl_SSAO_lightColor = glm::vec3(0.2, 0.2, 0.7);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    logl_SSAO_ifInitOnce = true;
  }
}
void logl_SSAO_Display(){
  // be sure to activate shader when setting uniforms/drawing objects
  float currentFrame = glutGet(GLUT_ELAPSED_TIME);
  logl_deltaTime = currentFrame - logl_lastFrame;
  logl_lastFrame = currentFrame;

  glClearColor(colorBG.x,colorBG.y, colorBG.z, colorBG.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!show_text){
    if(!logl_resetMousePos){
      glutWarpPointer( SCR_WIDTH/2 , SCR_HEIGHT/2 );
      glutSetCursor(GLUT_CURSOR_NONE);
      logl_resetMousePos = true;
      useMouseForImGui = false;
    }
    if(windowResized){
      glBindTexture(GL_TEXTURE_2D, logl_SSAO_gPosition);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_SSAO_gPosition, 0);
      // normal color buffer
      glBindTexture(GL_TEXTURE_2D, logl_SSAO_gNormal);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, logl_SSAO_gNormal, 0);
      // color + specular color buffer
      glBindTexture(GL_TEXTURE_2D, logl_SSAO_gAlbedo);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, logl_SSAO_gAlbedo, 0);
      // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
      glDrawBuffers(3, logl_SSAO_attachments);
      // create and attach depth buffer (renderbuffer)
      glBindRenderbuffer(GL_RENDERBUFFER, logl_SSAO_rboDepth);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, logl_SSAO_rboDepth);
      // finally check if framebuffer is complete
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Framebuffer not complete!" << std::endl;
      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      // also create framebuffer to hold SSAO processing stage
      // -----------------------------------------------------
      glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_ssaoFBO);
      // SSAO color buffer
      glBindTexture(GL_TEXTURE_2D, logl_SSAO_ssaoColorBuffer);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_SSAO_ssaoColorBuffer, 0);
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "SSAO Framebuffer not complete!" << std::endl;
      // and blur stage
      glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_ssaoBlurFBO);
      glBindTexture(GL_TEXTURE_2D, logl_SSAO_ssaoColorBufferBlur);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, logl_SSAO_ssaoColorBufferBlur, 0);
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      windowResized = false;
    }



    // 1. geometry pass: render scene's geometry/color data into gbuffer
    // -----------------------------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0001f, 1000.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    logl_SSAO_shaderGeometryPass.use();
    logl_SSAO_shaderGeometryPass.setMat4("projection", projection);
    logl_SSAO_shaderGeometryPass.setMat4("view", view);
    // room cube
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, 7.0f, 0.0f));
    model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
    logl_SSAO_shaderGeometryPass.setMat4("model", model);
    logl_SSAO_shaderGeometryPass.setInt("invertedNormals", 1); // invert normals as we're inside the cube
    logl_SSAO_renderCube();
    logl_SSAO_shaderGeometryPass.setInt("invertedNormals", 0);
    // nanosuit model on the floor
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.0));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    logl_SSAO_shaderGeometryPass.setMat4("model", model);
    nanosuit.Draw(logl_SSAO_shaderGeometryPass);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. generate SSAO texture
    // ------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_ssaoFBO);
    glClear(GL_COLOR_BUFFER_BIT);
    logl_SSAO_shaderSSAO.use();
    // Send kernel + rotation
    for (unsigned int i = 0; i < 64; ++i)
    logl_SSAO_shaderSSAO.setVec3("samples[" + std::to_string(i) + "]", ssaoKernel[i]);
    logl_SSAO_shaderSSAO.setMat4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_noiseTexture);
    logl_SSAO_renderQuad();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. blur SSAO texture to remove noise
    // ------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, logl_SSAO_ssaoBlurFBO);
    glClear(GL_COLOR_BUFFER_BIT);
    logl_SSAO_shaderSSAOBlur.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_ssaoColorBuffer);
    logl_SSAO_renderQuad();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 4. lighting pass: traditional deferred Blinn-Phong lighting with added screen-space ambient occlusion
    // -----------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    logl_SSAO_shaderLightingPass.use();
    // send light relevant uniforms
    glm::vec3 lightPosView = glm::vec3(view * glm::vec4(logl_SSAO_lightPos, 1.0));
    logl_SSAO_shaderLightingPass.setVec3("light.Position", lightPosView);
    logl_SSAO_shaderLightingPass.setVec3("light.Color", logl_SSAO_lightColor);
    // Update attenuation parameters
    const float constant  = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
    const float linear    = 0.09;
    const float quadratic = 0.032;
    logl_SSAO_shaderLightingPass.setFloat("light.Linear", linear);
    logl_SSAO_shaderLightingPass.setFloat("light.Quadratic", quadratic);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_gAlbedo);
    glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
    glBindTexture(GL_TEXTURE_2D, logl_SSAO_ssaoColorBufferBlur);
    logl_SSAO_renderQuad();





    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    //glDepthFunc(GL_LESS);

  }

  fps_counter();
  render_ImGui();
  glutSwapBuffers();
}
// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int logl_SSAO_cubeVAO = 0;
unsigned int logl_SSAO_cubeVBO = 0;
void logl_SSAO_renderCube()
{
  // initialize (if necessary)
  if (logl_SSAO_cubeVAO == 0)
  {
    float vertices[] = {
      // back face
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
      -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
      -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
      // front face
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
      -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
      -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
      // left face
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
      -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
      // right face
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
      1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
      1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
      // bottom face
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
      -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      // top face
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
    };
    glGenVertexArrays(1, &logl_SSAO_cubeVAO);
    glGenBuffers(1, &logl_SSAO_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, logl_SSAO_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(logl_SSAO_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  // render Cube
  glBindVertexArray(logl_SSAO_cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}


// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int logl_SSAO_quadVAO = 0;
unsigned int logl_SSAO_quadVBO;
void logl_SSAO_renderQuad()
{
  if (logl_SSAO_quadVAO == 0)
  {
    float quadVertices[] = {
      // positions        // texture Coords
      -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &logl_SSAO_quadVAO);
    glGenBuffers(1, &logl_SSAO_quadVBO);
    glBindVertexArray(logl_SSAO_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, logl_SSAO_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(logl_SSAO_quadVAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}
/////////////// LearnOpenGL - SSAO ////////////

void load_logl_Textures(){
  if(loadLoglTextures){
    containerTexId = loadTex_stb("textures/container.jpg");
    combinedTexId = loadTex_stb("textures/textures_combined2.png");
    vector<std::string> faces
    {
      "textures/skybox/right.jpg",
      "textures/skybox/left.jpg",
      "textures/skybox/top.jpg",
      "textures/skybox/bottom.jpg",
      "textures/skybox/front.jpg",
      "textures/skybox/back.jpg"
    };
    logl_Cubemaps_cubemapTexture = loadCubemap(faces);
    loadLoglTextures = false;
  }

}

void logl_modelsLoader(){
  nanosuit = Model("learnOpenGL-tut/models/nanosuit/nanosuit.obj");
  rock = Model("learnOpenGL-tut/models/rock/rock.obj");
  planet = Model("learnOpenGL-tut/models/planet/planet.obj");
  //glBindVertexArray(0);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);

}

#endif //LEARNOGL_HPP
