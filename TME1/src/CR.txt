# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/tme1>" -*-
#
# Pour voir les commandes lancées par cmake/make, utiliser:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(TME1)
 
 set( CMAKE_C_FLAGS              "-Wall -g" CACHE STRING "C Compiler Release options."   FORCE )
 set( CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE )
 set( CMAKE_INSTALL_PREFIX       "../install" )

                    set( cincludes    cBox.h )
                    set( cs           cMain.c cBox.c )
         add_executable( ctme1        ${cs} )

                install( TARGETS ctme1        DESTINATION bin )
                install( FILES   ${cincludes} DESTINATION include )
