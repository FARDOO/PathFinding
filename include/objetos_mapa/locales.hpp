#ifndef AYED_TPG_1C2024_LOCALES_HPP
#define AYED_TPG_1C2024_LOCALES_HPP

#include <string>
#include "heap.hpp"
#include "pedidos.hpp"

bool comparar_prioridad(pedido a, pedido b);

class local{
private:
    heap<pedido, comparar_prioridad> pedidos_local;
    std::string nombre;
    size_t prioridad;
    coordenada posicion;
public:

    local(const std::string& nombre, size_t prioridad, int x, int y);

    // Pre: "destino" debe ser un puntero valido a un objeto local.
    // Post: crea un pedido y lo añade a los heaps.
    void crear_pedido(local* destino, size_t peso);

    // Pre: -
    // Post: Devuelve el nombre del local.
    std::string get_nombre() const;

    // Pre: -
    // Post: Devuelve la prioridad del local.   
    size_t get_prioridad() const;

    // Pre: -
    // Post: Devuelve la coordenada del local.
    coordenada get_coordenada() const;
    
    // Pre: -
    // Post: Devuelve el heap de pedidos global.
    static heap<pedido, comparar_prioridad> get_pedidos();

    // Pre: -
    // Post: Devuelve el heap de pedidos local.
    heap<pedido, comparar_prioridad> get_pedidos_local();

    // Pre: El heap de pedidos local no debe estar vacio.
    // Post: Elimina el pedido de mayor prioridad del heap de pedidos locales.
    void borrar_pedido_local();

};

#endif // AYED_TPG_1C2024_LOCALES_HPP

