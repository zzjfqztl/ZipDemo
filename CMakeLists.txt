cmake_minimum_required(VERSION 3.17) 

#设置C++的版本为11，所有的工程统一最低使用11
set(CMAKE_CXX_STANDARD 11)

set(TARGET_NAME QuaZip_Demo)
add_definitions(-D APP_NAME="\\"QuaZip_Demo\\"")
project(${TARGET_NAME})

option(BUILD_SHARED_LIBS "" ON)
option(QUAZIP_INSTALL "" ON)
option(QUAZIP_USE_QT_ZLIB "" OFF)
option(QUAZIP_ENABLE_TESTS "Build QuaZip tests" OFF)
set(QUAZIP_QT_MAJOR_VERSION 5 CACHE STRING "Qt version to use (4, 5 or 6), defaults to 5")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

set(DEMO_SDK ${CMAKE_SOURCE_DIR}/SDK/)
set(3RD_PARTY ${CMAKE_SOURCE_DIR}/SDK/3rdParty)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(EXISTS "${CMAKE_SOURCE_DIR}/deploy.cmake")
    message("deploy.cmake")
	include("deploy.cmake")
else()
    message("deploy.cmake.local")
	include("deploy.cmake.local")
endif()


include_directories (${CMAKE_SOURCE_DIR})
include_directories (${3RD_PARTY})

add_definitions( -DAPP_VERSION=${APP_VERSION})
add_definitions( -DAPP_BUILD_NUMBER=${APP_BUILD_NUMBER} )
add_definitions( -DAPP_BUILD_TIME=${APP_BUILD_TIME} )


add_definitions(-DQT_CC_WARNINGS)
add_subdirectory(SDK)
add_subdirectory(Demo)
