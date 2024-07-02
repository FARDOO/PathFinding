#include "a_estrella.hpp"
#include <algorithm>

vertice* a_estrella::buscar_mejor_vertice() {
    vertice* mejor_vertice = nullptr;
    auto it = min_element(set_abierto.begin(), set_abierto.end(), vertice::menor);
    if (it != set_abierto.end()) {
        mejor_vertice = *it;
        set_abierto.erase(it);
    }
    return mejor_vertice;
}

vertice* a_estrella::buscar_vertice(std::vector<vertice*> set, coordenada posicion) {
    vertice* vertice_buscado = nullptr;
    auto coincide_posicion = [&posicion](vertice* v) { return *v == posicion; };
    auto it = std::find_if(set.begin(), set.end(), coincide_posicion);
    if (it != set.end()) {
        vertice_buscado = *it;
    }
    return vertice_buscado;
}

void a_estrella::limpiar_sets() {
    for (vertice* vertice: set_abierto) {
        delete vertice;
    }
    for (vertice* vertice: set_cerrado) {
        delete vertice;
    }
    set_abierto.clear();
    set_cerrado.clear();
}

std::stack<coordenada> a_estrella::reconstruir_camino(vertice* destino) {
    std::stack<coordenada> camino;
    vertice* actual = destino;

    while ( actual != nullptr ) {
        camino.push(actual->posicion);
        actual = actual->padre;
    }

    return camino;
}

void a_estrella::procesar_vecino(vertice* prometedor, coordenada vecino, vertice *vertice_destino, mapa& mapa_callejon,
                                 int heuristica(vertice*, vertice*)) {

    if (buscar_vertice(set_cerrado, vecino) == nullptr &&
    buscar_vertice(set_abierto, vecino) == nullptr &&
    mapa_callejon.es_vecino_valido(vecino)) {
        auto vecino_a_agregar = new vertice(vecino,prometedor);
        vecino_a_agregar->costo_origen = prometedor->costo_origen + 1;
        vecino_a_agregar->distancia_destino = heuristica(vecino_a_agregar, vertice_destino);
        set_abierto.push_back(vecino_a_agregar);
    }
}

void a_estrella::expandir_vertice(vertice* prometedor, vertice* vertice_destino, mapa& mapa_callejon,
                                  int heuristica(vertice*, vertice*)) {
    std::vector<coordenada> vecinos = {
            {prometedor->posicion.x() - 1, prometedor->posicion.y()},
            {prometedor->posicion.x() + 1, prometedor->posicion.y()},
            {prometedor->posicion.x(), prometedor->posicion.y() - 1},
            {prometedor->posicion.x(), prometedor->posicion.y() + 1}
    };

    for (auto& vecino : vecinos) {
        procesar_vecino(prometedor, vecino, vertice_destino, mapa_callejon, heuristica);
    }
}

std::stack<coordenada> a_estrella::obtener_camino_minimo(coordenada origen, coordenada destino, mapa& mapa_callejon,
                                                         int heuristica(vertice*, vertice*)) {
  
    auto vertice_origen = new vertice(origen);
    auto vertice_destino = new vertice(destino);
    bool destino_alcanzado = false;
    vertice* prometedor;
    set_abierto.push_back(vertice_origen);
    std::stack<coordenada> camino;
    while (!set_abierto.empty() && !destino_alcanzado) {
        prometedor = buscar_mejor_vertice();
        if (prometedor->posicion == destino) {
            camino = reconstruir_camino(prometedor);
            destino_alcanzado = true;
        }
        set_cerrado.push_back(prometedor);
        expandir_vertice(prometedor, vertice_destino, mapa_callejon, heuristica);
    }

    delete vertice_destino;

    limpiar_sets();
    return camino;
}
