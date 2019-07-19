# Find Qt5Keychain
# ~~~~~~~~~~~~~~~
# Copyright (c) 2016, Boundless Spatial
# Author: Larry Shaffer <lshaffer (at) boundlessgeo (dot) com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
# CMake module to search for Qt5Keychain library from:
#    https://github.com/frankosterfeld/qtkeychain
#
# If it's found it sets QT5KEYCHAIN_FOUND to TRUE
# and following variables are set:
#    QT5KEYCHAIN_INCLUDE_DIR
#    QT5KEYCHAIN_LIBRARY

find_path(QT5KEYCHAIN_INCLUDE_DIR
  NAMES
  keychain.h
  PATHS
  $ENV{INCLUDE}
  /usr/local/include
  /usr/include
  PATH_SUFFIXES
  qt5keychain
)

find_library(QT5KEYCHAIN_LIBRARY
  NAMES
  qt5keychain
  libqt5keychain
  PATHS
  /usr/lib
  /usr/lib/${CMAKE_ARCH_TRIPLET}
  /usr/local/lib
  /opt/local/lib
  ${CMAKE_LIBRARY_PATH}
  ${CMAKE_INSTALL_PREFIX}/lib
)

if (QT5KEYCHAIN_INCLUDE_DIR AND QT5KEYCHAIN_LIBRARY)
  set(QT5KEYCHAIN_FOUND TRUE)
else()
  set(QT5KEYCHAIN_FOUND FALSE)
endif (QT5KEYCHAIN_INCLUDE_DIR AND QT5KEYCHAIN_LIBRARY)

if (QT5KEYCHAIN_FOUND)
   if (NOT QT5KEYCHAIN_FIND_QUIETLY)
      message(STATUS "Found Qt5Keychain: ${QT5KEYCHAIN_LIBRARY}")
   endif (NOT QT5KEYCHAIN_FIND_QUIETLY)
else (QT5KEYCHAIN_FOUND)
   if (QT5KEYCHAIN_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find Qt5Keychain")
   endif (QT5KEYCHAIN_FIND_REQUIRED)
endif (QT5KEYCHAIN_FOUND)

if(NOT TARGET Qt5Keychain)
    add_library(Qt5Keychain UNKNOWN IMPORTED)
  set_target_properties(Qt5Keychain
                        PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                   ${QT5KEYCHAIN_INCLUDE_DIR})
  set_property(TARGET Qt5Keychain APPEND PROPERTY IMPORTED_LOCATION ${QT5KEYCHAIN_LIBRARY})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Qt5Keychain DEFAULT_MSG QT5KEYCHAIN_INCLUDE_DIR QT5KEYCHAIN_LIBRARY)

mark_as_advanced(QT5KEYCHAIN_INCLUDE_DIR QT5KEYCHAIN_INCLUDE_DIR)
