#ifndef MORPH_H
#define MORPH_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>

#include "morph_object.h"
#include "slot.h"

class Model;
class ClientHandler;

/* Clase que representa a la representacion de los MorphObjects y sus slots */
class Morph : public Goocanvas::Group {
 public:
  static Glib::RefPtr <Morph> create(const Posicion &pos,
									 const Glib::ustring &nombre, int id);
  Morph(const Posicion &pos, const Glib::ustring &nombre, int id);
  ~Morph();

  Morph(Morph &&otra);
  Morph &operator=(Morph &&otra);

  /* Establece el controlador con el que se va a comunicar la clase */
  void set_handler(ClientHandler *client_handler);
  /* Conecta en el morph las señales necesarias para manejar las
   * acciones sobre la interfaz */
  void connect_signals();
  /* Elimina al morph de la interfaz */
  void dismiss();
  /* Devuelve true si el morph se encuentra en la posicion dada */
  bool is_in_position(const Posicion &pos) const;
  /* Cambia el nombre del morph por el recibido */
  void edit_name(const std::string &new_name);
  /* Agrega los slots recibidos */
  void add_slots(std::map <std::string, std::string> added_slots);
  /* Devuelve la posicion x del morph*/
  double get_x() const;
  /* Devuelve la posicion y del morph*/
  double get_y() const;
  /* Devuelve el id del morph */
  int get_id() const;
  /* Devuelve el nombre del morph */
  const std::string get_name() const;
  /* Devuelve el valor del slot que se encuentra en la posicion dada */
  const std::string get_slot_value(const Posicion &slot_pos) const;
  /* Devuelve el nombre del slot que se encuentra en la posicion dada */
  const std::string get_slot_name(const Posicion &slot_pos) const;
  /* Mueve el morph a la posicion dada */
  void move(const Posicion &new_pos);
  /* Devuelve true si en la posicion dada se encuentra el MorphObject del morph */
  bool is_object(const Posicion &pos) const;
  /* Devuelve true si en la posicion dada se encuentra algun slot del morph*/
  bool is_slot(const Posicion &pos) const;
  /* Cambia la posicion del morph por la posicion recibida */
  void change_position(const Posicion &new_pos);
  /* Devuelve la posicion del morph*/
  const Posicion &get_position() const;
  /* Devuelve true si el id del morph coincide con el id recibido */
  bool has_id(int id);
  /* Redimensiona el morph al tamanio nuevo*/
  void resize(double new_size);
  /* Agrega un camino del MorphObject al slot identificado con slot_name del morph
   * identificado con parent_id */
  void add_path_to_object(int parent_id, const std::string &slot_name);
  /* Agrega un camino desde el slot identificado con slot_name al MorphObject del
   * morph identificado por parent_id */
  void add_path_to_slot(const std::string &slot_name, int parent_id);
  /* Devuelve la posicion en la que se encuentra el slot identificado por
   * el nombre dado */
  const Posicion &get_slot_position(const std::string &slot_name) const;
  /* Agrega una union desde el morph identificado con id_obj al slot
   * identificado con slot_name del morph identificado con parent_id*/
  void add_union(int id_obj, int parent_id, const std::string &slot_name);
  /* Devuelve true si esta unido al slot identificado por slot_name
   * del morph representado por parent_id */
  bool shares_parent(int parent_id, const std::string &slot_name);
 private:
  Glib::RefPtr <Goocanvas::Item> dragging;
  int drag_x, drag_y;
  Glib::RefPtr <MorphObject> object;
  int id;
  ClientHandler *client_handler;

  /* Maneja el evento en el que se presiona sobre el morph */
  bool on_item_button_press_event(const Glib::RefPtr <Goocanvas::Item> &item,
								  GdkEventButton *event);
  /* Maneja el evento en el que se deja de presionar sobre el morph */
  bool on_item_button_release_event(const Glib::RefPtr <Goocanvas::Item> &item,
									GdkEventButton *event);
  /* Maneja el evento en el que se mueve el morph */
  bool on_item_motion_notify_event(const Glib::RefPtr <Goocanvas::Item> &item,
								   GdkEventMotion *event);

  Morph(const Morph &otra) = delete;
  Morph &operator=(const Morph &otra) = delete;

  /* Realiza el metodo create() en el hilo principal */
  bool do_create(Glib::RefPtr <MorphObject>);
  /* Realiza el metodo dismiss() en el hilo principal */
  bool do_dismiss();
};
#endif
