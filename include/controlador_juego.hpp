//
// Created by David on 21/6/2024.
//

#ifndef AYED_TPG_1C2024_CONTROLADOR_JUEGO_HPP
#define AYED_TPG_1C2024_CONTROLADOR_JUEGO_HPP
#include <string>
#include "objetos_mapa/locales.hpp"
#include "a_estrella/a_estrella.hpp"
#include "vertice.hpp"
#include "mapa.hpp"
#include "diccionario.hpp"
#include "minijuego.hpp"
#include "grafo.hpp"

class controlador_juego_exeption : public std::exception {};
bool comparar(std::string local_a, std::string local_b);
int distanciaManhattan(vertice* origen, vertice* destino);

class controlador_juego{

private:

    diccionario<std::string,local*,comparar>* locales;
    mapa* mapa_callejon_aurum;
    minijuego minijuego1;
    grafo grafo_pedidos;
public:
    //constructor
    controlador_juego();

    grafo generar_grafo_conexo();

    size_t definir_indice(coordenada coordenada_local);

    void mostrar_minijuego();
    //pre:El puntero no debe ser nulo
    //pos:Agrega el local al diccionario locales
    bool agregar_local(local* nuevo_local);

    //pre:Los punteros deben no ser nulos
    //pos:agrega un nuevo pedido al local origen
    void agregar_pedido(local* origen,local* destino, size_t peso);

    //pre:-
    //pos:muestra por consola los caminos realizados para entrgar los pedidos del local
    //    pasado por parametro o el camino del pedido de mayor prioridad si no se pasa un local
    void realizar_pedidos(local* local = nullptr);

    void realizar_pedidos_de_mayor_prioridad();

    void realizar_pedido(local* local);

    //pre:-
    //pos:muestra por pantalla el mapa del juego
    void mostrar_callejo_aurum();

    //pre:-
    //pos:devuelve un vecctor con coordenadas validas para colocar obstaculos
    std::vector<coordenada> generar_obstaculos();

    //pre:-
    //pos:coloca obstaculos en el mapa en las coordenadas contenidas en el vector
    void colocar_obstaclos_en_mapa(std::vector<coordenada> obstaculos);

    //pre:-
    //pos:quitas los obstaculos de las coordenadas contenidas en el vector pasado por parametro
    void quitar_obstaculos(std::vector<coordenada> obstaculos);

    //pre:-
    //pos:agrega 6 locales diccionario de locales
    void generar_locales();

    //pre:-
    //pos:genera un numero aleatorio de pedidos a locales aleatorios
    void agregar_pedidos_aleatorios();

    //pre:-
    //pos:muestra por consola los locales con su coordenada y cantidad de pedidos
    void mostrar_locales();

    //pre:-
    //pos:devuelve el local en la posicion pasada por parametro
    local* seleccionar_local(size_t posicion);

    //destructor
    ~controlador_juego();
};

#endif //AYED_TPG_1C2024_CONTROLADOR_JUEGO_HPP
