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
	objeto = Objeto::create(pos, nombre, *this);
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

void Morph::resize(double new_size){
	objeto->resize_all(new_size);
}

int Morph::get_id() const{
	return id;
}

void Morph::agregar_union(Glib::RefPtr<Goocanvas::Polyline> linea){
	add_child(linea);
}

bool Morph::do_dismiss(){
	objeto->remove();
	remove();
	return false;
}

bool Morph::has_id(int id) {
	return id == this->id;
}

void Morph::dismiss() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &Morph::do_dismiss));
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
 		client_handler->move_morph(get_id(), new_pos);
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
	client_handler->update_morph_position(get_id(), get_posicion());
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

void Morph::cambiar_posicion(const Posicion& new_pos){
	objeto->cambiar_posicion(new_pos);
}

void Morph::add_path_to_object(int id_padre, const std::string& slot_name){
	objeto->add_path(id_padre, slot_name);
}

void Morph::add_path_to_slot(const std::string& slot_name, int id_padre){
	objeto->add_path_to_slot(slot_name, id_padre);
}

const Posicion& Morph::get_posicion_slot(const std::string &slot_name) {
	return objeto->get_posicion_slot(slot_name);
}

void Morph::add_union(int id, int id_padre, const std::string& slot_name){
	client_handler->add_union(id, id_padre, slot_name);
}