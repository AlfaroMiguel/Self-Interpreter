#!/bin/bash
cd src/server/parser

echo '#######################################################'
echo 'GENERANDO PARSER SELF'
echo '#######################################################'
./generar.sh
echo '#######################################################'
echo 'PARSER GENERADO CORRECTAMENTE'
echo '#######################################################'
cd ../../..
cmake ./src
cp src/client/ventana_vm.glade client/ventana_vm.glade
echo 'INSTALANDO SELF INTERPRETER'
make
echo '#######################################################'
echo 'SELF INTERPRETER INSTALADO CORRECTAMENTE'
echo '#######################################################'
echo 'INICIAR SERVER: en "/server" ejecutar "./server port"'
echo '#######################################################'
echo 'INICIAR CLIENTE: en "/client" ejecutar "./client host port"'
echo '#######################################################'
echo 'ULTIMA VERSION DISPONIBLE EN: https://github.com/AlfaroMiguel/Self-Interpreter'
echo '#######################################################'
echo 'REALIZADO POR: Alfaro Miguel - Gonzalez Cristian - Mendez Agustina'