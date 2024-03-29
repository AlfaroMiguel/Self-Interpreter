# Self-Interpreter
Trabajo practico final de la materia Taller de Programacion - 75.42 - FIUBA

##Integrantes
* [Alfaro Miguel](https://github.com/AlfaroMiguel) :boy:
* [Gonzalez Cristian](https://github.com/Cristian3629) :boy:
* [Mendez Agustina](https://github.com/abmendez) :girl:

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
* Manual del usuario: https://www.overleaf.com/7090924zfjbtsqfghrk#/24374756/ <-- REVISAR, creo que ya esta terminado.


##TODO List (23/11) :arrow_right: (29/11) En orden de importancia

- [x] Pasar por referencia (no por copia!)
- [x] Serializacion/Persistencia
- [x] Cambios en la interfaz de Glade (Agregar cosas que se charlaron en clase)
- [x] Mensajes con contexto en los objetos
- [x] Actualizacion de Slots (incluso cuando se hace DO)
- [x] Notificar morphs (_AddSlot + Get =  mostrar valor de slot) (_AddSlot + Do = Actualiza el morph [si se encuentra visualizado])
- [x] Cambiar de Lobby dentro de la app (TESTING) :microscope:
- [x] Agregar linea en la interfaz uniendo Morph con el Morph de su Slot. (TESTING) :microscope: :relieved::relieved::relieved:
- [x] Interfaz en un solo idioma (Ingles)
- [ ] Seleccionar slot -> Cambia de color el borde :soon:
- [x] Fixear los anchos de los slots al ancho del Morph que lo contiene
- [x] Borde del nombre del Morph mas grueso
- [x] Borde de los slots mas fino
- [ ] Nombre de Morph en negrita :no_entry_sign:
- [x] No repetir Morphs que ya estan visualizados (TESTING) :microscope:
- [ ] Parser: resolver multiples parametros :no_entry_sign:
- [x] Documentacion mas ordenada -> en los .h (REALIZADO EN ALGUNAS CLASES) :heavy_exclamation_mark:
- [x] Valgrind Servidor (TESTING) :microscope:
- [x] Manejar excepciones correctamente (TESTING) :microscope:
- [x] Verificar errores de sintaxis en el codigo Self
- [ ] Codigo presentable SERVER: :white_check_mark: CLIENT: (EN PROCESO) :recycle:
- [x] Garbage collector con Serializacion
