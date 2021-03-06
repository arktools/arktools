cmake_minimum_required(VERSION 2.8)

project(arktools)

# package info
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_CONTACT "james.goppert@gmail.com")

# dependencies
set(PLIB_REQUIRED_VERSION                   1.8.5) # joystick 
set(BOOST_REQUIRED_VERSION                  1.4.2) # math, serial
set(OPENSCENEGRAPH_REQUIRED_VERSION         3.0.0) # 3D graphics
set(MAVLINK_REQUIRED_VERSION                1.0.0) # MAVLink comm protocol

# options
option(WITH_PREFER_STATIC "Prefer static linking." ON)
set(WITH_SUPPORT_TEST "Build support library unit tests." ON)

# modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CPack)
enable_testing()

# find packages
#   prefer static packages if building static library
if (WITH_PREFER_STATIC)
    set(Boost_USE_STATIC_LIBS ON)
    # prefer static libs
    if(WIN32)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
endif()
find_package(PLIB ${PLIB_REQUIRED_VERSION} REQUIRED COMPONENTS js ul)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost ${BOOST_REQUIRED_VERSION} REQUIRED COMPONENTS system thread)
if (APPLE)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(CARBON_LIBRARY Carbon)
endif()
find_package(Threads)
find_program(SCILAB_ADV_CLI scilab-adv-cli)
find_package(OpenGL REQUIRED)
find_package(OpenSceneGraph ${OPENSCENEGRAPH_REQUIRED_VERSION} REQUIRED COMPONENTS osgViewer osgText osgUtil osgDB osgGA osgManipulator)
find_package(OsgPlugin ${OPENSCENEGRAPH_REQUIRED_VERSION} REQUIRED COMPONENTS ac rgb)
find_package(MAVLink ${MAVLINK_REQUIRED_VERSION} REQUIRED)

# config files
configure_file(config.h.in config.h)
install(FILES ${CMAKE_BINARY_DIR}/config.h DESTINATION include/${PROJECT_NAME} COMPONENT Dev)

# build settings
add_definitions(-DOSG_LIBRARY_STATIC)

# library
add_subdirectory(src)

# data
add_subdirectory(data)

# test
add_subdirectory(test)
