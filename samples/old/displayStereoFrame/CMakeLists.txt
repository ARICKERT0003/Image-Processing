cmake_minimum_required(VERSION 3.9.6)
project(Vision-Sample
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "Camera connection sample"
)

#############################
# Declare Variables and Flags
#############################
# Release or Debug
set(CMAKE_BUILD_TYPE Debug)
set(EXEC_NAME vision-sample-displayStereoFrame)
set(SH_VER 1.0)

# Base Compiler Flags
set(MY_DEBUG_FLAGS 
  -Wall 
  -Wextra
  -Werror
  -W
  -DDEBUG
  -g
)

set(MY_RELEASE_FLAGS
  -pedantic
  -03
)

# Source Files
set(SRC_FILES
  sample-displayStereoFrame.cpp
)

set(MY_LIBS
  ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libVision.so
  ${CMAKE_CURRENT_SOURCE_DIR}/../../tools/lib/libImage-Viewer.so
)

set(MY_INC_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
  ${CMAKE_CURRENT_SOURCE_DIR}/../../tools/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/../../extern/inc
)

#############################
# Link Libraries
#############################
find_package(OpenCV REQUIRED)

add_executable(${EXEC_NAME}
  ${SRC_FILES}
)

set_target_properties(${EXEC_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Target Compiler Flags
target_compile_options( ${EXEC_NAME}
  PRIVATE
  "$<$<CONFIG:Debug>:${MY_DEBUG_FLAGS}>"
  "$<$<CONFIG:Release>:${MY_RELEASE_FLAGS}>"
)

# Target Include Directories
target_include_directories( ${EXEC_NAME}
  PUBLIC
  ${MY_INC_DIRS}
)

target_link_libraries( ${EXEC_NAME}
  PUBLIC
  ${MY_LIBS}
  ${OpenCV_LIBS}
)
