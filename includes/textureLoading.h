#ifndef TEXTURELOADING_H
#define TEXTURELOADING_H

#include <GL/glew.h>
#include <boost/algorithm/string.hpp>
#include <string.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

#include <GL/freeglut.h>
/* Image type - contains height, width, and data */
struct Image {
  unsigned long sizeX;
  unsigned long sizeY;
  char *data;
};

typedef struct Image Image;
/*
* getint and getshort arehelp functions to load the bitmap byte by byte on
* SPARC platform.
* I've got them from xv bitmap load routinebecause the original bmp loader didn't work
* I've tried to change as less code as possible.
*/
static unsigned int getint(FILE *fp);
static unsigned int getshort(FILE *fp);
// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(const char *filename, Image *image);
// Load Bitmaps And Convert To Textures
unsigned int LoadGLTextures(const char* path);
GLuint loadTex_stb(const char *path);
GLuint logl_loadTex_stb(const char *path, bool gammaCorrection);
unsigned int logl_loadTex_stb(char const * path);
GLuint loadTex_stb(const char *path, int &my_image_width, int &my_image_height);
unsigned int loadCubemap(vector<std::string> faces);

#endif //TEXTURELOADING_H
