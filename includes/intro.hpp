#ifndef INTRO_HPP
#define INTRO_HPP

#include <chrono>
#include <thread>

LoglShader introShader;
unsigned int LogoLeftTex, LogoRightTex;
unsigned int introVAO, introVBO;
float logoVertices[] = {
  // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
  -0.25f,  0.25f,  0.0f,  0.0f,  0.0f,
  -0.25f, -0.25f,  0.0f,  0.0f,  1.0f,
  0.25f, -0.25f,  0.0f,  1.0f,  1.0f,

  -0.25f,  0.25f,  0.0f,  0.0f,  0.0f,
  0.25f, -0.25f,  0.0f,  1.0f,  1.0f,
  0.25f,  0.25f,  0.0f,  1.0f,  0.0f
};
float xMotion = 10.0, textLogoColor = 0.0;
bool introInitialized = false;

sf::Music introSound;
void playIntroSound(){

  thread introThread{[](){
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    introSound.play();
  }};
  introThread.detach();
}

void intro_Init(){
  introShader = LoglShader("learnOpenGL-tut/shaders/3.2.blending.vs", "learnOpenGL-tut/shaders/3.2.blending (intro).fs");

  LogoLeftTex = logl_loadTex_stb("textures/intro/LogoSym.png", false);
  LogoRightTex = logl_loadTex_stb("textures/intro/LogoText.png", false);

  introShader.use();
  introShader.setInt("texture1", 0);

  glGenVertexArrays(1, &introVAO);
  glGenBuffers(1, &introVBO);
  glBindVertexArray(introVAO);
  glBindBuffer(GL_ARRAY_BUFFER, introVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(logoVertices), logoVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void intro_Display(){

  if(!introInitialized)
  {
    intro_Init();
    introInitialized = true;
  }


  if(introInitialized){

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    introShader.use();
    glm::mat4 projection = glm::perspective(glm::radians(logl_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(logl_cameraPos, logl_cameraPos + logl_cameraFront, logl_cameraUp);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(xMotion,0,-4));
    introShader.setFloat("dimmColor", 1.0f);
    introShader.setMat4("model", model);
    introShader.setMat4("projection", projection);
    introShader.setMat4("view", view);

    glBindVertexArray(introVAO);
    glBindTexture(GL_TEXTURE_2D, LogoLeftTex);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, LogoRightTex);
    introShader.setFloat("dimmColor", textLogoColor);
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(3,0.98,1));
    model = glm::translate(model, glm::vec3(0.1,0,-4));
    introShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  glUseProgram(0);

  if(xMotion >= -0.8){
    xMotion -= 0.4;
  }else{
    xMotion = -0.8;
  }
  if(textLogoColor <= 1.0){
    textLogoColor += 0.005;
  }else{
    glutDisplayFunc(myGlutDisplay);
  }

  glutSwapBuffers();
}
#endif //INTRO_HPP
