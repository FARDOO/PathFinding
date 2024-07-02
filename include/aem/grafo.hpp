#ifndef AYED_TPG_1C2024_GRAFO_HPP
#define AYED_TPG_1C2024_GRAFO_HPP

#include <vector>
#include <set>
#include "matriz.hpp"
#include "arista.hpp"

// Usen un valor suficientemente grande para no tener problemas.
// También, pueden usar un valor negativo.
const int INFINITO = -1;

// Este grafo va a calcular el arbol de expansión mínimo/máximo (MST).
class grafo {
private:
    matriz<int> matriz_adyacencia;

    //Pre:-
    //Post: Devuelve todas las aristas del grafo en orden decendente.
    std::vector<arista> obtener_aristas_ordenadas();

    //Pre:-
    //Post: Devuelve true si el peso de la primera arista es mayor que el de la segunda.
    static bool comparar_aristas(arista a, arista b);

    //Pre:-
    //Post: Define si la arista no genera ciclos y a que sub-arbol pertenece.
    void procesar_arista(arista arista_mayor_peso, std::vector<arista>& aem, std::vector <std::set<size_t>>& vertices_conectados);


public:
    // Constructores.
    grafo() = default;

    grafo(size_t cantidad_vertices);

    // Pre: -
    // Post: Agrega un nuevo vértice aislado al grafo (es decir, no tiene ninguna arista asociada).
    // NOTA: El número del vértice corresponde con el último índice agregado a la matriz.
    // Por ejemplo, si tienen 5 vértices y se agrega uno más, ese vértice es el 5 (recordar que matriz es 0-indexed).
    void agregar_vertice();

    void aumentar_arista(size_t origen, size_t destino, int peso_a_sumar);

    // Pre: -
    // Post: Agrega (o modifica) la arista desde origen a destino. Si los vértices no son válidos, la matriz no cambia.
    // NOTA: Como solo se guarda una arista entre dos vértices, este grafo no puede tener aristas paralelas.
    void modificar_arista(size_t origen, size_t destino, int peso);

    // Pre: -
    // Post: Elimina la arista desde origen a destino. Si los vértices no son válidos, la matriz no cambia.
    void eliminar_arista(size_t origen, size_t destino);

    // Pre: -
    // Post: Aisla el vértice. Si no es válido, la matriz no cambia.
    void aislar_vertice(size_t vertice);

    // Constructor de copia.
    grafo(const grafo& grafo1);

    // Operador de asignación.
    grafo& operator=(const grafo& grafo1);

    // Pre: El grafo representado debe ser conexo y no direccionado (asumirlo).
    // Post: Devuelve el arbol de expansión mínimo/máximo.
    // NOTA: Me base en el algoritmo de kruskal para implementar este metodo.
    std::vector<arista> obtener_aem();
};

#endif