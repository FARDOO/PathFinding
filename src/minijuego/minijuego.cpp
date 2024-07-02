#include "minijuego.hpp"
using namespace std;
minijuego::minijuego(std::vector<local *> locales) {
    for (auto local : locales){
        nombres.push_back(local->get_nombre());
    }
    resetear_caminos();
}
void minijuego::resetear_caminos() {
    CIAOMI_A_JUANCETE = BLACK;
    CIAOMI_A_MANZANA = BLACK;
    CIAOMI_A_RAMIRO = BLACK;
    CIAOMI_A_TELE = BLACK;
    CIAOMI_A_TELMO = BLACK;
    JUANCETE_A_MANZANA = BLACK;
    JUANCETE_A_RAMIRO = BLACK;
    JUANCETE_A_TELE = BLACK;
    JUANCETE_A_TELMO = BLACK;
    MANZANA_A_RAMIRO = BLACK;
    MANZANA_A_TELE = BLACK;
    MANZANA_A_TELMO = BLACK;
    RAMIRO_A_TELE = BLACK;
    RAMIRO_A_TELMO = BLACK;
    TELE_A_TELMO = BLACK;
    INTERSECCION_1 = BLACK;
    INTERSECCION_2 = BLACK;
    INTERSECCION_3 = BLACK;
    INTERSECCION_4 = BLACK;
    INTERSECCION_5 = BLACK;
    INTERSECCION_6 = BLACK;
    INTERSECCION_7 = BLACK;
    INTERSECCION_8 = BLACK;
    INTERSECCION_9 = BLACK;
    INTERSECCION_10 = BLACK;
    INTERSECCION_11 = BLACK;
    INTERSECCION_12 = BLACK;
    INTERSECCION_13 = BLACK;
    INTERSECCION_14 = BLACK;
    INTERSECCION_15 = BLACK;

}


