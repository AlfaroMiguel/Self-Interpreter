#include "modelo.h"
#include "ventana_objetos.h"
#include "ventana_edicion.h"
#include "ventana_inicio.h"
#include "ventanaVM.h"

Modelo::Modelo(const std::string& hostname, const std::string& puerto): com_server(hostname, puerto){
	com_server.set_modelo(this);
}

Modelo::~Modelo(){}

Modelo::Modelo(Modelo&& otra): morphs(otra.morphs), morph_editando(otra.morph_editando),
								com_server(std::move(otra.com_server)), ventana_objetos(otra.ventana_objetos){}

Modelo& Modelo::operator=(Modelo&& otra){
	morphs = otra.morphs;
	morph_editando = otra.morph_editando;
	com_server = std::move(otra.com_server);
	ventana_objetos = otra.ventana_objetos;
	return *this;
}

bool Modelo::editar_morph(double x, double y){
	for(unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->esta_en_posicion(x, y)) {
			morphs[i]->editando(true);
			morph_editando = morphs[i];
			ventana_edicion->show_all();
			return true;
		}
	}
	return false;
}

void Modelo::cambiar_nombre_morph(const std::string& nuevo_nombre){
	if (morph_editando) morph_editando->editar_nombre(nuevo_nombre);
}

void Modelo::finalizar_edicion(){
	if (morph_editando) morph_editando->editando(false);
}

void Modelo::eliminar_morph(double x, double y){
	if (morph_editando){
		ventana_objetos->eliminar_morph(morph_editando);
		for(unsigned int i = 0; i < morphs.size(); i++){
			if (morphs[i] == morph_editando)
				morphs.erase(morphs.begin()+i);
		}
	}
}

void Modelo::enviar_mensaje(const std::string& mensaje, const std::string& evento){
	if (mensaje.empty()) return;
	com_server.enviar_mensaje(mensaje, evento);
}

void Modelo::crear_morph(const std::string& nombre, double x, double y, std::map<std::string, std::string> dic_slots) {
	const Glib::ustring nombre_morph(nombre);
	Glib::RefPtr<Morph> morph = Morph::create(x, y, nombre_morph);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(dic_slots);
	ventana_objetos->dibujar_morph(morph);
}

void Modelo::unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2) {
	double x_inicio = morph1->get_x();
	double x_fin = morph2->get_x();
	double y_inicio = morph1->get_y();
	double y_fin = morph2->get_y();
	Glib::RefPtr <Goocanvas::Polyline> linea = Goocanvas::Polyline::create(x_inicio, y_inicio, x_fin, y_fin);
	morph1->agregar_union(linea);
	morph2->agregar_union(linea);
}

void Modelo::set_vista_objetos(VentanaObjetos* vista){
	ventana_objetos = vista;
	std::map<std::string, std::string> slots;
	const std::string shell("shell");
	crear_morph(shell, 0, 0, slots);
}

void Modelo::set_vista_editar(VentanaEdicion* vista){
	ventana_edicion = vista;
}

void Modelo::set_vista_inicio(VentanaInicio* vista){
	ventana_inicio = vista;
}

void Modelo::crear_morph_de_slot(double x, double y){
	if (morph_editando){
		std::map<std::string, std::string> dic_slots;
		const std::string nombre = morph_editando->obtener_nombre_slot(x, y);
		if (! nombre.empty())
			crear_morph(nombre, x + 50, y + 50, dic_slots);
	}
}

void Modelo::set_lobby(const std::string& id){
	ventana_inicio->agregar_lobby(id);
}

void Modelo::iniciar() {
	ventana_inicio->iniciar();
}

void Modelo::inicializar(){
	com_server.inicializar();
}

void Modelo::abrir_vm(VentanaVM* ventanavm, const std::string& lobby, const std::string& nombre_cliente){
	this->ventana_vm = ventanavm;
	com_server.enviar_datos_cliente(lobby, nombre_cliente);
}

void Modelo::crear_vm(){
	//aca creo todos los morphs
	//ventana_vm->mostrar();
	ventana_vm->iniciar();
}