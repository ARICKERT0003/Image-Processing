cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "File-Handler samples"
)

#############################
# Variables for all Exe
#############################
link_directories( ${IMGPROC_LIBRARY_OUTPUT_DIR} )

#############################
# Add Path
#############################
add_executable( sample-calibration-camera sample-calibration-camera.cpp )

set_target_properties( sample-calibration-camera PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-calibration-camera PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-calibration-camera PUBLIC Image-Processing ${IMGPROC_LIBS} )

#############################
# Load
#############################
#add_executable( sample-filehandler-load sample-filehandler-load.cpp )
#
#set_target_properties( sample-filehandler-load PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#target_include_directories( sample-filehandler-load PUBLIC ${IMGPROC_INC_DIRS} )
#target_link_libraries( sample-filehandler-load PUBLIC Image-Processing ${IMGPROC_LIBS} )

##############################
## Stereo
##############################
#add_executable( sample-filehandler-stereo sample-filehandler-stereo.cpp )
#
#set_target_properties( sample-filehandler-stereo PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#target_include_directories( sample-filehandler-stereo PUBLIC ${IMGPROC_INC_DIRS} )
#target_link_libraries( sample-filehandler-stereo PUBLIC Image-Processing ${IMGPROC_LIBS} )
