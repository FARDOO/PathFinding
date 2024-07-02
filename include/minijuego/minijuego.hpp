
#ifndef AYED_TPG_1C2024_MINIJUEGO_HPP
#define AYED_TPG_1C2024_MINIJUEGO_HPP
#include <iostream>
#include "vector"
#include "locales.hpp"
#include "colors.hpp"
#include "grafo.hpp"

class minijuego {
private:
    std::string CIAOMI_A_JUANCETE;
    std::string CIAOMI_A_MANZANA;
    std::string CIAOMI_A_RAMIRO;
    std::string CIAOMI_A_TELE;
    std::string CIAOMI_A_TELMO;
    std::string JUANCETE_A_MANZANA;
    std::string JUANCETE_A_RAMIRO;
    std::string JUANCETE_A_TELE;
    std::string JUANCETE_A_TELMO;
    std::string MANZANA_A_RAMIRO;
    std::string MANZANA_A_TELE;
    std::string MANZANA_A_TELMO;
    std::string RAMIRO_A_TELE;
    std::string RAMIRO_A_TELMO;
    std::string TELE_A_TELMO;
    std::string INTERSECCION_1;
    std::string INTERSECCION_2;
    std::string INTERSECCION_3;
    std::string INTERSECCION_4;
    std::string INTERSECCION_5;
    std::string INTERSECCION_6;
    std::string INTERSECCION_7;
    std::string INTERSECCION_8;
    std::string INTERSECCION_9;
    std::string INTERSECCION_10;
    std::string INTERSECCION_11;
    std::string INTERSECCION_12;
    std::string INTERSECCION_13;
    std::string INTERSECCION_14;
    std::string INTERSECCION_15;
    void resetear_caminos();


    std::vector<std::string> nombres;
public:
    enum indice_locales{
        CIAOMI = 0,
        JUANCETE = 1,
        MANZANA = 2,
        RAMIRO = 3,
        TELE = 4,
        TELMO = 5
    };
    minijuego(std::vector<local*> locales);
    void mostrar_camino_sugerido(grafo grafo_a_procesar);
    void imprimir_aem();

};


#endif //AYED_TPG_1C2024_MINIJUEGO_HPP
