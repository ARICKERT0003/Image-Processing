cmake_minimum_required(VERSION 3.9.6)
project(Image-Prcessing
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "Library for computer vision"
)

#############################
# General Tools Variables
#############################
set(TOOLS_LIB_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(TOOLS_HEADER_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

#############################
# Set Lib Specific Variables 
#############################
# Set User-Interface Options
set(USER_INTERFACE_BUILD_IMAGE_VIEWER ON CACHE BOOL "Build image-viewer" FORCE)
set(USER_INTERFACE_BUILD_SHARED_LIBS ON CACHE BOOL "Enable shared library" FORCE)
set(IMAGE_VIEWER_LIBRARY_INSTALL_DIR ${TOOLS_LIB_INSTALL_DIR})
set(IMAGE_VIEWER_HEADER_INSTALL_DIR ${TOOLS_HEADER_INSTALL_DIR})

#############################
# Recurse into Subdirectories 
#############################
add_subdirectory(User-Interface)
