#include "parser/interpreter.h"



int main(int argc, char const *argv[]) {
  Interpreter interpreter;
  //interpreter.interpretFile(argv[1]);
  char pajaro[] = "lobby _AddSlots: (| pajaro = (| x = 1. y = 3. algunMetodo = (|  | 3 * 2. ). |).  |). \n\0\0";
  interpreter.interpretChar(pajaro);
  char algunMetodo[] = "pajaro algunMetodo.\n\0\0";
  interpreter.interpretChar(algunMetodo);
  // char pajaro[] = "lobby _AddSlots: (| pajaro = (| x = 1. y = 3. algunMetodo = (|  | 3 * 2 + 1. ). |).  |). \n\0\0";
  // interpreter.interpretChar(pajaro);
  // char algunMetodo[] = "pajaro algunMetodo.\n\0\0";
  //interpreter.interpretChar(algunMetodo);
  // char OtroObjeto[] = "lobby _AddSlots: (| OtroObjeto = (|x = 1. y <- 3. metodo = (|  | 4 + 2 + 1. ).|).|).";
  // char objeto[] = "lobby _AddSlots: (| objeto = (| x = 1. y = 3. numero = (|  | 3 * 3.).|). |).";
  // char numero[] = "objeto numero.";
  // char metodo[] = "OtroObjeto metodo.";
  // interpreter.interpretChar(OtroObjeto);
  // interpreter.interpretChar(objeto);
  // interpreter.interpretChar(numero);
  // interpreter.interpretChar(metodo);
  return 0;
}
