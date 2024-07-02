#ifndef AYED_TPG_1C2024_PEDIDOS_HPP
#define AYED_TPG_1C2024_PEDIDOS_HPP

#include "coordenada.hpp"


class pedido {
private:
    coordenada origen;
    coordenada destino;
    std::size_t peso;
    std::size_t prioridad_pedido;

public:
    pedido(coordenada origen, coordenada destino, std::size_t peso, std::size_t prioridad_local);


    // Pre: -
    // Post: Devuelve la coordenada de origen del pedido.
    coordenada get_origen() const;

    // Pre: -
    // Post: Devuelve la coordenada de destino del pedido.    
    coordenada get_destino() const;

    // Pre: -
    // Post: Devuelve la prioridad del pedido.    
    std::size_t get_prioridad_pedido() const;

    // Pre: -
    // Post: Devuelve True si la prioridad del pedido actual es menor que la prioridad del pedido "a_comparar", False en caso contrario, utilizando el operador "<".
    bool operator<(pedido a_comparar) const;

};


#endif // AYED_TPG_1C2024_PEDIDOS_HPP
