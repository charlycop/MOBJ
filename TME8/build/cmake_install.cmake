# Install script for directory: /users/enseig/oudy/Bureau/MOBJ/TME8/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "../install")
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

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../work/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../work/tme810")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../work/tme810"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/../work" TYPE EXECUTABLE FILES "/users/enseig/oudy/Bureau/MOBJ/TME8/build/tme810")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../work/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../work/tme810")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../work/tme810")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Indentation.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/XmlUtil.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Point.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Box.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Term.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Net.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Instance.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Node.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Line.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Shape.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Symbol.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/Cell.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/SaveCellDialog.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/OpenCellDialog.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/InstancesWidget.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/InstancesModel.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/CellWidget.h"
    "/users/enseig/oudy/Bureau/MOBJ/TME8/src/CellViewer.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/users/enseig/oudy/Bureau/MOBJ/TME8/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/users/enseig/oudy/Bureau/MOBJ/TME8/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