void minijuego::imprimir_aem() {
cout<<"                          "                           "┌"                                                                                                                 "────────────────────────┐  ┌─"                                  "───────────────────────"                                                                                           "┐                          "<<endl;
cout << "            " << CIAOMI_A_MANZANA << "┌──────────"         "───┤      " << RESET << nombres[0] << "      " << CIAOMI_A_JUANCETE << "├──┤  " << RESET << nombres[1] << "   " << JUANCETE_A_RAMIRO << "├─────"                                           "────────┐" << RESET << "            " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "             └─────"                          "" << CIAOMI_A_TELE << "┬" << RESET << "─────" << CIAOMI_A_TELMO << "┬" << RESET << "────────" << CIAOMI_A_RAMIRO << "┬" << RESET << "───┘  └" << JUANCETE_A_MANZANA << "┬" << RESET << "───────────" << JUANCETE_A_TELE << "┬" << RESET << "─────" << JUANCETE_A_TELMO << "┬" << RESET << "─────┘             " << JUANCETE_A_RAMIRO << "│" << RESET << "            " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "                   "                          "" << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "        " << CIAOMI_A_RAMIRO << "│" << RESET << "       " << JUANCETE_A_MANZANA << "│" << RESET << "           " << JUANCETE_A_TELE << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "                   " << JUANCETE_A_RAMIRO << "│" << RESET << "           " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "          " << JUANCETE_A_MANZANA << "┌──"                              "──────"<< INTERSECCION_1 << "┼" << JUANCETE_A_MANZANA <<"───"                           "──"<< INTERSECCION_4 << "┼" << JUANCETE_A_MANZANA <<"───"                          "─────"<< INTERSECCION_11 << "┼" << JUANCETE_A_MANZANA <<"───"                        "────┘" << RESET << "           " << JUANCETE_A_TELE << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "                   " << JUANCETE_A_RAMIRO << "│" << RESET << "           " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "          " << JUANCETE_A_MANZANA << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "        " << CIAOMI_A_RAMIRO << "│" << RESET << "        "                        "           " << JUANCETE_A_TELE << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "                   " << JUANCETE_A_RAMIRO << "│" << RESET << "           " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "          " << JUANCETE_A_MANZANA << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "        " << CIAOMI_A_RAMIRO << "└────────"                                                     "───────────"<< INTERSECCION_7 << "┼" << CIAOMI_A_RAMIRO <<"────"                                                                        "─"<< INTERSECCION_13 << "┼" << CIAOMI_A_RAMIRO <<"─"                           "───────┐" << RESET << "          " << JUANCETE_A_RAMIRO << "│" << RESET << "           " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "          " << JUANCETE_A_MANZANA << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "                 "                                                    "           " << JUANCETE_A_TELE << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "        " << CIAOMI_A_RAMIRO << "│" << RESET << "          " << JUANCETE_A_RAMIRO << "│" << RESET << "            " << endl;
cout << "            " << CIAOMI_A_MANZANA << "│" << RESET << "          " << JUANCETE_A_MANZANA << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "  " << JUANCETE_A_TELE << "┌──────────────"                                                    "───────────┘" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "        " << CIAOMI_A_RAMIRO << "│" << RESET << "          " << JUANCETE_A_RAMIRO << "│" << RESET << "           " << endl;
cout << "┌───────────" << CIAOMI_A_MANZANA << "┴" << RESET << "──────────" << JUANCETE_A_MANZANA << "┴" << RESET << "─┐      " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "  " << JUANCETE_A_TELE << "│" << RESET << "              "                                                    "                 " << JUANCETE_A_TELMO << "│" << RESET << "      ┌─" << CIAOMI_A_RAMIRO << "┴" << RESET << "──────────" << JUANCETE_A_RAMIRO << "┴" << RESET << "────"    "───────┐" << endl;
cout << "│    " << nombres[2] <<"   "                              "" << MANZANA_A_RAMIRO << "├─────"/***************/"─"<< INTERSECCION_2 << "┼" << MANZANA_A_RAMIRO <<"───"/*************************/"──"<< INTERSECCION_5 << "┼" << MANZANA_A_RAMIRO <<"─"                           "─"<< INTERSECCION_8 << "┼" << MANZANA_A_RAMIRO <<"──────────────"                                                                                                                              "─────────────────"<< INTERSECCION_14 << "┼" << MANZANA_A_RAMIRO <<"───"          "───┤" << RESET << "    " << RESET << nombres[3] << "     │" << endl;
cout << "└───────────" << MANZANA_A_TELE << "┬" << RESET << "──────────" << MANZANA_A_TELMO << "┬" << RESET << "─┘      " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "│" << RESET << "  " << JUANCETE_A_TELE << "│" << RESET << "              "                                                                 "                 " << JUANCETE_A_TELMO << "│" << RESET << "      └─" << RAMIRO_A_TELE << "┬" << RESET << "──────────" << RAMIRO_A_TELMO << "┬" << RESET << "────""───────┘" << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "          " << MANZANA_A_TELMO << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "     " << CIAOMI_A_TELMO << "└─"                           "─"<< INTERSECCION_9 << "┼" << CIAOMI_A_TELMO <<"──────────────"                                                                                                  "───────────┐" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "        " << RAMIRO_A_TELE << "│" << RESET << "          " << RAMIRO_A_TELMO << "│" << RESET << "            " << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "          " << MANZANA_A_TELMO << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "    "                           "    " << JUANCETE_A_TELE << "│" << RESET << "              "                                                                     "           " << CIAOMI_A_TELMO << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "        " << RAMIRO_A_TELE << "│" << RESET << "          " << RAMIRO_A_TELMO << "│" << RESET << "           " << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "          " << MANZANA_A_TELMO << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "    "                           "    " << JUANCETE_A_TELE << "│" << RESET << "       " << RAMIRO_A_TELE << "┌──────"                                                                    "───────────"<< INTERSECCION_6 << "┼" << RAMIRO_A_TELE <<"─────"                          << INTERSECCION_15 << "┼" << RAMIRO_A_TELE <<                             "────────┘" << RESET << "          " << RAMIRO_A_TELMO << "│" << RESET << "           " << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "          " << MANZANA_A_TELMO << "│" << RESET << "        " << CIAOMI_A_TELE << "│" << RESET << "    "                           "    " << JUANCETE_A_TELE << "│" << RESET << "       " << RAMIRO_A_TELE << "│" << RESET << "      "                                       "           " << CIAOMI_A_TELMO << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "                   " << RAMIRO_A_TELMO << "│" << RESET << "            " << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "          " << MANZANA_A_TELMO << "└─"                            "───────"<< INTERSECCION_3 << "┼" << MANZANA_A_TELMO <<"────"                                                        "────"<< INTERSECCION_10 << "┼" << MANZANA_A_TELMO <<"────"                            "───"<< INTERSECCION_12 << "┼" << MANZANA_A_TELMO <<"──────"                                       "──┐" << RESET << "        " << CIAOMI_A_TELMO << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "                   " << RAMIRO_A_TELMO << "│" << RESET << "           " << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "            "                          "       " << CIAOMI_A_TELE << "│" << RESET << "    "                           "    " << JUANCETE_A_TELE << "│" << RESET << "       " << RAMIRO_A_TELE << "│" << RESET << "      "           "  " << MANZANA_A_TELMO << "│" << RESET << "        " << CIAOMI_A_TELMO << "│" << RESET << "     " << JUANCETE_A_TELMO << "│" << RESET << "                   " << RAMIRO_A_TELMO << "│" << RESET << "            " << endl;
cout << "            " << MANZANA_A_TELE << "│" << RESET << "            "                          " ┌─────" << CIAOMI_A_TELE << "┴" << RESET << "────"                           "────" << JUANCETE_A_TELE << "┴" << RESET << "───────" << RAMIRO_A_TELE << "┴" << RESET << "─┐  ┌─"           "──" << MANZANA_A_TELMO << "┴" << RESET << "────────" << CIAOMI_A_TELMO << "┴" << RESET << "─────" << JUANCETE_A_TELMO << "┴" << RESET << ""        "─────┐             " << RAMIRO_A_TELMO << "│" << RESET << "            " << endl;
cout << "            " << MANZANA_A_TELE << "└──────────"/***********************************/"───┤" << RESET << "       " << nombres[4] << "        " << TELE_A_TELMO << "├──┤   " << RESET << nombres[5] << "   " << RAMIRO_A_TELMO << "├─────"                                     "────────┘" << RESET << "            " << endl;
cout<<"                         "                                                       " └───────────────────────"/******************************************************************************************************************/"─┘  └─"                                                                                                          "───────────────────────┘                          "<<endl;
}

