#ifndef NEW_MORPH_HANDLER_H
#define NEW_MORPH_HANDLER_H

class NewMorphHandler: public EventHandler{
 public:
  NewMorphHandler(ControladorEventos* cont_eventos);
  ~NewMorphHandler();
  void operator()();
 private:
  void run();
};
#endif