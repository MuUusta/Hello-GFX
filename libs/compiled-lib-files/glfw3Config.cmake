# - Config file for the glfw3 package
# It defines the following variables
#   GLFW3_INCLUDE_DIR, the path where GLFW headers are located
#   GLFW3_LIBRARY_DIR, folder in which the GLFW library is located
#   GLFW3_LIBRARY, library to link against to use GLFW

set(GLFW3_VERSION "3.1.2")


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was glfw3Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../" ABSOLUTE)

# Use original install prefix when loaded through a "/usr move"
# cross-prefix symbolic link such as /lib -> /usr/lib.
get_filename_component(_realCurr "${CMAKE_CURRENT_LIST_DIR}" REALPATH)
get_filename_component(_realOrig "/usr/lib/x86_64-linux-gnu/cmake/glfw3/" REALPATH)
if(_realCurr STREQUAL _realOrig)
  set(PACKAGE_PREFIX_DIR "/usr")
endif()
unset(_realOrig)
unset(_realCurr)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

set_and_check(GLFW3_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include")
set_and_check(GLFW3_LIBRARY_DIR "${PACKAGE_PREFIX_DIR}/lib/x86_64-linux-gnu")

find_library(GLFW3_LIBRARY "glfw" HINTS ${GLFW3_LIBRARY_DIR})

