#include "morph.h"
#include "modelo.h"
#include "cont_eventos.h"
#include <vector>
#include <map>

#define ALTO 23
#define ANCHO 200

Morph::Morph(double x, double y, const Glib::ustring& nombre) {
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

double Morph::get_x() {
	return objeto->get_x();
}

double Morph::get_y() {
	return objeto->get_y();
}

void Morph::agregar_union(Glib::RefPtr<Goocanvas::Polyline> linea){
	add_child(linea);
}

bool Morph::do_eliminar(){
	objeto->remove();
	remove();
	return false;
}

void Morph::eliminar() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &Morph::do_eliminar));
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

const std::string Morph::obtener_valor_slot(double x, double y){
	return (objeto->obtener_valor_slot(x, y)).raw();
}

const std::string Morph::obtener_nombre_slot(double x, double y){
	return (objeto->obtener_nombre_slot(x, y)).raw();
}


bool Morph::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) {
	if(item && dragging && item == dragging) {
		auto new_x = event->x;
		auto new_y = event->y;
		std::cout << "New pos: " << new_x << ", " << new_y << std::endl;
		std::cout << "Drag pos: " << drag_x << ", " << drag_y << std::endl;
 		cont_eventos->mover_morph(get_nombre(), new_x - drag_x , new_y - drag_y);
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

const std::string Morph::get_nombre(){
	return objeto->get_nombre();
}

void Morph::mover(double x, double y){
	objeto->mover(x, y);
	cont_eventos->actualizar_posicion(get_nombre(), get_x(), get_y());
	if (linea) linea->translate(x, y);
}

void Morph::set_control(ControladorEventos *cont_eventos) {
	this->cont_eventos = cont_eventos;
}

bool Morph::es_objeto(double x, double y) {
	return objeto->objeto_en_posicion(x, y);
}

bool Morph::es_slot(double x, double y) {
	return objeto->slot_en_posicion(x, y);
}
