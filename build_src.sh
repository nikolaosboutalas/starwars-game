#!/bin/bash

CC=g++
LD=g++
BIN_PATH="bin"
LIB_PATH="lib"
CFLAGS="-O2"

mkdir -p $BIN_PATH
mkdir -p $BIN_PATH/assets

$CC $CFLAGS -L$LIB_PATH -Igraphics src/*.cpp -o $BIN_PATH/main -lsgg -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype

cp -r assets $BIN_PATH
