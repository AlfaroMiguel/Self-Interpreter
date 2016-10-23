#include "ventanaVM.h"
#include "canvas_objetos.h"
#include "morph.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <vector>

#define TITULO_VENTANA "Self Virtual Machine"
#define BTN_NUEVO_OBJ "Nuevo Objeto"
#define BTN_ELIMINAR_OBJ "Eliminar Objeto"

VentanaVM::VentanaVM() {
	set_default_size(600, 400);
	set_title(TITULO_VENTANA);
	maximize();
	set_border_width(0);

	hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	add(*hbox);
	canvas = Gtk::manage(new Goocanvas::Canvas());
	canvas->set_size_request(400,400);
	hbox->set_homogeneous(false);
	hbox->set_center_widget(*canvas);
	add_events(Gdk::BUTTON_PRESS_MASK);
	crear_menu_objetos();
	root = Goocanvas::GroupModel::create();
	canvas->set_root_item_model(root);
	show_all_children();
}

VentanaVM::~VentanaVM() {}

void VentanaVM::crear_menu_objetos(){
	objeto_nuevo.set_label(BTN_NUEVO_OBJ);
	eliminar_objeto.set_label(BTN_ELIMINAR_OBJ);
	objeto_nuevo.signal_activate().connect(sigc::mem_fun(*this, &VentanaVM::on_obj_nuevo_event));
	eliminar_objeto.signal_activate().connect(sigc::mem_fun(*this, &VentanaVM::on_eliminar_obj_event));
	menu_obj.append(objeto_nuevo);
	menu_obj.append(eliminar_objeto);
	menu_obj.show_all();
}
void VentanaVM::dibujar_morph(double x, double y) {
	Glib::RefPtr<Morph> morph = Morph::create(x, y, 100, 50);
	morphs.push_back(morph);
	root->add_child(morph);
	auto item = canvas->get_item(morph);
	morph->conectar_seniales(item);
}

void VentanaVM::on_obj_nuevo_event() {
	dibujar_morph(x, y);
}

void VentanaVM::on_eliminar_obj_event(){
	for(int i = 0; i < morphs.size(); i++){
		if (morphs[i]->esta_en_posicion(x, y, canvas))
			morphs[i]->eliminar();
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
void VentanaVM::on_quit_click() {
	hide();
}


