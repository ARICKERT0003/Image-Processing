cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "File-Handler samples"
)

#############################
# Varaibles for all Exe
#############################
link_directories( ${IMGPROC_LIBRARY_OUTPUT_DIR} )

#############################
# Filehandler
#############################
add_executable( sample-filehandler-addPath sample-filehandler-addPath.cpp )

set_target_properties( sample-filehandler-addPath PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-filehandler-addPath PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-filehandler-addPath PUBLIC Image-Processing ${IMGPROC_LIBS} )

#############################
# Camera
#############################
#add_executable( sample-filehandler-camera sample-filehandler-camera.cpp )
#
#set_target_properties( sample-filehandler-camera PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#target_include_directories( sample-filehandler-camera PUBLIC ${IMGPROC_INC_DIRS} )
#target_link_libraries( sample-filehandler-camera PUBLIC Image-Processing ${IMGPROC_LIBS} )
#
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
