#ifndef AYED_TPG_1C2024_MAPA_HPP
#define AYED_TPG_1C2024_MAPA_HPP

#include "coordenada.hpp"
#include "matriz.hpp"
#include "objetos_mapa/locales.hpp"
#include <vector>
#include <stack>

/* Esta clase es la encargada de decirle a a_estrella si la posición de un vecino es válida o no.
 * Queda a criterio del grupo como implementarla. La idea es que a_estrella no tenga detalles de
 * implementación de posibles casilleros, clientes, paredes, locales, etc.
 * Adicionalmente, la pueden utilizar para otras partes del TP.
 * TIP: Tienen una matriz ya implementada como parte de la plantilla del TP. */
//class controlador_juego;
class mapa {
private:

    size_t filas;
    size_t columnas;
    matriz<int> casilleros_mapa_aurum;

    friend class controlador_juego;

public:
    //constructor.
    mapa();

    enum elementos_mapa{
        NO_CAMINABLE = 0,
        CAMINO_LIBRE = 1,
        LOCAL = 2,
        OBSTACULO = 3,
        CAMINO_MINIMO = 8
    };

    // Pre: -
    // Post: Devuelve true si la posición del vecino es válida (es decir, es una coordenada válida y es caminable).
    bool es_vecino_valido(coordenada posicion);

    // Pre: "a_agregar" debe ser un puntero valido a un objeto de tipo "local" y la coordenada del "local" debe estar dentro de los límites del mapa y ser una coordenada valida.
    // Post: El "local" es agregado al mapa en la posicion especificada.
    void agregar_local(local* a_agregar);

    // Pre: "camino" debe ser una pila no vacia de coordenadas validas en el mapa.
    // Post: Muestra el camino en el mapa resaltando el destino y el origen.
    void mostrar_camino(std::stack<coordenada> camino);

    // Pre: El mapa debe estar inicializado.
    // Post: Muestra el mapa con los elementos actuales.
    void mostrar_mapa();

    // Pre: "x" e "y" deben estar dentro de los limites del mapa.
    // Post: Devuelve True si el casillero en la coordenada (x, y) está libre, False en caso contrario.
    bool consultar_casillero_libre(int x, int y);

    // Pre: -
    // Post: Devuelve True si (x, y) está dentro de los límites válidos del mapa, False en caso contrario.
    bool validar_rango(int x, int y);

    // Pre: -
    // Post: El contenido de "a_copiar" es copiado en el objeto actual con el operados "=".
    void operator=(mapa a_copiar);

};

#endif
