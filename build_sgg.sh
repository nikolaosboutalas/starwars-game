#!/bin/bash

CC=g++
LD=g++
AR=ar
BUILD_PATH="build"
LIB_PATH="lib"
CFLAGS="-O2"

mkdir -p $LIB_PATH
mkdir -p $BUILD_PATH
mkdir -p $BUILD_PATH/sgg

$CC -c $CFLAGS -I3rdparty/include graphics/graphics.cpp -o $BUILD_PATH/sgg/graphics.o
$CC -c $CFLAGS -I3rdparty/include graphics/GLbackend.cpp -o $BUILD_PATH/sgg/GLbackend.o
$CC -c $CFLAGS -I3rdparty/include graphics/shader.cpp -o $BUILD_PATH/sgg/shader.o
$CC -c $CFLAGS -I3rdparty/include graphics/texture.cpp -o $BUILD_PATH/sgg/texture.o
$CC -c $CFLAGS -I3rdparty/include graphics/audio.cpp -o $BUILD_PATH/sgg/audio.o
$CC -c $CFLAGS -I3rdparty/include graphics/AudioManager.cpp -o $BUILD_PATH/sgg/AudioManager.o
$CC -c $CFLAGS -I3rdparty/include graphics/lodepng.cpp -o $BUILD_PATH/sgg/lodepng.o
$CC -c $CFLAGS -I3rdparty/include graphics/fonts.cpp -o $BUILD_PATH/sgg/fonts.o

$AR rcs $LIB_PATH/libsgg.a $BUILD_PATH/sgg/*.o
