# FlightControlUnit

| Author | Created | 
| ------ | ------- |
| Alex Rickert | 12/17/2019 |

## Table of Contents

  - [Overview](#overview)
  - [Dependencies](#dependencies)
  - [Using the library](#using-the-library)
  - [Tests](#tests)
    - [How to build samples](#how-to-build-tests)
    - [Available samples](#available-tests)
      - [Sample 1](#sample1)
      - [Sample 2](#sample2)

---

## Overview

Library for various image processing modules

## Dependencies

- OpenCV 3.3.1
- Computer running Linux distribution
- C++14

## Using the library

1. Clone Image-Processing to project directory
   
    `git clone https://github.com/ARICKERT0003/FlightControlUnit.git`

    or 

    `git clone git@github.com:ARICKERT0003/FlightControlUnit.git`

2. Clone submodules into Image-Processing directory
    
    ```
    cd Image-Processsing
    git submodule update --init -recursive
    ```

3. First time build
   
    1. #### Make Build Directory
      
      `mkdir build && cd build`

    2. #### Build External Libraries

      `cmake -DIMGPROC_BUILD_EXTERN=ON .. && make install`

    3. #### Build Samples [Optional]
    
       Must be done after all previous steps. Will build all samples in sample
       directory.

      `cmake -DIMGPROC_BUILD_SAMPLES=ON .. && make`

4. Build options

    1. #### External Libraries
         
         * fmt
         * spdlog
         * yaml-cpp
         * Camera

    2. #### Build Flags  
        
         * 
      
## Samples

Sample code for features of the library are located in the `samples/` directory.

### How to build samples

### Available Samples

1. #### File:

    1. #### sample-file

    Loosely tests the following capabilities
    
      * Read / write single image to file
      * Read / write multiple images to same file while incrementing filename
      * Read / write vector of images to same file while incrementing filename
      * Read / write primitive values to YAML file
      * Read / write string to YAML file
      * Read / write values to a map in YAML file
      * Read / write values to a sequence in to YAML file

2. #### Image-Viewer:

    1. #### sample-image-viewer

    Loosely tests the following capabilities

      * Starting / stopping image-viewer 
      * Adding windows
      * Save image to vector
      * Save image to file 

