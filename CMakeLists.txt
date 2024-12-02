cmake_minimum_required(VERSION 3.30)
project(Marmoset)

set(CMAKE_CXX_STANDARD 20)

add_executable(Marmoset main.cpp
        core/Archive.cpp
        core/Archive.h
        core/Decompressor.cpp
        core/Decompressor.h
        core/ByteStream.cpp
        core/ByteStream.h)
