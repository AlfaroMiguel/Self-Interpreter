#ifndef UNION_H
#define UNION_H

#include <goocanvasmm.h>
#include <gtkmm.h>
#include "posicion.h"

#include <string>

class ClientHandler;

class Union{
 public:
  Union(int id, int id_padre, const std::string& slot_name, ClientHandler* client_handler);
  ~Union();

  void add_path(const Posicion& pos_begin, const Posicion& pos_end);
  void update_path(const Posicion& pos_begin, const Posicion& pos_end);
  bool operator==(const Union& other) const;
  Glib::RefPtr<Goocanvas::Path> get_path() const;
  bool is_equal(const Union& other);
 private:
  int id;
  int id_padre;
  const std::string slot_name;
  ClientHandler* client_handler;
  Glib::RefPtr<Goocanvas::Path> path;

  bool on_add_path(const std::string& path_data);
};
#endif