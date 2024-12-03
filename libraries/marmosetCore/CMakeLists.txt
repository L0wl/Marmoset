cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
project(MarmosetCore)
add_library(MarmosetCore SHARED
        archive/Archive.h
        archive/Archive.cpp
        bytestream/ByteStream.h
        bytestream/ByteStream.cpp
        limpelziv/Decompressor.h
        limpelziv/Decompressor.cpp
)

target_include_directories(MarmosetCore PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/archive>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bytestream>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/limpelziv>
        $<INSTALL_INTERFACE:include/MarmosetCore>
)

target_include_directories(MarmosetBridgeApp PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/libraries/marmosetCore/archive>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/libraries/marmosetCore/bytestream>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/libraries/marmosetCore/limpelziv>
)