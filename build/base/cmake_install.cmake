# Install script for directory: /Users/mattjakob/Downloads/s3d/base

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/mattjakob/Downloads/s3d/build")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/laux/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/gp/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/gutil/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/geom/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/color/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/image/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/lang/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/poly/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/prim/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/csg/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/gener/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/view/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/clip/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/raster/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/shade/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/scene/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/hier/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/visib/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/ray/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/rad/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/map/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/plot/cmake_install.cmake")
  INCLUDE("/Users/mattjakob/Downloads/s3d/build/base/anim/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

