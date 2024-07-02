#include <iostream>
#include "mapa.hpp"
#include "colors.hpp"


mapa::mapa() {
    filas = 18;
    columnas = 24;
    casilleros_mapa_aurum = matriz<int>(filas,columnas);
    std::vector<std::vector<int>> aux = {
            {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0},
            {1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0},
            {1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0},
            {1,1,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0},
            {1,1,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0},
            {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    for (size_t f = 0; f < filas; f++){
        for(size_t c = 0; c < columnas; c++){
            casilleros_mapa_aurum.elemento(f,c) = aux[f][c];
        }
    }
}


bool mapa::es_vecino_valido(coordenada posicion) {
    bool vecino_valido = false;
    if(0 <= posicion.x() && static_cast<size_t>(posicion.x()) < casilleros_mapa_aurum.columnas() &&
    0 <= posicion.y() && static_cast<size_t>(posicion.y()) < casilleros_mapa_aurum.filas() ){
        if(casilleros_mapa_aurum.elemento(static_cast<size_t>(posicion.y()), static_cast<size_t>(posicion.x())) == CAMINO_LIBRE
        || casilleros_mapa_aurum.elemento(static_cast<size_t>(posicion.y()), static_cast<size_t>(posicion.x())) == 6 ) {
            vecino_valido = true;
        }
    }
    return vecino_valido;
}

void mapa::mostrar_camino(std::stack<coordenada> camino){
    matriz aux = this->casilleros_mapa_aurum;
    coordenada origen(camino.top().y(), camino.top().x());
    coordenada destino;
    while(!camino.empty()){
        aux.elemento(static_cast<size_t>(camino.top().y()), static_cast<size_t>(camino.top().x())) = 8;
        if(camino.size() == 1){
            destino.first = camino.top().y();
            destino.second = camino.top().x();
        }
        camino.pop();
    }
    for(size_t i = 0 ; i < this->filas ; i++){
        if(i < 10){
            std::cout << BLUE << i << "  - ";
        }else{
            std::cout << BLUE << i << " - ";
        }
        for(size_t j = 0 ; j < this->columnas ; j++){
            if(origen.first == (int)i && origen.second == (int)j){
                std::cout << BG_BLUE << BLUE << " " << "  ";
            }else if(destino.first == (int)i && destino.second == (int)j){
                std::cout << BG_MAGENTA << MAGENTA << " " << "  " << RESET;
            }else if(aux.elemento(i,j) == NO_CAMINABLE) {
                std::cout << BG_GRAY << GRAY << " " << "  " << RESET;
            }else if(aux.elemento(i,j) == LOCAL) {
                std::cout << BG_YELLOW<< " "  << "  " << RESET;
            }else if(aux.elemento(i,j) == OBSTACULO) {
                std::cout << BG_BLACK << " "  << "  " << RESET;
            }else if(aux.elemento(i,j) == CAMINO_MINIMO) {
                std::cout << BG_RED << RED << " "  << "  " << RESET;
            }else{
                std::cout << BG_GREEN << GREEN << " " << "  " << RESET;
            }
        }
        std::cout << std::endl;
    }
    std::cout << BLUE <<"     0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23"<< std::endl;
    std::cout << RESET<< std::endl;
}

void mapa::mostrar_mapa() {
    matriz aux = this->casilleros_mapa_aurum;
    for(size_t i = 0 ; i < this->filas ; i++){
        if(i < 10){
            std::cout << BLUE << i << "  - ";
        }else{
            std::cout << BLUE << i << " - ";
        }
        for(size_t j = 0 ; j < this->columnas ; j++){

            if(aux.elemento(i,j) == NO_CAMINABLE) {
                std::cout << BG_GRAY << GRAY << " " << "  " << RESET;
            }else if(aux.elemento(i,j) == LOCAL) {
                std::cout << BG_YELLOW << " "  << "  " << RESET;
            }else if(aux.elemento(i,j) == OBSTACULO) {
                std::cout << BG_BLACK << " "  << "  " << RESET;
            }else{
                std::cout << BG_GREEN << GREEN << " " << "  " << RESET;
            }

        }
        std::cout << std::endl;
    }
    std::cout << BLUE <<"     0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23"<< std::endl;
    std::cout << RESET<< std::endl;
}

void mapa::agregar_local(local* a_agregar) {
    size_t y = (size_t)a_agregar->get_coordenada().x();
    size_t x = (size_t)a_agregar->get_coordenada().y();
    this->casilleros_mapa_aurum.elemento(x,y) = 2;
}

bool mapa::consultar_casillero_libre(int x, int y) {
    bool casillero_libre = true;
    int casillero = casilleros_mapa_aurum.elemento(static_cast<size_t>(x), static_cast<size_t>(y));
    if(casillero == NO_CAMINABLE || casillero == LOCAL|| casillero == OBSTACULO){
        casillero_libre = false;
    }
    return casillero_libre;
}

bool mapa::validar_rango(int x, int y) {
    bool rango_valido = true;
    if((x < 0 || x > (int)this->columnas)&&(y < 0 || y > (int)this->filas )){
        rango_valido = false;
    }
    return rango_valido;
}

void mapa::operator=(mapa a_copiar) {
    this->casilleros_mapa_aurum = a_copiar.casilleros_mapa_aurum;
}