# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/4-5>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)
 
 set (CMAKE_CXX_FLAGS            "-Wall -g -std=c++11"  CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

# Detection de LibXml2.
find_package(LibXml2)

# Trouver les includes de LibXml2.
   include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR} )



# Faire l'edition de liens avec la LibXml2.
#target_link_libraries ( tme6 ${LIBXML2_LIBRARIES} )


    include_directories( ${SCHEMATIC_SOURCE_DIR}
                       )

                    set( includes     Indentation.h
                                      Term.h
                                      Net.h
                                      Instance.h
                                      Point.h
                                      Node.h
                                      Cell.h
                                      XmlUtil.h
                        				      Box.h
                        				      Line.h
                                      Symbol.h
				                              Shape.h
					
                       )

                    set( cpps         Indentation.cpp
                                      Term.cpp
                                      Net.cpp
                                      Instance.cpp
                                      Point.cpp
                                      Node.cpp
                                      Cell.cpp
                                      Main.cpp
                                      XmlUtil.cpp
                        				      Box.cpp
                        				      Line.cpp
                        				      Shape.cpp
                                      Symbol.cpp
                       )

        add_executable ( tme7        ${cpps} )
               install ( TARGETS      tme7        DESTINATION "../work"  )
               install ( FILES        ${includes}  DESTINATION include )
# Faire l'edition de liens avec la LibXml2.
target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )


