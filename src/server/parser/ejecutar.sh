#!/bin/bash
`flex scanner.l`
`bison -d  --debug -g -tx parser.y`

echo `g++ -std=c++11 -o parser  -Wno-write-strings tokenizer.cpp tuple_string.cpp lex.yy.c parser.tab.c`
echo 'Parse init'
./parser  __stdin__
