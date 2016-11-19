#include "morph.h"
#include "modelo.h"
#include "client_handler.h"
#include <vector>
#include <map>

#define ALTO 23
#define ANCHO 200

bool Morph::on_create(Glib::RefPtr<Objeto>){
	add_child(objeto);
	return false;
}

Morph::Morph(const Posicion& pos, const Glib::ustring& nombre, int id): id(id) {
	objeto = Objeto::create(pos, nombre);
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Morph::on_create), objeto));
}

Morph::~Morph(){}

Morph::Morph(Morph&& otra): dragging(otra.dragging), drag_x(otra.drag_x), drag_y(otra.drag_y),
							siendo_editado(otra.siendo_editado), objeto(otra.objeto),
							id(otra.id){}

Morph& Morph::operator=(Morph&& otra){
	dragging = otra.dragging;
	drag_x = otra.drag_x;
	drag_y = otra.drag_y;
	siendo_editado = otra.siendo_editado;
	objeto = otra.objeto;
	id = otra.id;
	return *this;
}

Glib::RefPtr<Morph> Morph::create(const Posicion& pos, const Glib::ustring& nombre, int id){
	return Glib::RefPtr<Morph>(new Morph(pos, nombre, id));
}

double Morph::get_x() const {
	return objeto->get_x();
}

double Morph::get_y() const {
	return objeto->get_y();
}

int Morph::get_id() const{
	return id;
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

bool Morph::esta_en_posicion(const Posicion& pos) const {
	return objeto->esta_en_posicion(pos);
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

const std::string Morph::obtener_valor_slot(const Posicion& pos) const{
	return (objeto->obtener_valor_slot(pos)).raw();
}

const std::string Morph::obtener_nombre_slot(const Posicion& pos) const{
	return (objeto->obtener_nombre_slot(pos)).raw();
}


bool Morph::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) {
	if(item && dragging && item == dragging) {
		Posicion new_pos(event->x - drag_x, event->y - drag_y);
 		client_handler->mover_morph(get_id(), new_pos);
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

const std::string Morph::get_nombre() const{
	return objeto->get_nombre();
}

void Morph::mover(const Posicion& new_pos){
	objeto->mover(new_pos);
	client_handler->actualizar_posicion(get_id(), get_posicion());
	//if (linea) linea->translate(x, y);
}

const Posicion& Morph::get_posicion() const{
	return objeto->get_posicion();
}

void Morph::set_control(ClientHandler *client_handler) {
	this->client_handler = client_handler;
}

bool Morph::es_objeto(const Posicion& pos) const{
	return objeto->objeto_en_posicion(pos);
}

bool Morph::es_slot(const Posicion& pos) const{
	return objeto->slot_en_posicion(pos);
}

void Morph::cambiar_posicion(Posicion* pos){
	objeto->cambiar_posicion(pos);
}