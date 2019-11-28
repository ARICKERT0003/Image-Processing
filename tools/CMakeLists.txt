cmake_minimum_required(VERSION 3.9.6)
project(Image-Prcessing
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "Library for computer vision"
)

#############################
# General Tools Variables
#############################
set(TOOLS_LIBRARY_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(TOOLS_LIBRARY_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install")
set(TOOLS_HEADER_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

#############################
# Set Lib Specific Variables 
#############################
# Set User-Interface Options
set(USER_INTERFACE_BUILD_IMAGE_VIEWER ON CACHE BOOL "Build image-viewer" FORCE)
set(USER_INTERFACE_BUILD_SHARED_LIBS ON CACHE BOOL "Enable shared library" FORCE)
set(USER_INTERFACE_BUILD_EXTERN OFF CACHE BOOL "Enable shared library" FORCE)
set(IMAGE_VIEWER_LIBRARY_INSTALL_DIR ${TOOLS_LIB_INSTALL_DIR})
set(IMAGE_VIEWER_LIBRARY_DIR ${TOOLS_LIBRARY_OUTPUT_DIR})
set(IMAGE_VIEWER_HEADER_INSTALL_DIR ${TOOLS_HEADER_INSTALL_DIR})
set(USER_INTERFACE_EXTERN_LIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../extern/lib)
set(USER_INTERFACE_EXTERN_INC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../extern/inc)
set(MEDIA_PIPELINE_LIBRARY_OUTPUT_DIR ${TOOLS_LIBRARY_OUTPUT_DIR})
set(MEDIA_PIPELINE_LIBRARY_INSTALL_DIR ${TOOLS_LIBRARY_INSTALL_DIR})
set(MEDIA_PIPELINE_HEADER_INSTALL_DIR ${TOOLS_HEADER_INSTALL_DIR})

#############################
# Recurse into Subdirectories 
#############################
add_subdirectory(User-Interface)
