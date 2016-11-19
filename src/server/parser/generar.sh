#!/bin/bash
`flex --header-file=scanner.h --outfile=scanner.cpp scanner.l`
`bison -d  --debug -g -v --defines=parser.h --output=parser.cpp parser.y`

echo 'Archivos de parser generados'
