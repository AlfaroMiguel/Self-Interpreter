#ifndef Model_H
#define Model_H

#include "client_handler.h"
#include <gtkmm.h>
#include "union.h"
class Morph;

class Model {
 public:
  Model();
  ~Model();

  Model(Model &&otra);
  Model &operator=(Model &&otra);

  /* Establece el controlador con el que se comunica la clase*/
  void set_handler(ClientHandler *client_handler);
  /* Crea un nuevo morph */
  void create_morph(const std::string &name, const Posicion &pos,
					std::map<std::string, std::string> slots, int id,
					int parent_id, const std::string &slot_name);
  /* Elimina el morph editado de la vista */
  void dismiss_morph();
  /* Elimina el morph representado por el id recibido de la interfaz */
  void dismiss_morph(int id);
  /* Cambia el nombre del morph seleccionado */
  void change_morph_name(const std::string &new_name);
  /* Habilita la edicion del morph seleccionado */
  void enable_editing() const; //ex editar_morph;
  /* Obtiene un morph a partir del slot en la posicion indicada */
  void get_morph_from_slot(Posicion &slot_pos);
  /* Mueve el morph a la posicion indicada */
  void move_morph(int morph_id, const Posicion &new_pos);
  /* Devuelve true si la parte del morph que se encuentra
   * en la posicion dada es la del objeto */
  bool is_object(const Posicion &pos) const;
  /* Devuelve true si la parte del morph que se encuentra
   * en la posicion dada es la de un slot*/
  bool is_slot(const Posicion &pos) const;
  /* Selecciona el morph que se encuentra en la posicion dada */
  void select_morph(const Posicion &morph_pos);
  /* Devuelve true si el id dado corresponde a un morph existente */
  bool existing_morph(int morph_id);
  /* Cambia la posicion del morph cuyo id se recibe */
  void change_morph_position(int morph_id, const Posicion &new_pos);
  /* Devuelve el morph seleccionado */
  Glib::RefPtr <Morph> get_selected_morph() const;
  /* Elimina todos los morphs existentes en el lobby activo */
  void reset_lobby();
  /* Agrega la union entre el morph representado por id_obj y el slot de
   * nombre slot_name presente en el morph id_morph */
  void add_union(int id_obj, int parent_id, const std::string &slot_name);
 private:
  Model(const Model &otra) = delete;
  Model &operator=(const Model &otra) = delete;
  ClientHandler *client_handler;

  std::vector<Glib::RefPtr < Morph>> morphs;
  std::vector<Union *> unions;
  Glib::RefPtr <Morph> selected_morph;
};
#endif
