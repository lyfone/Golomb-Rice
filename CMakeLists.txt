cmake_minimum_required(VERSION 3.9)
project(Golomb_Rice)

set(CMAKE_CXX_STANDARD 11)

add_executable(Golomb_Rice main.cpp BitStream.h BitStream.cpp GolombDecoder.h GolombEncoder.h ReadAndWriteFile.h)