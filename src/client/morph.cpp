#include "morph.h"
#include <vector>
#include <map>

#define ALTO 23
#define ANCHO 200

Morph::Morph(double x, double y, Glib::ustring& nombre) {
	//TODO: creo que se deberia poder redimensionar
	objeto = Objeto::create(x, y, nombre);
//	Glib::RefPtr<Goocanvas::Rect> rectangulo = Goocanvas::Rect::create(x, y, 100, 100);
//	rectangulo->property_fill_color().set_value("white");
//	add_child(rectangulo);
	//add_child(objeto);
//	base_titulo = Goocanvas::Rect::create(x, y, ANCHO, ALTO);
//	base_titulo->property_fill_color().set_value("white");
//	titulo = Goocanvas::Text::create(nombre, x+2, y+2);
//	titulo->property_fill_color().set_value("black");
//	items.push_back(base_titulo);
//	items.push_back(titulo);
}

Morph::~Morph(){}

Glib::RefPtr<Morph> Morph::create(double x, double y, Glib::ustring& nombre){
	return Glib::RefPtr<Morph>(new Morph(x, y, nombre));
}

void Morph::eliminar(){
	objeto->remove();
//	base_titulo->remove();
//	titulo->remove();
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

void Morph::agregar_slots(std::map<Glib::ustring, Glib::ustring> slots_a_agregar){
	objeto->agregar_slots(slots_a_agregar);
}

//void Morph::agregar_slot(const Glib::ustring& nombre, Glib::RefPtr<Goocanvas::Item>& item){
//	//TODO: arreglar diferencias entre clickear en los slots y clickear en el objeto base
//	if (nombre.empty()) return;
//	int offset = ALTO*(slots.size()+1);
//	Glib::RefPtr<Morph> slot = create(pos_x, pos_y+offset, nombre);
//	slots.push_back(slot);
//	slot->conectar_seniales(item);
//	add_child(slot);
//}

bool Morph::esta_en_posicion(double x, double y /* Goocanvas::Canvas* canvas */) {
	//Glib::RefPtr<Goocanvas::Item> item_en_pos = canvas->get_item_at(x, y, true);
	return objeto->esta_en_posicion(x, y);
}

void Morph::mover_elementos(double new_x, double new_y){
	objeto->mover(new_x - drag_x, new_y - drag_y);
	//titulo->translate(new_x - drag_x, new_y - drag_y);
}

bool Morph::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) {
	if(item && dragging && item == dragging) {
		auto new_x = event->x;
		auto new_y = event->y;
		mover_elementos(new_x, new_y);
//		pos_x += (new_x-drag_x);
//		pos_y += (new_y-drag_y);
	}
	return false;
}

void Morph::agregar_elementos(){
	add_child(objeto);
}

void Morph::conectar_seniales(){
	signal_button_press_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_press_event));
	signal_button_release_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_release_event));
	signal_motion_notify_event().connect(sigc::mem_fun(*this, &Morph::on_item_motion_notify_event));
	agregar_elementos();
}

void Morph::editando(bool valor) {
	siendo_editado = valor;
}

bool Morph::editando(){
	return siendo_editado;
}

void Morph::editar_nombre(Glib::ustring nombre_nuevo) {
	objeto->editar_nombre(nombre_nuevo);
}