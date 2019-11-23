cmake_minimum_required(VERSION 3.9.6)
project(Vision-Sample
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "Camera connection sample"
)

#############################
# Declare Variables and Flags
#############################
# Releae or Debug
set(CMAKE_BUILD_TYPE Debug)
set(EXEC_NAME vision-sample-getFrame)
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
  sample-getFrame.cpp
)

# Include Files
set(INC_FILES
)

# Declare Libraries
set(MY_LIBS
  ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libVision.so
)

find_package(OpenCV REQUIRED)

set(MY_INC_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
  ${CMAKE_CURRENT_SOURCE_DIR}/../../extern/inc
)

add_executable(${EXEC_NAME}
  ${SRC_FILES}
  ${INC_FILES}
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
  ${OpenCV_LIBS}
  ${MY_LIBS}
)
