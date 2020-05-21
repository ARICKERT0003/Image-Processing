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
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS 
#  PRIVATE
#  "$<$<CONFIG:Debug>:${IMGPROC_DEBUG_FLAGS}>"
#  "$<$<CONFIG:Release>:${IMGPROC_RELEASE_FLAGS}>"
#)

#############################
# Recurse into Subdirectories 
#############################
if(IMGPROC_BUILD_SAMPLES)
 
  # Calibration
  if(IMGPROC_BUILD_SAMPLE_CALIBRATION)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Calibration)
  endif()

  # File
  if(IMGPROC_BUILD_SAMPLE_FILE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/File)
  endif()

  # File-Handler
  if(IMGPROC_BUILD_SAMPLE_FILE_HANDLER)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/File-Handler)
  endif()

  # Filter
  if(IMGPROC_BUILD_SAMPLE_FILTER)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Filter)
  endif()

  # Image-Viewer
  if(IMGPROC_BUILD_SAMPLE_IMAGE_VIEWER)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Image-Viewer)
  endif()

  # Media-Source
  if(IMGPROC_BUILD_SAMPLE_MEDIA_SOURCE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Media-Source)
  endif()

  # Stereo
  if(IMGPROC_BUILD_SAMPLE_STEREO)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Stereo)
  endif()

endif()
