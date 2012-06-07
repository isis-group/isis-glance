###########################################################
#ISIS-Glance project
#
# Main CMake configuration file of the ISIS project.
#
# Author: Erik Tuerke <etuerke@googlemail.com>
# Date: Thu, 07 Jun 2012 16:44:23 +0200
#
############################################################

cmake_minimum_required(VERSION 2.6)

include(InstallRequiredSystemLibraries)

project(isis-glance)

############################################################
# set isis version number
############################################################
set(ISIS_GLANCE_VERSION_MAJOR "0")
set(ISIS_GLANCE_VERSION_MINOR "1")
set(ISIS_GLANCE_VERSION_PATCH "0")

add_definitions(-D_ISIS_GLANCE_VERSION_MAJOR=${ISIS_GLANCE_VERSION_MAJOR})
add_definitions(-D_ISIS_GLANCE_VERSION_MINOR=${ISIS_GLANCE_VERSION_MINOR})
add_definitions(-D_ISIS_GLANCE_VERSION_PATCH=${ISIS_GLANCE_VERSION_PATCH})

set(ISIS_GLANCE_VERSION
  ${ISIS_GLANCE_VERSION_MAJOR}.${ISIS_GLANCE_VERSION_MINOR}.${ISIS_GLANCE_VERSION_PATCH}
  CACHE INTERNAL "The current Version of the ISIS-Glance project")

set(ISIS_GLANCE_VERSION_API "0.0.0")

STRING( REGEX MATCH "^[0-9]+" ISIS_GLANCE_VERSION_SO ${ISIS_GLANCE_VERSION_API})

if(NOT WIN32)
############################################################
# set install infix for plugin installation path
############################################################
set(ISIS_GLANCE_WIDGET_INFIX lib/isis-glance/widgets)
endif(NOT WIN32)

############################################################
# set project specific module path
############################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

############################################################
# general compiler flags
############################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wstrict-aliasing=2" )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wstrict-aliasing=2"  )

############################################################
# compiler flags on 64Bit cpus
############################################################

if(${APPLE})
  if(${CMAKE_OSX_ARCHITECTURES})
    set(PROCESSOR ${CMAKE_OSX_ARCHITECTURES})
  else(${CMAKE_OSX_ARCHITECTURES})
    set(PROCESSOR "x86_64")
  endif(${CMAKE_OSX_ARCHITECTURES})
else(${APPLE})
  set(PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
endif(${APPLE})

if("${PROCESSOR}" STREQUAL "x86_64")
  message(STATUS "Compiling on x86_64. Using the '-fPIC' option in any case")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC"  )
endif("${PROCESSOR}" STREQUAL "x86_64" )

############################################################
# RCS revision number
############################################################
# The revision number is based on GIT commit informations.
# It will be stored in GIT_REVISION.
find_program(GIT_COMMAND git DOC "The rcs revision description information tool.")

if (NOT GIT_REVISION)
  if (GIT_COMMAND)
    execute_process(COMMAND ${GIT_COMMAND} describe OUTPUT_VARIABLE OUT WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX MATCH "[0-9]+-[^-]+$" GIT_REVISION "${OUT}") #@todo wont work with more complex revisions/modified sources
    set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${GIT_REVISION}-${CMAKE_SYSTEM_NAME}-${PROCESSOR}-${CMAKE_BUILD_TYPE})
  else(GIT_COMMAND)
    message(STATUS "git not found")
  endif (GIT_COMMAND)
endif (NOT GIT_REVISION)

if (GIT_REVISION)
  message(STATUS "RCS Revision: ${GIT_REVISION}")
  add_definitions(-DISIS_RCS_REVISION=${GIT_REVISION})
  set(ISIS_CORE_REV_STRING ${ISIS_GLANCE_VERSION_MAJOR}.${ISIS_GLANCE_VERSION_MINOR}.${ISIS_GLANCE_VERSION_PATCH}-${GIT_REVISION})
else(GIT_REVISION)
  set(ISIS_CORE_REV_STRING ${ISIS_GLANCE_VERSION_MAJOR}.${ISIS_GLANCE_VERSION_MINOR}.${ISIS_GLANCE_VERSION_PATCH})
endif(GIT_REVISION)

###########################################################
# CPack config
###########################################################
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "isis glance library")
SET(CPACK_PACKAGE_VENDOR "the friendly isis team")
SET(CPACK_PACKAGE_CONTACT "etuerke@googlemail.com")
SET(CPACK_PACKAGE_NAME "isis-glance")
SET(CPACK_BUNDLE_NAME ${CPACK_PACKAGE_NAME})
SET(CPACK_COMPONENTS_ALL "RuntimeLibraries")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${ISIS_GLANCE_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${ISIS_GLANCE_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${ISIS_GLANCE_VERSION_PATCH})
SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${ISIS_CORE_REV_STRING}-${CMAKE_SYSTEM_NAME}-${PROCESSOR}-${CMAKE_BUILD_TYPE})
#SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${ISIS_VERSION_MAJOR}.${ISIS_VERSION_MINOR}")
SET(CPACK_NSIS_MODIFY_PATH ON)
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\isis-group.github.com/isis-glance")
INCLUDE(CPack)

# build the ISIS-Glance libraries
add_subdirectory(lib)

# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake//cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)