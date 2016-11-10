#include "parser/interpreter.h"



int main(int argc, char const *argv[]) {
  Interpreter interpreter;
  char* buffer = "lobby _AddSlots: (| objeto = (| x = 1. y = 3. metodo = (|  | 3 * 2 + 1. ). |).  |).";
  interpreter.interpret(buffer);
  char* otro = "objeto metodo.";
  interpreter.interpret(otro);
  return 0;
}
