#include <iostream>
#include <algorithm>
#include "grafo.hpp"

grafo::grafo(size_t cantidad_vertices) {
    matriz_adyacencia = matriz(cantidad_vertices, INFINITO);
    for (size_t i = 0; i < matriz_adyacencia.columnas(); i++) {
        matriz_adyacencia.elemento(i, i) = 0;
    }
}

void grafo::agregar_vertice() {
    size_t vertices = matriz_adyacencia.columnas() + 1;
    matriz_adyacencia.redimensionar(vertices, vertices);
    for (size_t i = 0; i < vertices - 1; i++) {
        eliminar_arista(vertices - 1, i);
        eliminar_arista(i, vertices - 1);
    }
}

void grafo::modificar_arista(size_t origen, size_t destino, int peso) {
    size_t vertices = matriz_adyacencia.columnas();
    if (origen < vertices && destino < vertices) {
        matriz_adyacencia.elemento(origen, destino) = peso;
    } else {
        std::cout << "ERROR: Los vértices no son válidos. No se cambió el camino." << std::endl;
    }
}

void grafo::aumentar_arista(size_t origen, size_t destino, int peso_a_sumar) {
    size_t vertices = matriz_adyacencia.columnas();
    if (origen < vertices && destino < vertices) {
        matriz_adyacencia.elemento(origen, destino) += peso_a_sumar;
    } else {
        std::cout << "ERROR: Los vértices no son válidos. No se cambió el camino." << std::endl;
    }
}

void grafo::eliminar_arista(size_t origen, size_t destino) {
    modificar_arista(origen, destino, INFINITO);
}

void grafo::aislar_vertice(size_t vertice) {
    size_t vertices = matriz_adyacencia.columnas();
    if (vertice < vertices) {
        for (size_t i = 0; i < vertices; i++) {
            if (i != vertice) {
                eliminar_arista(i, vertice);
                eliminar_arista(vertice, i);
            }
        }
    } else {
        std::cout << "ERROR: El vértice no es válido. No se aisló." << std::endl;
    }
}

grafo::grafo(const grafo& grafo1) {
    matriz_adyacencia = grafo1.matriz_adyacencia;
}

grafo& grafo::operator=(const grafo& grafo1) {
    if (this != &grafo1) {
        matriz_adyacencia = grafo1.matriz_adyacencia;
    }
    return *this;
}

std::vector<arista> grafo::obtener_aristas_ordenadas() {
    std::vector<arista> aristas;
    size_t vertices = matriz_adyacencia.columnas();
    for(size_t i = 0; i < vertices - 1; i++){
        for(size_t j = i + 1; j < vertices; j++){
            aristas.emplace_back(std::make_pair(i,j), matriz_adyacencia.elemento(i,j) );
        }
    }
    std::sort(aristas.begin(),aristas.end(), comparar_aristas);
    return aristas;
}
bool grafo::comparar_aristas(arista a, arista b){
    return a.obtener_peso() > b.obtener_peso();
}

void grafo::procesar_arista(arista arista_mayor_peso, std::vector<arista>& aem, std::vector <std::set<size_t>>& vertices_conectados){
    std::pair<bool, std::vector <std::set<size_t>>::iterator> pertenece_otro_arbol = {false, vertices_conectados.end()};
    bool genera_ciclo = false;
    auto arbol = vertices_conectados.begin();
    size_t vertice1 = arista_mayor_peso.obtener_vertices().first;
    size_t vertice2 = arista_mayor_peso.obtener_vertices().second;

    while (!genera_ciclo && arbol != vertices_conectados.end()){
        auto it1= arbol->find(vertice1);
        auto it2 = arbol->find(vertice2);
        genera_ciclo = it1 != arbol->end() && it2 != arbol->end();

        if (!genera_ciclo && ( it1 != arbol->end() || it2 != arbol->end() ) ) {
            if(!pertenece_otro_arbol.first){
                pertenece_otro_arbol = {true,arbol};
                aem.push_back(arista_mayor_peso);
                arbol->insert({vertice1,vertice2});
                arbol++;
            } else{
                for(auto vertice : *arbol){
                    pertenece_otro_arbol.second->insert(vertice);
                }
                vertices_conectados.erase(arbol);
                arbol = vertices_conectados.end();
            }
        } else{
            arbol++;
        }

    }
    if (!pertenece_otro_arbol.first && !genera_ciclo){
        std::set<size_t> nuevo_arbol = {vertice1,vertice2};
        vertices_conectados.push_back(nuevo_arbol);
        aem.push_back(arista_mayor_peso);
    }

}


std::vector<arista> grafo::obtener_aem() {
    std::vector<arista> aristas_ordenadas = obtener_aristas_ordenadas();
    std::vector <std::set<size_t>> vertices_conectados; //Cada elemento "sub-arbol" del aem.
    std::vector<arista> aem;
    size_t vertices = matriz_adyacencia.columnas();

    while (aem.size() < vertices - 1 && !aristas_ordenadas.empty() ){
        auto arista_mayor_peso = aristas_ordenadas.front();
        procesar_arista(arista_mayor_peso, aem, vertices_conectados);
        aristas_ordenadas.erase(aristas_ordenadas.begin());
    }

    return aem;
}


