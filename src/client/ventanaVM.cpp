#include "ventanaVM.h"
#include "canvas_objetos.h"
#include "morph.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <vector>

#define BTN_NUEVO_OBJ "Nuevo Objeto"
#define BTN_ELIMINAR_OBJ "Eliminar Objeto"
#define BTN_EDITAR_NOMBRE "Editar Nombre"
#define BTN_AGREGAR_SLOT "Agregar Slot"

VentanaVM::VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
							Gtk::Window(cobject), builder(builder) {
	maximize();
//TODO: que solo aparezca el menu en el canvas
	caja_base = nullptr;
	builder->get_widget("cajaBase", caja_base);
	canvas = Gtk::manage(new Goocanvas::Canvas());
	canvas->set_size_request(400,400);
	canvas->set_hexpand(true);
	caja_base->add(*canvas);
	add_events(Gdk::BUTTON_PRESS_MASK);
	crear_menu_objetos();
	root = Goocanvas::GroupModel::create();
	canvas->set_root_item_model(root);
	caja_editar = nullptr;
	builder->get_widget("cajaEditar", caja_editar);
	Gtk::Button* boton_aceptar_nombre = nullptr;
	builder->get_widget("btnAceptarNombre", boton_aceptar_nombre);
	boton_aceptar_nombre->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_aceptar_nombre_event));
	entrada_nombre = nullptr;
	builder->get_widget("entradaNombre", entrada_nombre);
	Gtk::Button* boton_aceptar_slot = nullptr;
	builder->get_widget("btnAceptarSlot", boton_aceptar_slot);
	boton_aceptar_slot->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_aceptar_slot_event));
	entrada_slot = nullptr;
	builder->get_widget("entradaSlot", entrada_slot);
	show_all_children();
	caja_editar->hide();
}

VentanaVM::~VentanaVM() {}

void VentanaVM::crear_menu_objetos(){
	objeto_nuevo.set_label(BTN_NUEVO_OBJ);
	eliminar_objeto.set_label(BTN_ELIMINAR_OBJ);
	editar_nombre.set_label(BTN_EDITAR_NOMBRE);
	agregar_slot.set_label(BTN_AGREGAR_SLOT);
	objeto_nuevo.signal_activate().connect(sigc::mem_fun(*this, &VentanaVM::on_obj_nuevo_event));
	eliminar_objeto.signal_activate().connect(sigc::mem_fun(*this, &VentanaVM::on_eliminar_obj_event));
	editar_nombre.signal_activate().connect(sigc::mem_fun(*this, &VentanaVM::on_editar_nombre_event));
	agregar_slot.signal_activate().connect(sigc::mem_fun(*this, &VentanaVM::on_agregar_slot_event));
	menu_obj.append(objeto_nuevo);
	menu_obj.append(eliminar_objeto);
	//TODO: las opciones que no son nuevo y eliminar se activan solo cuando hay objetos
	menu_obj.append(editar_nombre);
	menu_obj.append(agregar_slot);
	menu_obj.show_all();
}
void VentanaVM::dibujar_morph(double x, double y) {
	contador_morphs += 1;
	Glib::ustring nombre = "Objeto";
	nombre += Glib::ustring::format(contador_morphs);
	Glib::RefPtr<Morph> morph = Morph::create(x, y, nombre);
	morphs.push_back(morph);
	root->add_child(morph);
	auto item = canvas->get_item(morph);
	morph->conectar_seniales(item);
}

void VentanaVM::on_obj_nuevo_event() {
	dibujar_morph(x, y);
}

//TODO: pasar este for a una funcion aparte urgente
void VentanaVM::on_agregar_slot_event() {
	for(int i = 0; i < morphs.size(); i++)
		if (morphs[i]->esta_en_posicion(x, y, canvas))
			morphs[i]->editando(true);
	//TODO: que caja_editar sea atributo y pasar esto a una funcion de mostrar
	Gtk::Box* caja_editar = nullptr;
	builder->get_widget("cajaEditar", caja_editar);
	caja_editar->show_all();
	Gtk::Box* caja_editar_nombre = nullptr;
	Gtk::Label* lbl_editar_nombre = nullptr;
	builder->get_widget("boxEditarNombre", caja_editar_nombre);
	builder->get_widget("lblEditarNombre", lbl_editar_nombre);
	caja_editar_nombre->hide();
	lbl_editar_nombre->hide();
}

void VentanaVM::on_eliminar_obj_event(){
	for(int i = 0; i < morphs.size(); i++){
		if (morphs[i]->esta_en_posicion(x, y, canvas)) {
			morphs[i]->eliminar();
			if(morphs[i]->editando())
				ocultar_barra_edicion();
		}
	}
}

bool VentanaVM::on_button_press_event(GdkEventButton *event) {
	if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)){
		menu_obj.popup(event->button, event->time);
		x = event->x;
		y = event->y;
		return true;
	}
	return false;
}

void VentanaVM::on_aceptar_nombre_event() {
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = entrada_nombre->get_buffer();
	const Glib::ustring nuevo_nombre = buffer->get_text();
	for(int i = 0; i < morphs.size(); i++){
		if (morphs[i]->esta_en_posicion(x, y, canvas))
			morphs[i]->editar_nombre(nuevo_nombre);
	}
	ocultar_barra_edicion();
}

void VentanaVM::on_aceptar_slot_event() {
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = entrada_slot->get_buffer();
	const Glib::ustring nombre_slot = buffer->get_text();
	for(int i = 0; i < morphs.size(); i++){
		if (morphs[i]->esta_en_posicion(x, y, canvas)) {
			auto item = canvas->get_item(morphs[i]);
			morphs[i]->agregar_slot(nombre_slot, item);
		}
	}
	ocultar_barra_edicion();
}

void VentanaVM::on_editar_nombre_event(){
	for(int i = 0; i < morphs.size(); i++){
		if (morphs[i]->esta_en_posicion(x, y, canvas))
			morphs[i]->editando(true);
	}
	Gtk::Box* caja_editar = nullptr;
	builder->get_widget("cajaEditar", caja_editar);
	caja_editar->show_all();
	Gtk::Box* caja_agregar_slot = nullptr;
	Gtk::Label* lbl_agregar_slot = nullptr;
	builder->get_widget("boxAgregarSlot", caja_agregar_slot);
	builder->get_widget("lblAgregarSlot", lbl_agregar_slot);
	caja_agregar_slot->hide();
	lbl_agregar_slot->hide();
}

void VentanaVM::ocultar_barra_edicion(){
	entrada_nombre->delete_text(0, entrada_nombre->get_buffer()->get_text().size());
	caja_editar->hide();
}
void VentanaVM::on_quit_click() {
	hide();
}


