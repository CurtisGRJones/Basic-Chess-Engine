#! /bin/bash

if [ ! -d "dest" ]
then
    mkdir dest;
fi


# TODO find better way to compile everything
g++ -o dest/engine.o \
       src/engine/main.cpp \
       src/shared/position/position.cpp