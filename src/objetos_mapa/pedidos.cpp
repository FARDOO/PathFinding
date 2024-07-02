#include "pedidos.hpp"

using namespace std;

pedido::pedido(coordenada origen, coordenada destino,
               size_t peso, size_t prioridad_local){
    this->origen = origen;
    this->destino = destino;
    this->peso = peso;
    this->prioridad_pedido = peso * prioridad_local;
}

coordenada pedido::get_origen() const {
    return this->origen;
}

coordenada pedido::get_destino() const {
    return this->destino;
}

size_t pedido::get_prioridad_pedido() const {
    return this->prioridad_pedido;
}

bool pedido::operator<(pedido a_comparar) const {
    return this->get_prioridad_pedido() < a_comparar.get_prioridad_pedido();

}