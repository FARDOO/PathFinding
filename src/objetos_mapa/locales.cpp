#include "objetos_mapa/locales.hpp"
bool comparar_prioridad(pedido a, pedido b){
    return b < a;
}

local::local(const std::string& nombre, size_t prioridad, int x, int y){
    this->nombre = nombre;
    this->prioridad = prioridad;
    this->posicion = coordenada (x,y);
}

std::string local::get_nombre() const {
    return this->nombre;
}

size_t local::get_prioridad() const{
    return this->prioridad;
}

coordenada local::get_coordenada() const {
    return this->posicion;
}


void local::crear_pedido(local* destino, size_t peso) {
    pedido nuevo_pedido(this->posicion,destino->get_coordenada(),peso,this->prioridad);
    pedidos_local.alta(nuevo_pedido);
}

heap<pedido, comparar_prioridad> local::get_pedidos_local() {
    return pedidos_local;
}

void local::borrar_pedido_local() {
    if(!pedidos_local.vacio()){
        pedidos_local.baja();
    }
}
