# Install script for directory: /home/thecitystate/shooter/assimp/code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
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
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libassimp.so.1.0.0")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libassimp.so.1.0.0"
         RPATH "")
  ENDIF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libassimp.so.1.0.0")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/home/thecitystate/shooter/assimp/lib/libassimp.so.1.0.0"
    "/home/thecitystate/shooter/assimp/lib/libassimp.so.1"
    "/home/thecitystate/shooter/assimp/lib/libassimp.so"
    )
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libassimp.so.1.0.0")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libassimp.so.1.0.0")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libassimp.so.1.0.0")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/assimp" TYPE FILE FILES
    "/home/thecitystate/shooter/assimp/code/../include/aiAnim.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiAssert.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiCamera.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiColor4D.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiColor4D.inl"
    "/home/thecitystate/shooter/assimp/code/../include/aiConfig.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiDefines.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiFileIO.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiLight.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiMaterial.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiMaterial.inl"
    "/home/thecitystate/shooter/assimp/code/../include/aiMatrix3x3.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiMatrix3x3.inl"
    "/home/thecitystate/shooter/assimp/code/../include/aiMatrix4x4.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiMatrix4x4.inl"
    "/home/thecitystate/shooter/assimp/code/../include/aiMesh.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiPostProcess.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiQuaternion.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiScene.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiTexture.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiTypes.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiVector2D.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiVector3D.h"
    "/home/thecitystate/shooter/assimp/code/../include/aiVector3D.inl"
    "/home/thecitystate/shooter/assimp/code/../include/aiVersion.h"
    "/home/thecitystate/shooter/assimp/code/../include/assimp.h"
    "/home/thecitystate/shooter/assimp/code/../include/assimp.hpp"
    "/home/thecitystate/shooter/assimp/code/../include/DefaultLogger.h"
    "/home/thecitystate/shooter/assimp/code/../include/IOStream.h"
    "/home/thecitystate/shooter/assimp/code/../include/IOSystem.h"
    "/home/thecitystate/shooter/assimp/code/../include/Logger.h"
    "/home/thecitystate/shooter/assimp/code/../include/LogStream.h"
    "/home/thecitystate/shooter/assimp/code/../include/NullLogger.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/assimp/Compiler" TYPE FILE FILES
    "/home/thecitystate/shooter/assimp/code/../include/Compiler/pushpack1.h"
    "/home/thecitystate/shooter/assimp/code/../include/Compiler/poppack1.h"
    "/home/thecitystate/shooter/assimp/code/pstdint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

