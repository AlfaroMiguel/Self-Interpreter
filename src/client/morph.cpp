#include "morph.h"
#include <vector>
Morph::Morph(double x, double y, double width, double height){
	base = Goocanvas::Rect::create(x, y, width, height);
	base->property_fill_color().set_value("blue");
	titulo = Goocanvas::Text::create("hola", x, y);
	items.push_back(base);
	items.push_back(titulo);
}

Morph::~Morph(){}

Glib::RefPtr<Morph> Morph::create(double x, double y, double width, double height){
	return Glib::RefPtr<Morph>(new Morph(x,y,width,height));
}

void Morph::eliminar(){
	base->remove();
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

bool Morph::esta_en_posicion(double x, double y, Goocanvas::Canvas* canvas) {
	Glib::RefPtr<Goocanvas::Item> item_en_pos = canvas->get_item_at(x, y, true);
	for(int i = 0; i < items.size(); i++){
		if (item_en_pos == items[i])
			return true;
	}
	return false;
}

bool Morph::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) {
	if(item && dragging && item == dragging) {
		auto new_x = event->x;
		auto new_y = event->y;
		base->translate(new_x - drag_x, new_y - drag_y);
		titulo->translate(new_x - drag_x, new_y - drag_y);
	}
	return false;
}

void Morph::conectar_seniales(const Glib::RefPtr<Goocanvas::Item>& item){
	item->signal_button_press_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_press_event));
	item->signal_button_release_event().connect(sigc::mem_fun(*this, &Morph::on_item_button_release_event));
	item->signal_motion_notify_event().connect(sigc::mem_fun(*this, &Morph::on_item_motion_notify_event));
	item->add_child(base);
	item->add_child(titulo);
}