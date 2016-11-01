#include "modelo.h"
#include "ventana_objetos.h"
#include "ventana_edicion.h"

Modelo::Modelo(const std::string& hostname, const std::string& puerto): com_server(hostname, puerto){
	std::cout << "CREANDO EL MODELO" << std::endl;
	com_server.set_modelo(this);
	std::cout << "MODELO CREADO" << std::endl;
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
	//TODO: ARREGLAR LO DE STRING Y USTRING
	std::cout << "CREANDO MORPH" << std::endl;
	const Glib::ustring nombre_morph(nombre);
	Glib::RefPtr<Morph> morph = Morph::create(x, y, nombre_morph);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(dic_slots);
	std::cout << "MORPH CREADO" << std::endl;
	ventana_objetos->dibujar_morph(morph);
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
