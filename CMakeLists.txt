cmake_minimum_required(VERSION 3.30)
project(Marmoset)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(app)
add_subdirectory(libraries)

#cmake_minimum_required(VERSION 3.30)
#project(Marmoset)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(Marmoset
#    main.cpp
#        libraries/marmosetCore/archive/Archive.cpp
#        libraries/marmosetCore/archive/Archive.h
#        libraries/marmosetCore/limpelziv/Decompressor.cpp
#        libraries/marmosetCore/limpelziv/Decompressor.h
#        libraries/marmosetCore/bytestream/ByteStream.cpp
#        libraries/marmosetCore/bytestream/ByteStream.h
#    core/cmd/CommandlineParser.cpp
#    core/cmd/CommandlineParser.h
#)
##
##add_library(Marmoset SHARED
##    core/archive/Archive.cpp
##    core/archive/Archive.h
##    core/archive/decompressor/Decompressor.cpp
##    core/archive/decompressor/Decompressor.h
##    core/bytestream/ByteStream.cpp
##    core/bytestream/ByteStream.h
##)
##
##install(TARGETS Marmoset DESTINATION libs)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
