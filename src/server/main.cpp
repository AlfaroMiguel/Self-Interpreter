#include <iostream>

#include "number.h"
#include "lobby.h"
#include "bool.h"
#include "string.h"

int main() {
    /*La idea es que el interprete haga esto cuando el parser se lo indica
      Por ejemplo si se tiene ((12 print)+(10 print))print
     */
    Lobby* lobby = new Lobby();
    lobby->setNombre("LobbyPrincipal");

    Number* numero = new Number;
    numero->setNombre("numero");
    numero->setValor(12);

    Number* numero2 = new Number;
    numero->setNombre("numero2");
    numero2->setValor(10);

    lobby->AddSlots("numero", numero, true, false);
    lobby->AddSlots("numero2", numero2, true, false);

    std::vector<Object*> argsVacio;
    std::vector<Object*> args;
    args.push_back(numero2);
    lobby->recvMessage("numero", "print", argsVacio);
    lobby->recvMessage("numero2", "print", argsVacio);
    lobby->recvMessage("numero", "+", args);
    lobby->recvMessage("numero", "print", argsVacio);

    /*Pruebo un 'hola' print*/
    String* cadena = new String();
    cadena->setNombre("cadena");
    cadena->setValor("hola");
    lobby->AddSlots("cadena", cadena, false, false);
    lobby->recvMessage("cadena", "print", argsVacio);

    /*Esto lo deberia de hacer la clase interprete, este seria como el assambly
     * de como crear un objeto y como enviar un mensaje
     * Lo unico que falta es conectar con el parser cuando un mensaje no es reconocido
     * es porque el codigo de ese mensaje se encuentra como codigo asociado en un objeto
     * en formato std::string.
     *
     * Esta string se la tiene que pasar al Parser para que el diga que significa*/
    return 0;
}