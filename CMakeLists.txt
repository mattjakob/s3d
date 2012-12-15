# S3D

cmake_minimum_required(VERSION 2.8)

project(s3d C)

set(VERSION 10.0.0)

set(BUILD_SHARED_LIBS false)

set(BASE ${PROJECT_SOURCE_DIR}/base)
set(SCN_DIR ${PROJECT_SOURCE_DIR}/scn)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build)

set(BIN_DIR bin)
set(LIB_DIR lib)
set(INCL_DIR include)
 
find_package(BISON) 
find_package(FLEX)
 
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

include_directories(${SDL_INCLUDE_DIR})

set(OPT_INCLUDE_DIR /opt/local/include)
set(PBM_INCLUDE_DIR /opt/local/include/netpbm)
set(PBM_LIBRARY_DIR /opt/local/lib) 
include_directories(${OPT_INCLUDE_DIR} ${PBM_INCLUDE_DIR})
link_directories(${PBM_LIBRARY_DIR})

include_directories(${BASE}/laux ${BASE}/gp ${BASE}/gutil ${BASE}/geom ${BASE}/color ${BASE}/image ${BASE}/lang ${BASE}/poly ${BASE}/prim ${BASE}/csg ${BASE}/gener ${BASE}/view ${BASE}/clip ${BASE}/raster ${BASE}/shade ${BASE}/scene ${BASE}/hier ${BASE}/visib ${BASE}/ray ${BASE}/rad ${BASE}/map ${BASE}/plot ${BASE}/anim)


add_subdirectory(base)
add_subdirectory(proj)


