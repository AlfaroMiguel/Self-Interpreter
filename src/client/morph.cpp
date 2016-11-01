#include "morph.h"
#include <vector>
#include <map>

#define ALTO 23
#define ANCHO 200

Morph::Morph(double x, double y, const Glib::ustring& nombre) {
	//TODO: creo que se deberia poder redimensionar
	objeto = Objeto::create(x, y, nombre);
	add_child(objeto);
}

Morph::~Morph(){}

Morph::Morph(Morph&& otra): dragging(otra.dragging), drag_x(otra.drag_x), drag_y(otra.drag_y),
							siendo_editado(otra.siendo_editado), objeto(otra.objeto){}

Morph& Morph::operator=(Morph&& otra){
	dragging = otra.dragging;
	drag_x = otra.drag_x;
	drag_y = otra.drag_y;
	siendo_editado = otra.siendo_editado;
	objeto = otra.objeto;
	return *this;
}

Glib::RefPtr<Morph> Morph::create(double x, double y, const Glib::ustring& nombre){
	return Glib::RefPtr<Morph>(new Morph(x, y, nombre));
}

void Morph::eliminar(){
	objeto->remove();
	remove();
}

void Morph::agregar_slots(std::map<std::string, std::string> slots_a_agregar){
	objeto->agregar_slots(slots_a_agregar);
}

bool Morph::esta_en_posicion(double x, double y) {
	return objeto->esta_en_posicion(x, y);
}

void Morph::conectar_seniales(){
	signal_button_press_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_press_event));
	signal_button_release_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_release_event));
	signal_motion_notify_event().connect(sigc::mem_fun(*this, &Morph::on_item_motion_notify_event));
}

void Morph::editando(bool valor) {
	siendo_editado = valor;
}

bool Morph::editando(){
	return siendo_editado;
}

void Morph::editar_nombre(const std::string& nombre_nuevo) {
	Glib::ustring nombre(nombre_nuevo);
	objeto->editar_nombre(nombre);
}

bool Morph::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) {
	if(item && dragging && item == dragging) {
		auto new_x = event->x;
		auto new_y = event->y;
		objeto->mover(new_x - drag_x, new_y - drag_y);
	}
	return false;
}

bool Morph::on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event) {
	if(event->button == 1) {
		dragging = item;
		drag_x = (int) event->x;
		drag_y = (int) event->y;
	}
	return false;
}

bool Morph::on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>&  item , GdkEventButton* event) {
	if(event->button == 1)
		dragging.reset();
	return false;
}