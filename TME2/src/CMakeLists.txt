# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/tme2>" -*-
#
# Pour voir les commandes lancées par cmake/make, utiliser:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(TME2)

 set( CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE )
 set( CMAKE_INSTALL_PREFIX       "../install" )

    include_directories( ${TME2_SOURCE_DIR} )

                    set( includes     Box.h )
                    set( cpps         Box.cpp
                                      Main.cpp
                       )
         add_executable( tme2         ${cpps} )

                install( TARGETS tme2        DESTINATION bin )
                install( FILES   ${includes} DESTINATION include )

