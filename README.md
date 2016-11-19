# Self-Interpreter
Trabajo practico final de la materia Taller de Programacion - 75.42 - FIUBA

##Integrantes
* [Alfaro Miguel](https://github.com/AlfaroMiguel)
* [Gonzalez Cristian](https://github.com/Cristian3629)
* [Mendez Agustina](https://github.com/abmendez)

##Pre-Build
Cmake >= 2.8.4
G++ >= 5.4.0
Bison = 3.0.4  
Flex = 2.5.35
gtkmm-3.0
goocanvasmm-2.0

##Build
En src/server/parser
* `./generar.sh`
En la carpeta raiz del proyecto:
* `cmake ./src`
Finalmente copiar de:
* `src/client/ventana_vm.glade` a `client`
Por ultimo en la carpeta raiz del proyecto:
* `make`
Se generan dos carpetas con los respectivos ejecutables 
* `client` y `server`

#Run 

Server `./server port`
Client `./client host port`

##Documentacion adicional
* Manual del usuario: https://www.overleaf.com/7090924zfjbtsqfghrk#/24374756/
* Manual de proyecto: https://www.overleaf.com/7097737cbmvrznwvpqb
* Documentacion tecnica: https://www.overleaf.com/7097755ztvkcsjjjxgv
