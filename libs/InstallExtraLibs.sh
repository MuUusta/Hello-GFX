#!/bin/bash  

#printf "1-g++			2-pThread		3-X11\n"			
#printf "4-Xrandr		5-glut			6-glfw\n"
#printf "7-glm			8-glew			9-Assimp\n"
#printf "10-glu			11-SDL1.2		12-SDL2\n"
#printf "13-SDL-Image		14-SFML			15-SFML-Audio\n"
#printf "16-SFML-Graphics	17-SFML-System		18-mesa-common-dev\n"
#printf "19-build-essential	20-mesa-utils 		21-libgl1-mesa-dev\n"
#printf "22-xclip		23-ffmpeg 		24-libav-tools\n"
#printf "25-boost-all		26-boost-serialization	27-boost\n"

libsMenu="1-g++			2-pThread		3-X11\n4-Xrandr		5-glut			6-glfw\n7-glm			8-glew			9-Assimp\n10-glu			11-SDL1.2		12-SDL2\n13-SDL-Image		14-SFML			15-SFML-Audio\n16-SFML-Graphics	17-SFML-System		18-mesa-common-dev\n19-build-essential	20-mesa-utils 		21-libgl1-mesa-dev\n22-xclip		23-ffmpeg 		24-libav-tools\n25-boost-all		26-boost-serialization	27-boost\n"

printf "$libsMenu"

libNamesArr=(g++ pThread X11 Xrandr glut glfw glm glew Assimp glu SDL1.2 SDL2 SDL-Image SFML SFML-Audio SFML-Graphics SFML-System mesa-common-dev build-essential mesa-utils libgl1-mesa-dev xclip ffmpeg libav-tools boost-all boost-serialization boost)

libInstComm=(g++ libpthread-stubs0-dev libx11-dev libxrandr-dev freeglut3-dev libglfw3-dev libglm-dev libglew-dev libassimp-dev libglu1-mesa-dev libsdl1.2-dev libsdl2-dev libsdl2-image-dev libsfml-dev libsfml-audio2.3v5 libsfml-graphics2.3v5 libsfml-system2.3v5 mesa-common-dev build-essential mesa-utils libgl1-mesa-dev xclip ffmpeg libav-tools libboost-all-dev libboost-serialization-dev libboost-dev)

while :
do
printf "\n\e[38;5;248mType '\e[38;5;35mq\e[38;5;248m' to quit or the number of the lib to install it:\e[38;5;252m"
read -p " " REPLY
if [ "${REPLY,,}" == "q" ]; then
	printf "\n\e[38;5;40m\e[1mGoodBye!\n\e[38;5;15m\e[0m";
	sleep 1
	break
elif [[ $REPLY -gt 0 ]] && [[ $REPLY -le ${#libNamesArr[@]} ]]; then
	for i in  {1..27}; do
	if [[ $REPLY -eq $i ]]; then
		sudo apt-get install ${libInstComm[$i-1]};
		printf "\n\e[38;5;40m\e[1mDone Installing -> \e[38;5;32m${libNamesArr[$i-1]} \e[38;5;15m\e[0m";
		sleep 1
		printf "\n\n$libsMenu"
	fi
	done;
else
	printf "\n\e[38;5;124m\e[1mInvalid Input!\e[0m\e[38;5;15m - \e[38;5;144mPlease Type '\e[38;5;114mq\e[38;5;144m' or any number between '\e[38;5;114m1-${#libNamesArr[@]}\e[38;5;144m'!\e[38;5;15m"
	sleep 2
	printf "\n\n$libsMenu"
fi
done


