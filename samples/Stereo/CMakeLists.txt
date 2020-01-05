cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "Stereo samples"
)

#############################
# Varaibles for all Exe
#############################
link_directories( ${IMGPROC_LIBRARY_OUTPUT_DIR} )

#############################
# Connect
#############################
add_executable( sample-stereo-connect sample-stereo-connect.cpp )

set_target_properties(sample-stereo-connect PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-stereo-connect PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-stereo-connect PUBLIC Image-Processing ${IMGPROC_LIBS} )

#############################
# Get-Frame
#############################
add_executable( sample-stereo-getFrame sample-stereo-getFrame.cpp )

set_target_properties(sample-stereo-getFrame PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-stereo-getFrame PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-stereo-getFrame PUBLIC Image-Processing ${IMGPROC_LIBS} )
