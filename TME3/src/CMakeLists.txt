# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/tme3>" -*-
#
# Pour voir les commandes lancées par cmake/make, utiliser:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(TME3)

 set (CMAKE_CXX_FLAGS            "-Wall -g -std=c++11" CACHE STRING
                                 "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

    include_directories( ${TME3_SOURCE_DIR})

                    set( includes     
                                    vector.h
                                    GPL_2_text.h
                                      timer.h )
                    set( cpps         vector.cpp
                                      Main.cpp )
         add_executable( tme3         ${cpps} )

               #install( TARGETS tme3        DESTINATION bin )
                install( TARGETS tme3        DESTINATION "../work" )
                install( FILES   ${includes} DESTINATION include )
