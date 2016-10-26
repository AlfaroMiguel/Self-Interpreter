#!/bin/bash
`bison -d --debug parser.y`
`flex scanner.l`

g++ -std=c++11 -o parser  -Wno-write-strings interpreter.cpp lex.yy.c parser.tab.c
echo 'Parse init'
./parser __stdin__
