#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>
#include "morph.h"
#include "view_handler.h"
#include "client_handler.h"
#include "ventana_cliente.h"

class VentanaEdicion;
class VentanaObjetos;
class VentanaInicio;

/* Clase que representa a la ventana principal de programa. */
class MainView : public Gtk::Window {
 public:
  MainView(BaseObjectType *cobject,
           const Glib::RefPtr <Gtk::Builder> &builder);
  virtual ~MainView();

  MainView(MainView &&otra);
  MainView &operator=(MainView &&otra);

  /* Cierra la ventana */
  void quit();
  /* Establece el manejador del cliente en el controlador de la vista*/
  void set_handler(ClientHandler *client_handler);
 private:
  VentanaEdicion *editing_view;
  VentanaObjetos *objects_view;
  VentanaInicio *lobbies_view;
  VentanaCliente *client_view;
  ViewHandler *view_handler;

  Glib::RefPtr <Gtk::Builder> builder;

  /* Realiza la funcion quit() en el hilo principal */
  bool do_quit();
};
#endif
