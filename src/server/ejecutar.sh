#!/bin/bash
`bison++ -d -hparser.h -o parser.cpp parser.y`
`flex++ -d -oscanner.cpp scanner.l`

`g++ -c -Wno-write-strings parser.cpp`
`g++ -c scanner.cpp`
`g++ -c main.cpp`
g++ -o parser main.o parser.o scanner.o
echo 'Parse init'
./parser

