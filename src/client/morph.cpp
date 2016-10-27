#include "morph.h"
#include <vector>

#define ALTO 23
#define ANCHO 200
Morph::Morph(double x, double y, const Glib::ustring& nombre): pos_x(x), pos_y(y){
	//TODO: creo que se deberia poder redimensionar
	base_titulo = Goocanvas::Rect::create(x, y, ANCHO, ALTO);
	base_titulo->property_fill_color().set_value("white");
	titulo = Goocanvas::Text::create(nombre, x+2, y+2);
	titulo->property_fill_color().set_value("black");
	items.push_back(base_titulo);
	items.push_back(titulo);
}

Morph::~Morph(){}

Glib::RefPtr<Morph> Morph::create(double x, double y, const Glib::ustring& nombre){
	return Glib::RefPtr<Morph>(new Morph(x, y, nombre));
}

void Morph::eliminar(){
	base_titulo->remove();
	titulo->remove();
	remove();
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

void Morph::agregar_slot(const Glib::ustring nombre, Glib::RefPtr<Goocanvas::Item>& item){
	//TODO: arreglar diferencias entre clickear en los slots y clickear en el objeto base
	if (nombre.empty()) return;
	int offset = ALTO*(slots.size()+1);
	Glib::RefPtr<Morph> slot = create(pos_x, pos_y+offset, nombre);
	slots.push_back(slot);
	slot->conectar_seniales(item);
	add_child(slot);
}

bool Morph::esta_en_posicion(double x, double y, Goocanvas::Canvas* canvas) {
	Glib::RefPtr<Goocanvas::Item> item_en_pos = canvas->get_item_at(x, y, true);
	for(unsigned int i = 0; i < items.size(); i++){
		if (item_en_pos == items[i])
			return true;
	}
	return false;
}

void Morph::mover_elementos(double new_x, double new_y){
	base_titulo->translate(new_x - drag_x, new_y - drag_y);
	titulo->translate(new_x - drag_x, new_y - drag_y);
}

bool Morph::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) {
	if(item && dragging && item == dragging) {
		auto new_x = event->x;
		auto new_y = event->y;
		mover_elementos(new_x, new_y);
		pos_x += (new_x-drag_x);
		pos_y += (new_y-drag_y);
	}
	return false;
}

void Morph::agregar_elementos(Glib::RefPtr<Goocanvas::Item>& item){
	item->add_child(base_titulo);
	item->add_child(titulo);
}

void Morph::conectar_seniales(Glib::RefPtr<Goocanvas::Item>& item){
	item->signal_button_press_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_press_event));
	item->signal_button_release_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_release_event));
	item->signal_motion_notify_event().connect(sigc::mem_fun(*this, &Morph::on_item_motion_notify_event));
	agregar_elementos(item);
}

void Morph::editando(bool valor) {
	siendo_editado = valor;
}

bool Morph::editando(){
	return siendo_editado;
}

void Morph::editar_nombre(const Glib::ustring nombre_nuevo) {
	if (nombre_nuevo.empty()) return;
	titulo->property_text() = nombre_nuevo;
}