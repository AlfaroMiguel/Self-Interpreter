#!/bin/bash
`flex scanner.l`
`bison -d  --debug -g -v parser.y`

echo `g++ -std=c++11 -o parser  -Wno-write-strings *.c *.h ../*cpp ../*h`
echo 'Parse init'
./parser  __stdin__
