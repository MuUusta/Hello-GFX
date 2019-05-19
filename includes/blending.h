#ifndef BLENDING_H
#define BLENDING_H

float transparency=0.3;

void renderQuad(){
  glBegin(GL_QUADS);
  glNormal3f( 0.0f, 0.0f, 1.0f);                              // front face points out of the screen on z.
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);  // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);  // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);  // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);  // Top Left Of The Texture and Quad
  glEnd();
}
void blendingDisplay(){

  glClearColor( colorBG.x,colorBG.y, colorBG.z, 1.0f );
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  // Reset transformations
  glLoadIdentity();
  gluPerspective(45.0f, SCR_WIDTH/SCR_HEIGHT, 0.1f, 1000.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if(!show_text){
    glColor3f(.9f, 0.3f, 0.3f);
    glDisable(GL_BLEND);					// Turn Blending On

    glTranslatef(0,0,-8);
    glRotatef(glutGet(GLUT_ELAPSED_TIME)*0.02,0,1,0);

    glPushMatrix();
    renderQuad();
    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);	// Blending Function For Translucency Based On Source Alpha Value
    glColor4f(.5f, 0.5f, 0.5f,transparency);		// Full Brightness, 50% Alpha ( NEW )


    glPushMatrix();
    glTranslatef(0,0,-1);
    renderQuad();
    glPopMatrix();

    glDisable(GL_BLEND);					// Turn Blending On


  }else{

  }
  render_ImGui();
  fps_counter();
  glutSwapBuffers();

}

#endif //BLENDING_H
