#!/bin/bash
`flex scanner.l`
`bison -d  --debug -g -tx parser.y`

g++ -std=c++11 -o parser  -Wno-write-strings interpreter.cpp lex.yy.c parser.tab.c
echo 'Parse init'
./parser  __stdin__
