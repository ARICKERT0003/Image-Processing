cmake_minimum_required(VERSION 3.9.6)
project(Image-Processing
  LANGUAGES CXX
  VERSION   1.0.0
  DESCRIPTION "User-Interface samples"
)

#############################
# Varaibles for all Exe
#############################
link_directories( ${IMGPROC_LIBRARY_OUTPUT_DIR} )

#############################
# Camera
#############################
add_executable( sample-UI-addWindow sample-UI-addWindow.cpp )

set_target_properties(sample-UI-addWindow PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-UI-addWindow PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-UI-addWindow PUBLIC Image-Processing ${IMGPROC_LIBS} )

#############################
# Camera
#############################
add_executable( sample-UI-camera sample-UI-camera.cpp )

set_target_properties(sample-UI-camera PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-UI-camera PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-UI-camera PUBLIC Image-Processing ${IMGPROC_LIBS} )

#############################
# Stereo
#############################
add_executable( sample-UI-stereo sample-UI-stereo.cpp )

set_target_properties( sample-UI-stereo PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories( sample-UI-stereo PUBLIC ${IMGPROC_INC_DIRS} )
target_link_libraries( sample-UI-stereo PUBLIC Image-Processing ${IMGPROC_LIBS} )
