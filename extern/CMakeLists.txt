cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "Library for computer vision"
)

#############################
# Set General Variables
#############################
# Release or Debug
set(CMAKE_BUILD_TYPE Release)

#############################
# Recurse into Subdirectories 
#############################
# SPDLOG
set(SPDLOG_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include/spdlog")
set( SPDLOG_HEADER_INSTALL_DIR ${IMGPROC_EXTERN_HEADER_INSTALL_DIR})

install(
  DIRECTORY ${SPDLOG_HEADER_DIR} 
  DESTINATION ${SPDLOG_HEADER_INSTALL_DIR}
)

#YAML_CPP
if(NOT TARGET yaml-cpp)
  set(YAML_CPP_BUILD_TESTS OFF)
  set(YAML_CPP_INSTALL OFF)
  set(YAML_CPP_BUILD_CONTRIB OFF)
  set(YAML_BUILD_SHARED_LIBS ON)
  set(BUILD_SHARED_LIBS ON)
  set(YAML_CPP_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include/yaml-cpp)
  set(YAML_CPP_HEADER_INSTALL_DIR ${IMGPROC_EXTERN_HEADER_INSTALL_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${IMGPROC_EXTERN_LIBRARY_OUTPUT_DIR})

  # Recurse into yaml-cpp
  add_subdirectory(yaml-cpp)

  # YAML header install
  install(
    DIRECTORY ${YAML_CPP_HEADER_DIR}
    DESTINATION ${YAML_CPP_HEADER_INSTALL_DIR}
  )
endif()
