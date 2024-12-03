cmake_minimum_required(VERSION 3.30)
project(Marmoset)

set(CMAKE_CXX_STANDARD 20)

add_executable(Marmoset main.cpp
        core/archive/Archive.cpp
        core/archive/Archive.h
        core/archive/decompressor/Decompressor.cpp
        core/archive/decompressor/Decompressor.h
        core/bytestream/ByteStream.cpp
        core/bytestream/ByteStream.h
        core/cmd/CommandlineParser.cpp
        core/cmd/CommandlineParser.h)
