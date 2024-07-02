#include "interfaz_de_usuario.hpp"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void interfaz_de_usuario::iniciar() {
    cout << "                                  " << endl;
    cout << "\n=======================================" << endl;
    cout << "           A*, MST, BST, HEAP       " << endl;
    cout << "=======================================\n" << endl;
    this->juego.generar_locales();
    juego.mostrar_callejo_aurum();
    int opcion;
    do {
        cout << endl;
        cout << "1: Add random orders" << endl;
        cout << "2: Place orders" << endl;
        cout << "3: Place the highest priority order" << endl;
        cout << "4: View optimal path" << endl;
        cout << "0: Exit" << endl;
        cout << endl;
        opcion = validar_rango_entre(0,5,"Select an option: ");
        cout << endl;
        switch (opcion) {
            case 1:
                this->juego.agregar_pedidos_aleatorios();
                break;
            case 2:
                this->menu_realizar_pedidos();
                break;
            case 3:
                this->juego.realizar_pedidos_de_mayor_prioridad();
                break;
            case 4:
                juego.mostrar_minijuego();
                break;
        }

        cout << endl;
    } while (opcion != 0);
}

void interfaz_de_usuario::menu_realizar_pedidos() {
    this->juego.mostrar_callejo_aurum();
    this->juego.mostrar_locales();
    cout << "0 - Exit" << endl;
    cout << endl;
    int opcion = this->validar_rango_entre(0,6,"Select a store: ");
    if(opcion > 0){
        opcion--;
        local*  local_seleccionado = this->juego.seleccionar_local(static_cast<size_t>(opcion));
        this->juego.realizar_pedidos(local_seleccionado);
    }
}

int interfaz_de_usuario::validar_rango_entre(int menor, int mayor, string mensaje) {
    int numero_a_validar;
    do{
        cout << mensaje;
        numero_a_validar = this->validar_numero();
    }while((numero_a_validar > mayor) || (numero_a_validar < menor));
    return numero_a_validar;
}

int interfaz_de_usuario::validar_numero() {
    string opcion;
    int numero;
    char letra;
    bool es_valido;
    do{
        es_valido = true;
        getline(cin, opcion);
        for(size_t i = 0; i < opcion.size(); i++) {
            letra = opcion[i];
            if(!isdigit(letra)) {
                es_valido = false;
            }
        }
        if(es_valido) {
            std::stringstream sstream(opcion);
            sstream >> numero;
        }else{
            cout << endl;
            cout << "Invalid value, please enter the requested value again. ";
        }
    }while(!es_valido);
    return numero;
}

