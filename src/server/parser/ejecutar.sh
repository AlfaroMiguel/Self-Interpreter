#!/bin/bash
`flex --header-file=scanner.h scanner.l`
`bison -d  --debug -g -v parser.y`

echo `g++ -Wall -std=c++11 -ggdb -o parser  -Wno-write-strings *.c  *.cpp ../*.cpp`
echo 'Parse init'
./parser  __stdin__
