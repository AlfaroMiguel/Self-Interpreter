#include "ventana_edicion.h"

#define GLD_BTN_ACEPTAR_NOMBRE "btnAceptarNombre"
#define GLD_ENTRADA_NOMBRE "entradaNombre"
#define GLD_BTN_GET "btnGet"
#define GLD_BTN_DO "btnDo"
#define GLD_code_entry "entradaMsj"
#define GLD_BTN_ELIMINAR "btnEliminar"
#define GLD_BTN_FINALIZAR "btnFinalizar"

VentanaEdicion::VentanaEdicion(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
								Gtk::Box(cobject){
	builder->get_widget(GLD_ENTRADA_NOMBRE, entrada_nombre);
	builder->get_widget(GLD_code_entry, code_entry);

	add_events(Gdk::BUTTON_PRESS_MASK);

	builder->get_widget(GLD_BTN_ACEPTAR_NOMBRE, boton_aceptar_nombre);
	builder->get_widget(GLD_BTN_GET, boton_get);
	builder->get_widget(GLD_BTN_DO, boton_do);
	builder->get_widget(GLD_BTN_ELIMINAR, boton_eliminar_obj);
	builder->get_widget(GLD_BTN_FINALIZAR, boton_finalizar_edicion);
	boton_aceptar_nombre->signal_clicked().connect(sigc::mem_fun(*this, &VentanaEdicion::on_aceptar_nombre_event));
	boton_get->signal_clicked().connect(sigc::mem_fun(*this, &VentanaEdicion::on_get_event));
	boton_do->signal_clicked().connect(sigc::mem_fun(*this, &VentanaEdicion::on_do_event));
	boton_eliminar_obj->signal_clicked().connect(sigc::mem_fun(*this, &VentanaEdicion::on_eliminar_obj_event));
	boton_finalizar_edicion->signal_clicked().connect(sigc::mem_fun(*this, &VentanaEdicion::on_finalizar_edicion_event));

	hide();
}

VentanaEdicion::~VentanaEdicion(){}

void VentanaEdicion::set_control(ClientHandler* client_handler){
	this->client_handler = client_handler;
}

void VentanaEdicion::on_aceptar_nombre_event() {
	const Glib::ustring new_name = entrada_nombre->get_buffer()->get_text();
	client_handler->change_morph_name(new_name.raw());
	entrada_nombre->delete_text(0, new_name.size());
}

void VentanaEdicion::on_finalizar_edicion_event(){
	client_handler->finalizar_edicion();
	ocultar_barra_edicion();
}

void VentanaEdicion::ocultar_barra_edicion(){
	entrada_nombre->delete_text(0, entrada_nombre->get_buffer()->get_text().size());
	code_entry->delete_text(0, code_entry->get_buffer()->get_text().size());
	hide();
}


void VentanaEdicion::on_eliminar_obj_event(){
	client_handler->dismiss_morph();
	ocultar_barra_edicion();
}

void VentanaEdicion::on_get_event(){
	const std::string event("get");
	send_code(event);
}

void VentanaEdicion::on_do_event(){
	const std::string event("do");
	send_code(event);
}

void VentanaEdicion::send_code(const std::string& event){
	Glib::ustring code = code_entry->get_buffer()->get_text();
	client_handler->send_code(code.raw(), event);
	code_entry->delete_text(0, code.size());
}

bool VentanaEdicion::do_start(){
	show();
	return false;
}

void VentanaEdicion::start(){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaEdicion::do_start));
}
