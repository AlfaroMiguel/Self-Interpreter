#include "ventanaVM.h"
#include "morph.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <vector>
#include <map>
#include "comunicador_server.h"

#define GLD_CAJA_BASE "cajaBase"
#define GLD_CAJA_EDITAR "cajaEditar"
#define GLD_BTN_ACEPTAR_NOMBRE "btnAceptarNombre"
#define GLD_ENTRADA_NOMBRE "entradaNombre"
#define GLD_BTN_GET "btnGet"
#define GLD_BTN_DO "btnDo"
#define GLD_ENTRADA_MSJ "entradaMsj"
#define GLD_BTN_ELIMINAR "btnEliminar"
#define GLD_BTN_FINALIZAR "btnFinalizar"

VentanaVM::VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
							Gtk::Window(cobject), builder(builder){
	maximize();
//TODO: que solo aparezca el menu en el canvas
	caja_base = nullptr;
	builder->get_widget(GLD_CAJA_BASE, caja_base);
	canvas = Gtk::manage(new Goocanvas::Canvas());
	canvas->set_size_request(800, 800);
	canvas->set_hexpand(true);
	caja_base->add(*canvas);
	add_events(Gdk::BUTTON_PRESS_MASK);
	root = Goocanvas::Group::create();
	canvas->set_root_item(root);
	caja_editar = nullptr;
	builder->get_widget(GLD_CAJA_EDITAR, caja_editar);
	Gtk::Button* boton_aceptar_nombre = nullptr;
	builder->get_widget(GLD_BTN_ACEPTAR_NOMBRE, boton_aceptar_nombre);
	boton_aceptar_nombre->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_aceptar_nombre_event));
	entrada_nombre = nullptr;
	builder->get_widget(GLD_ENTRADA_NOMBRE, entrada_nombre);
	Gtk::Button* boton_get = nullptr;
	builder->get_widget(GLD_BTN_GET, boton_get);
	boton_get->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_get_event));
	Gtk::Button* boton_do = nullptr;
	builder->get_widget(GLD_BTN_DO, boton_do);
	boton_do->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_do_event));
	entrada_msj = nullptr;
	builder->get_widget(GLD_ENTRADA_MSJ, entrada_msj);
	Gtk::Button* boton_eliminar_obj = nullptr;
	builder->get_widget(GLD_BTN_ELIMINAR, boton_eliminar_obj);
	boton_eliminar_obj->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_eliminar_obj_event));
	Gtk::Button* boton_finalizar_edicion = nullptr;
	builder->get_widget(GLD_BTN_FINALIZAR, boton_finalizar_edicion);
	boton_finalizar_edicion->signal_clicked().connect(sigc::mem_fun(*this, &VentanaVM::on_finalizar_edicion_event));
	std::map<Glib::ustring, Glib::ustring> slots;
	Glib::ustring shell = "shell";
	dibujar_morph(shell, 0, 0, slots);
	show_all_children();
	caja_editar->hide();
}

VentanaVM::~VentanaVM() {}

void VentanaVM::dibujar_morph(Glib::ustring& nombre, double x, double y, std::map<Glib::ustring, Glib::ustring> slots) {
	Glib::RefPtr<Morph> morph = Morph::create(x, y, nombre);
	morphs.push_back(morph);
	root->add_child(morph);
	//auto item = canvas->get_item(morph);
	morph->conectar_seniales();
	morph->agregar_slots(slots);
}

void VentanaVM::crear_objeto(Glib::ustring& nombre, std::map<Glib::ustring, Glib::ustring> slots) {
	morphs_activos += 1;
	morphs_creados += 1;
	//Glib::ustring valor;
	dibujar_morph(nombre, x, y, slots);
}

void VentanaVM::on_eliminar_obj_event(){
	morph_editando->eliminar();
	ocultar_barra_edicion();
	morphs_activos -= 1;
}

void VentanaVM::on_editar_obj_event(){
	for(unsigned int i = 0; i < morphs.size(); i++){
		if (morphs[i]->esta_en_posicion(x, y)) {
			morphs[i]->editando(true);
			morph_editando = morphs[i];
			caja_editar->show_all();
		}
	}
}

void VentanaVM::on_get_event(){
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = entrada_msj->get_buffer();
	Glib::ustring mensaje = buffer->get_text();
	if (mensaje.empty()) return;
	//aca hay que mandarle la cadena al modelo y hacer segun lo que diga
	std::cout << "Recibe mensaje: " << mensaje << std::endl;
	com_server.ejecutar_mensaje(mensaje.raw());
	entrada_msj->delete_text(0, entrada_msj->get_buffer()->get_text().size());
	//hc para ver si anda agregar slot
	Glib::ustring slot1 = "x";
	Glib::ustring slot2 = "y";
	Glib::ustring valor1 = "4";
	Glib::ustring valor2 = "6";
	std::map<Glib::ustring, Glib::ustring> slots;
	slots.insert(std::make_pair(slot1, valor1));
	slots.insert(std::make_pair(slot2, valor2));
	crear_objeto(mensaje, slots);
}

void VentanaVM::on_do_event(){
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = entrada_msj->get_buffer();
	const Glib::ustring mensaje = buffer->get_text();
	if (mensaje.empty()) return;
	//aca hay que mandarle la cadena al modelo y hacer segun lo que diga
	std::cout << "Recibe mensaje: " << mensaje << std::endl;
	entrada_msj->delete_text(0, entrada_msj->get_buffer()->get_text().size());
	//hc para ver si anda agregar slot
	//dibujar_morph(mensaje, x, y);
}


bool VentanaVM::on_button_press_event(GdkEventButton *event) {
	if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)){
		std::cout << "doble click" << std::endl;
		x = event->x;
		y = event->y;
		if (morphs_activos == 0) return false;
		for(unsigned int i = 0; i < morphs.size(); i++) {
			if (morphs[i]->esta_en_posicion(x, y)) {
				std::cout << "entra al if" << std::endl;
				morphs[i]->editando(true);
				morph_editando = morphs[i];
				caja_editar->show_all();
			}
		}
		return true;
	}
	return false;
}

void VentanaVM::on_aceptar_nombre_event() {
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = entrada_nombre->get_buffer();
	const Glib::ustring nuevo_nombre = buffer->get_text();
	if (morph_editando) morph_editando->editar_nombre(nuevo_nombre);
	entrada_nombre->delete_text(0, entrada_nombre->get_buffer()->get_text().size());
}

void VentanaVM::on_finalizar_edicion_event(){
	for(unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->esta_en_posicion(x, y))
			morphs[i]->editando(false);
	ocultar_barra_edicion();
}

void VentanaVM::ocultar_barra_edicion(){
	entrada_nombre->delete_text(0, entrada_nombre->get_buffer()->get_text().size());
	entrada_msj->delete_text(0, entrada_msj->get_buffer()->get_text().size());
	caja_editar->hide();
}
void VentanaVM::on_quit_click() {
	hide();
}

void VentanaVM::set_comunicador(ComunicadorServer& comunicador){
	com_server = std::move(comunicador);
}

