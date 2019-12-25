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
 
  # Media-Source
  if(IMGPROC_BUILD_SAMPLE_MEDIA_SOURCE)
    message("OK, building Media-Source")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Media-Source)
  endif()

  # User-Interface
  if(IMGPROC_BUILD_SAMPLE_USER_INTERFACE)
    add_subdirectory(User-Interface)
  endif()

  # File-Handler
  if(IMGPROC_BUILD_SAMPLE_FILE_HANDLER)
    add_subdirectory(File-Handler)
  endif()

  # Filter
  if(IMGPROC_BUILD_SAMPLE_FILTER)
    add_subdirectory(Filter)
  endif()

  #Stereo
  if(IMGPROC_BUILD_SAMPLE_STEREO)
    add_subdirectory(Stereo)
  endif()

endif()
