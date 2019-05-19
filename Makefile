CXX = g++

exec = Hello-GFX

VERSION = -std=c++11

Current_Dir = $(shell pwd)

WARNFLAGS =-Wall -Wextra -Wunused

Extra_Libs_Script = bash libs/InstallExtraLibs.sh

Update = sudo apt-get update

OpenGLLibs =mesa-common-dev build-essential mesa-utils libgl1-mesa-dev

Linux_Needed_Libs =xclip ffmpeg libav-tools libboost-dev libboost-serialization-dev

MoveLibFiles = sudo cp -an $(Current_Dir)/libs/compiled-lib-files/. /usr/lib/x86_64-linux-gnu

FLAGS = -lGLEW -lGL -lGLU -lassimp -lX11 -lpthread -lglut -lsfml-audio -lsfml-system -lboost_serialization

Dependencies = -I$(Current_Dir)/libs/ -I$(Current_Dir)/libs/compiled-lib-files/ -I$(Current_Dir)/includes/ -I$(Current_Dir)/learnOpenGL-tut/includes/

OBJS = main.o imgui.o imgui_draw.o imgui_impl_freeglut.o imgui_impl_opengl2.o imgui_widgets.o textureLoading.o filemanager.o styleEditor.o resources.o fog.o musicPlayer.o userData.o fontLoader.o


all: $(OBJS)
	@$(CXX) $(VERSION) $(OBJS) $(Dependencies) $(FLAGS) -o $(exec)
	make move
	./Hello-GFX

main.o: main.cpp
	$(CXX) $(VERSION) $(Dependencies) -c main.cpp

imgui.o: libs/imgui/imgui.cpp
	$(CXX) -c $(VERSION) $(Dependencies) libs/imgui/imgui.cpp

imgui_draw.o: libs/imgui/imgui_draw.cpp
	$(CXX) -c $(VERSION) $(Dependencies) libs/imgui/imgui_draw.cpp

imgui_impl_freeglut.o: libs/imgui/imgui_impl_freeglut.cpp
	$(CXX) -c $(VERSION) $(Dependencies) libs/imgui/imgui_impl_freeglut.cpp

imgui_impl_opengl2.o: libs/imgui/imgui_impl_opengl2.cpp
	$(CXX) -c $(VERSION) $(Dependencies) libs/imgui/imgui_impl_opengl2.cpp

imgui_widgets.o: libs/imgui/imgui_widgets.cpp
	$(CXX) -c $(VERSION) $(Dependencies) libs/imgui/imgui_widgets.cpp

textureLoading.o: includes/textureLoading.cpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/textureLoading.cpp

filemanager.o: includes/filemanager.cpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/filemanager.cpp

styleEditor.o: includes/styleEditor.cpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/styleEditor.cpp

resources.o: includes/resources.cpp includes/resources.hpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/resources.cpp

fog.o: includes/fog.cpp includes/fog.hpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/fog.cpp

musicPlayer.o: includes/musicPlayer.cpp includes/musicPlayer.hpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/musicPlayer.cpp

userData.o: includes/userData.cpp includes/userData.hpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/userData.cpp

fontLoader.o: includes/fontLoader.cpp includes/fontLoader.hpp
	$(CXX) -c $(VERSION) $(Dependencies) includes/fontLoader.cpp

install:
	@$(Update); sudo apt-get install $(OpenGLLibs) $(Linux_Needed_Libs)
	@$(MoveLibFiles)
	@make all

install-extra:
	@$(Extra_Libs_Script)
	
move:
	@mv -f *.o bin/

clean:
	@rm *.o $(exec)



