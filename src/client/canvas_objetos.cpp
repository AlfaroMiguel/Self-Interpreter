#include "canvas_objetos.h"

CanvasObj::CanvasObj() {
	set_size_request(200,200);
	root = get_root_item();
	add_events(Gdk::BUTTON_PRESS_MASK);
	objeto_nuevo.set_label("Nuevo Objeto");
	objeto_nuevo.signal_activate().connect(sigc::mem_fun(*this, &CanvasObj::on_obj_nuevo_event));
	menu_der.append(objeto_nuevo);
	menu_der.show_all();
}

CanvasObj::~CanvasObj() {}

void CanvasObj::dibujar_morph() {
	Glib::RefPtr<Goocanvas::Rect> cuadrado = Goocanvas::Rect::create(100, 100, 100, 100);
	cuadrado->property_fill_color().set_value("blue");
	root->add_child(cuadrado);
}

void CanvasObj::on_obj_nuevo_event() {
	dibujar_morph();
}

bool CanvasObj::on_button_press_event(GdkEventButton *event) {
	if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)){
		menu_der.popup(event->button, event->time);
		return true;
	}
	return false;
}