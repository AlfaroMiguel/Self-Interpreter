#!/bin/bash
`flex --header-file=scanner.h scanner.l`
`bison -d  --debug -g -v parser.y`

echo 'Parser generado'