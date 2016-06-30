cmake_minimum_required(VERSION 2.8.12)

set(XBOXCONTROLLERPLUGIN_NAME XBoxControllerPlugin)

project(${XBOXCONTROLLERPLUGIN_NAME})

set(XBOXCONTROLLERPLUGIN_MAJOR_VERSION 0)
set(XBOXCONTROLLERPLUGIN_MINOR_VERSION 1)
set(XBOXCONTROLLERPLUGIN_VERSION ${XBOXCONTROLLERPLUGIN_MAJOR_VERSION}.${XBOXCONTROLLERPLUGIN_MINOR_VERSION})

## RPATH
if(UNIX)
    # RPATH is a field in ELF binaries that is used as a hint by the system
    # loader to find needed shared libraries.
    #
    # In the build directory, cmake creates binaries with absolute paths in
    # RPATH.  And by default, it strips RPATH from installed binaries.  Here we
    # use CMAKE_INSTALL_RPATH to set a relative RPATH.  By doing so, we avoid
    # the need to play with LD_LIBRARY_PATH to get applications to run.
    set(CMAKE_INSTALL_RPATH "../lib")

    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_MACOSX_RPATH ON)
    endif()

endif(UNIX)

# set(CMAKE_INSTALL_PREFIX /Volumes/HFS_Data/Sofa/build/master/mac/release/install CACHE TRUE )

############### Files

set(XBOXCONTROLLERPLUGIN_SRC_DIR src/)
include_directories( ${XBOXCONTROLLERPLUGIN_SRC_DIR})
set(HEADER_FILES

    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerPlugin.h
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriverWindows.h
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriver.h

)

set(SOURCE_FILES

    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerPlugin.cpp
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriverWindows.cpp
    ${XBOXCONTROLLERPLUGIN_SRC_DIR}/XBoxControllerDriver.cpp
)

find_package(SofaBase REQUIRED)

# initXBOXCONTROLLERPLUGIN/config.h
configure_file(config.h.in ${XBOXCONTROLLERPLUGIN_NAME}/config.h)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${XBOXCONTROLLERPLUGIN_NAME}/config.h DESTINATION "include/${XBOXCONTROLLERPLUGIN_NAME}")

set(XBOXCONTROLLERPLUGIN_COMPILER_FLAGS "${XBOXCONTROLLERPLUGIN_COMPILER_FLAGS} -DSOFA_BUILD_XBOXCONTROLLERPLUGIN")

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaCore SofaSimulationCore)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC XInput )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${XBOXCONTROLLERPLUGIN_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${XBOXCONTROLLERPLUGIN_COMPILER_FLAGS}")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

install(TARGETS ${PROJECT_NAME}
        COMPONENT ${XBOXCONTROLLERPLUGIN_NAME}_libraries
        EXPORT ${XBOXCONTROLLERPLUGIN_NAME}Targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION "include/${PROJECT_NAME}")

install(DIRECTORY scenes/ DESTINATION ${XBOXCONTROLLERPLUGIN_INSTALL_DIR}/scenes)
install(DIRECTORY data/ DESTINATION ${XBOXCONTROLLERPLUGIN_INSTALL_DIR}/data)

## CMake package configurations files
## TODO
# include(SofaPackageConfigHelpers)
# sofa_write_package_config_files(${XBOXCONTROLLERPLUGIN_NAME} ${XBOXCONTROLLERPLUGIN_VERSION} "" "include")


