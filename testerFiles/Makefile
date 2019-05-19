NAME = exe
SRC = main.cpp glad.c
current_dir = $(shell pwd)

INCLUDES = /usr/include/GL/glut.h /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/glm/glm.hpp /usr/include/GLFW/glfw3.h 
IFLAGS = -I/usr/include/freetype2 -I$(current_dir) -I$(current_dir)/../libs/ -I$(current_dir)/../../libs/
CXX = g++
VERSION = -std=gnu++11
LIBS = -lGLEW -lGL -lGLU -lSDL -lassimp -lglfw -lX11 -lpthread -lXxf86vm -lglut -lsfml-audio -lsfml-system -ldl

$(NAME): $(SRC) $(INCLUDES)
	@$(CXX) $(VERSION) $(SRC) $(IFLAGS) $(LIBS) -o $(NAME) 2>error.log

