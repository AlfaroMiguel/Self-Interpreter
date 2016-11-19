#!/bin/bash
cd src/server/parser
./generar.sh
echo 'Parser generado'
cd ../../..
cmake ./src
cp src/client/ventana_vm.glade client/ventana_vm.glade
make
echo 'Interprete Self instalado'