void minijuego::mostrar_camino_sugerido(grafo grafo_a_procesar) {
    auto aristas = grafo_a_procesar.obtener_aem();
    for (auto arista : aristas){
        size_t aux1 = arista.obtener_vertices().first;
        size_t aux2 = arista.obtener_vertices().second;
        switch (aux1){
            case CIAOMI:
                switch (aux2) {
                    case JUANCETE:
                        CIAOMI_A_JUANCETE = RED;
                        break;
                    case MANZANA:
                        CIAOMI_A_MANZANA = RED;
                        break;
                    case RAMIRO:
                        CIAOMI_A_RAMIRO = RED;

                        INTERSECCION_7 = RED;
                        INTERSECCION_11 = RED;
                        INTERSECCION_13 = RED;
                        break;
                    case TELE:
                        CIAOMI_A_TELE = RED;

                        INTERSECCION_1 = RED;
                        INTERSECCION_2 = RED;
                        INTERSECCION_3 = RED;
                        break;
                    case TELMO:
                        CIAOMI_A_TELMO = RED;

                        INTERSECCION_4 = RED;
                        INTERSECCION_5 = RED;
                        INTERSECCION_6 = RED;
                        INTERSECCION_9 = RED;
                        break;
                }
                break;
            case JUANCETE:
                switch (aux2) {
                    case MANZANA:
                        JUANCETE_A_MANZANA = RED;

                        INTERSECCION_1 = RED;
                        INTERSECCION_4 = RED;
                        INTERSECCION_11 = RED;
                        break;
                    case RAMIRO:
                        JUANCETE_A_RAMIRO = RED;
                        break;
                    case TELE:
                        JUANCETE_A_TELE = RED;

                        INTERSECCION_7 = RED;
                        INTERSECCION_8 = RED;
                        INTERSECCION_9 = RED;
                        INTERSECCION_10 = RED;
                        break;
                    case TELMO:
                        JUANCETE_A_TELMO = RED;

                        INTERSECCION_13 = RED;
                        INTERSECCION_14 = RED;
                        INTERSECCION_15 = RED;
                        break;
                }
                break;
            case MANZANA:
                switch (aux2) {
                    case RAMIRO:
                        MANZANA_A_RAMIRO = RED;

                        INTERSECCION_2 = RED;
                        INTERSECCION_5 = RED;
                        INTERSECCION_8 = RED;
                        INTERSECCION_14 = RED;
                        break;
                    case TELE:
                        MANZANA_A_TELE = RED;
                        break;
                    case TELMO:
                        MANZANA_A_TELMO = RED;

                        INTERSECCION_3 = RED;
                        INTERSECCION_10 = RED;
                        INTERSECCION_12 = RED;
                        break;
                }
                break;
            case RAMIRO:
                switch (aux2) {
                    case TELE:
                        RAMIRO_A_TELE = RED;

                        INTERSECCION_6 = RED;
                        INTERSECCION_12 = RED;
                        INTERSECCION_15 = RED;
                        break;
                    case TELMO:
                        RAMIRO_A_TELMO = RED;
                        break;
                }
                break;
            case TELE:
                TELE_A_TELMO = RED;
                break;
        }

    }
    imprimir_aem();
    resetear_caminos();

}



