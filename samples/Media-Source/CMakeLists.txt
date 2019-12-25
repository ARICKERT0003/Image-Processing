cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "Media-Source samples"
)

#############################
# Varaibles for all Exe
#############################
link_directories( ${IMGPROC_LIBRARY_OUTPUT_DIR} )

#############################
# Connect
#############################
add_executable( sample-connect sample-connect.cpp )

set_target_properties(sample-connect PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-connect PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-connect PUBLIC Image-Processing ${IMGPROC_LIBS} )

#############################
# Get-Frame
#############################
add_executable( sample-getFrame sample-getFrame.cpp )

set_target_properties(sample-getFrame PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-getFrame PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-getFrame PUBLIC Image-Processing ${IMGPROC_LIBS} )
