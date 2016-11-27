# Self-Interpreter
Trabajo practico final de la materia Taller de Programacion - 75.42 - FIUBA

##Integrantes
* [Alfaro Miguel](https://github.com/AlfaroMiguel)
* [Gonzalez Cristian](https://github.com/Cristian3629)
* [Mendez Agustina](https://github.com/abmendez)

##Pre-Build
* Cmake >= 2.8.4
* G++ >= 5.4.0
* Bison = 3.0.4  
* Flex = 2.5.35
* gtkmm-3.0
* goocanvasmm-2.0

##Build
* En src/server/parser
 `./generar.sh`
* En la carpeta raiz del proyecto:
 `cmake ./src`
* Finalmente copiar:
 `src/client/ventana_vm.glade` a `client`
* Por ultimo en la carpeta raiz del proyecto:
 `make`
* Se generan dos carpetas con los respectivos ejecutables 
 `client` y `server`
 
 UPDATE: solo ejecutar install.sh

##Run 

* Server `./server port`
* Client `./client host port`

##Documentacion adicional
* Manual de proyecto: https://www.overleaf.com/7097737cbmvrznwvpqb
* Documentacion tecnica: https://www.overleaf.com/7097755ztvkcsjjjxgv
* Manual del usuario: https://www.overleaf.com/7090924zfjbtsqfghrk#/24374756/


##TODO List (23/09) En orden de importancia

- [ ] Pasar por referencia (no por copia!) usar const cuando lo amerite :soon:
- [x] Serializacion/Persistencia (TESTING) :microscope:
- [ ] Cambios en la interfaz de Glade (Agregar cosas que se charlaron en clase) (EN PROCESO) :recycle:
- [x] Mensajes con contexto en los objetos (TESTING) :microscope:
- [x] Actualizacion de Slots (incluso cuando se hace DO)
- [ ] Notificar morphs (_AddSlot + Get =  mostrar valor de slot) (_AddSlot + Do = Actualiza el morph [si se encuentra visualizado]) (EN PROCESO) :recycle:
- [ ] Cambiar de Lobby dentro de la app :soon:
- [ ] Agregar linea en la interfaz uniendo Morph con el Morph de su Slot. (PROBLEMA CON IMPLEMENTACION) :no_entry_sign:
- [x] Interfaz en un solo idioma (Ingles)
- [ ] Seleccionar slot -> Cambia de color el borde
- [x] Fixear los anchos de los slots al ancho del Morph que lo contiene
- [x] Borde del nombre del Morph mas grueso
- [x] Borde de los slots mas fino
- [ ] Nombre de Morph en negrita (PROBLEMA CON IMPLEMENTACION) :no_entry_sign:
- [ ] No repetir Morphs que ya estan visualizados 
- [ ] Parser: resolver multiples parametros
- [ ] Documentacion mas ordenada -> en los .h :soon:
- [ ] Valgrind Servidor
