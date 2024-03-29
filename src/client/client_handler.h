#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "morph.h"
#include "server_proxy.h"
#include "posicion.h"
#include "union.h"
#include <string>
#include <map>
#include <gtkmm.h>

class ViewHandler;
class Model;

/* Clase que se encarga de manejar las interacciones entre el servidor
 * y las distintas clases del cliente */
class ClientHandler {
 public:
  ClientHandler(Model *model, ServerProxy *server_proxy);
  ~ClientHandler();

  /* Establece el controlador con el que se va a comunicar la clase */
  void set_handler(ViewHandler *view_handler);
  /* Agrega un lobby a los lobbies en los que puede
   * participar el cliente */
  void add_lobby(const std::string &lobby_id) const;
  /* Establece los lobbies que se mostraran al
   * usuario para que elija cual usar */
  void set_lobbies() const;
  /* Muestra el lobby seleccionado por el cliente */
  void open_lobby();
  /* Mueve el morph a la posicion indicada */
  void move_morph(int morph_id, const Posicion &new_pos);
  /* Actualiza la posicion del morph */
  void update_morph_position(int morph_id, const Posicion &pos);
  /* Habilita la edicion del morph recibido */
  void enable_editing(Glib::RefPtr <Morph> morph);
  /* Crea un morph nuevo */
  void create_morph(const std::string &name, const Posicion &pos,
					std::map<std::string, std::string> slots, int id,
					int id_padre, const std::string &slot_name);
  /* Dibuja el morph en la interfaz */
  void draw_morph(Glib::RefPtr <Morph> morph);
  /* Elimina el morph seleccionado de la interfaz */
  void dismiss_morph();
  /* Elimina el morph recibido de la interfaz */
  void dismiss_morph(Glib::RefPtr <Morph> morph);
  /* Elimina el morph representado por el id recibido de la interfaz */
  void dismiss_morph(int morph_id);
  /* Maneja los clicks en la interfaz */
  bool button_event(GdkEventButton *event);
  /* Cambia el nombre del morph seleccionado */
  void change_morph_name(const std::string &new_name);
  /* Envia el codigo al servidor con el evento get o do, indicando el morph
   * al que se le pidio el mensaje */
  void send_code(const std::string &code, const std::string &event);
  /* Informa al servidor el nombre del cliente que se intenta conectar */
  void connect_client(const std::string &client_name);
  /* Cambia la posicion del morph cuyo id se recibe */
  void change_morph_position(int morph_id, const Posicion &new_pos);
  /* Informa a la interfaz que no se pudo conectar un cliente */
  void client_connection_error();
  /* Informa que se pudo conectar un cliente */
  void connected_client();
  /* Obtiene un morph a partir del slot perteneciente al morph indicado */
  void get_morph_from_slot(int morph_id, const std::string &slot_name);
  /* Pide los datos del lobby seleccionado al servidor */
  void select_lobby(const std::string &lobby_name,
                    const std::string &lobby_property);
  /* Elimina el morph de la vista */
  void hide_morph(Glib::RefPtr <Morph> morph);
  /* Cierra la aplicacion */
  void quit();
  /* Muestra al usuario las opciones para elegir un nuevo lobby */
  void show_lobby_options();
  /* Elimina todos los morphs existentes en el lobby activo */
  void reset_lobby();
  /* Agrega la union a la interfaz */
  void add_union(Union *morph_union);
  /* Agrega la union entre el morph representado por id_obj y el slot de
   * nombre slot_name presente en el morph id_morph */
  void add_union(int id_obj, int id_morph, const std::string &slot_name);
  /* Elimina la union de la interfaz */
  void delete_union(Union *morph_union);
 private:
  Model *model;
  ServerProxy *server_proxy;
  ViewHandler *view_handler;
};
#endif