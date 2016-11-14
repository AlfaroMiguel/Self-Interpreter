#!/bin/bash
`flex --header-file=scanner.h scanner.l`
`bison -d  --debug -g -v parser.y`

echo `g++ -Wall -std=c++11 -ggdb -o parser  -Wno-write-strings *.c *.cpp ../object.cpp ../number.cpp ../expression.cpp ../registrodeslots.cpp ../searcher_object.cpp ../nativevalue.cpp ../slot.cpp ../main.cpp`

echo 'Parser generado'