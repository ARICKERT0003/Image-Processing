cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "Library for computer vision"
)

#############################
# Set General Variables
#############################
# Library Output Directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(EXTERN_LIB_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(EXTERN_HEADER_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

#############################
# Set Lib Specific Variables 
#############################
# Set YAML Options
set(YAML_CPP_BUILD_TESTS OFF)
set(YAML_CPP_INSTALL OFF)
set(YAML_CPP_BUILD_CONTRIB OFF)
set(YAML_BUILD_SHARED_LIBS ON)
set(BUILD_SHARED_LIBS ON)
set(YAML_CPP_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include/yaml-cpp")

# Set spdlog Options
set(SPDLOG_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include/spdlog")

# Set Camera Options
set(CAMERA_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CAMERA_HEADER_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

#############################
# Recurse into Subdirectories 
#############################
add_subdirectory(yaml-cpp)
add_subdirectory(Camera)

#############################
# Install 
#############################
# YAML header install
install(
  DIRECTORY ${YAML_CPP_HEADERS_DIR}
  DESTINATION ${EXTERN_HEADER_INSTALL_DIR}
)

# Spdlog header install 
install(
  DIRECTORY ${SPDLOG_HEADERS_DIR} 
  DESTINATION ${EXTERN_HEADER_INSTALL_DIR}
)
