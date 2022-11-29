cmake_minimum_required(VERSION 3.12)
project(XBoxControllerPlugin VERSION 1.0 LANGUAGES CXX)

set(XBOXCONTROLLERPLUGIN_SRC_DIR src/XBoxControllerPlugin)

set(HEADER_FILES
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/config.h.in
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerPlugin.h
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriverWindows.h
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriver.h
)

set(SOURCE_FILES
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerPlugin.cpp
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriverWindows.cpp
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriver.cpp
)

find_package(Sofa.Simulation.Core REQUIRED)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Sofa.Core Sofa.Simulation.Core)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC XInput )
endif()

## Install rules for the library; CMake package configurations files
sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${PROJECT_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR "${PROJECT_NAME}"
    RELOCATABLE "plugins"
    )
