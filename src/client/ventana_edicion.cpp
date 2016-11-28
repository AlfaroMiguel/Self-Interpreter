#include "ventana_edicion.h"

#define GLD_BTN_GET "btnGet"
#define GLD_BTN_DO "btnDo"
#define GLD_CODE_ENTRY "entryCode"
#define GLD_BTN_ELIMINAR "btnDelete"
#define GLD_NAME_ENTRY "entryName"
#define GLD_BTN_CODE "btnCode"
#define GLD_BTN_ADD_SLOT "btnAddSlot"
#define GLD_BTN_REMOVE_SLOT "btnRemoveSlot"
#define GLD_BTN_FINALIZAR_EDICION "btnFinalizarEdicion"
#define GLD_BTN_CHANGE_LOBBY "btnChangeLobby"

VentanaEdicion::VentanaEdicion(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
								Gtk::Box(cobject){
	builder->get_widget(GLD_CODE_ENTRY, code_entry);
	builder->get_widget(GLD_NAME_ENTRY, name_entry);

	add_events(Gdk::BUTTON_PRESS_MASK);

	builder->get_widget(GLD_BTN_GET, boton_get);
	builder->get_widget(GLD_BTN_DO, boton_do);
	builder->get_widget(GLD_BTN_ELIMINAR, boton_eliminar_obj);
	builder->get_widget(GLD_BTN_CODE, code_hint);
	builder->get_widget(GLD_BTN_ADD_SLOT, add_slot_hint);
	builder->get_widget(GLD_BTN_REMOVE_SLOT, remove_slot_hint);
	builder->get_widget(GLD_BTN_FINALIZAR_EDICION, close_editing_btn);
	builder->get_widget(GLD_BTN_CHANGE_LOBBY, change_lobby_btn);
	boton_get->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_get_event));
	boton_do->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_do_event));
	boton_eliminar_obj->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_eliminar_obj_event));
	code_hint->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_code_hint_event));
	add_slot_hint->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_add_slot_hint_event));
	remove_slot_hint->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_remove_slot_hint_event));
	close_editing_btn->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_close_editing_event));
	change_lobby_btn->signal_clicked().connect
		(sigc::mem_fun(*this, &VentanaEdicion::on_change_lobby_event));
	hide();
}

VentanaEdicion::~VentanaEdicion(){}

void VentanaEdicion::on_change_lobby_event(){
	client_handler->show_lobby_options();
}

void VentanaEdicion::add_to_code_entry(const Glib::ustring& code){
	code_entry->get_buffer()->insert_at_cursor(code);
}

void VentanaEdicion::on_code_hint_event() {
	add_to_code_entry("(||).");
	code_entry->grab_focus();
}

void VentanaEdicion::on_add_slot_hint_event() {
	add_to_code_entry("self _AddSlot: (||).");
	code_entry->grab_focus();
}

void VentanaEdicion::on_remove_slot_hint_event() {
	add_to_code_entry("self _RemoveSlot: (||).");
	code_entry->grab_focus();
}

void VentanaEdicion::set_control(ClientHandler* client_handler){
	this->client_handler = client_handler;
}

void VentanaEdicion::ocultar_barra_edicion(){
	name_entry->delete_text(0, name_entry->get_buffer()->get_text().size());
	code_entry->get_buffer()->set_text("");
	hide();
}

void VentanaEdicion::on_close_editing_event(){
	ocultar_barra_edicion();
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
	code_entry->get_buffer()->set_text("");
}

bool VentanaEdicion::do_start(const std::string& morph_name){
	name_entry->get_buffer()->set_text(morph_name);
	show();
	return false;
}

void VentanaEdicion::start(const std::string& morph_name){
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &VentanaEdicion::do_start), morph_name));
}

bool VentanaEdicion::on_key_release_event(GdkEventKey* eventKey){
	if (eventKey->keyval == GDK_KEY_Return && name_entry->has_focus()){
		client_handler->change_morph_name((name_entry->get_buffer()->get_text()).raw());
		code_entry->grab_focus();
	}
	return true;
}
