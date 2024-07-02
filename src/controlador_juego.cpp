//
// Created by David on 21/6/2024.
//
#include "controlador_juego.hpp"
#include "colors.hpp"
#include <random>
#include <sstream>



using namespace std;

controlador_juego::controlador_juego(): minijuego1({}) {
    this->locales = new diccionario<string,local*,comparar>();
    this->mapa_callejon_aurum = new mapa();
    this->grafo_pedidos = generar_grafo_conexo();
}

bool comparar(std::string local_a, std::string local_b) {
    bool devolver = true;
    if (local_a.compare(local_b) > 0){
        devolver = false;
    }
    return devolver;
}

int distanciaManhattan(vertice* origen, vertice* destino) {
    coordenada coordenada_resultado = *origen - *destino;
    return std::abs(coordenada_resultado.x() ) + std::abs(coordenada_resultado.y() );
}



bool controlador_juego::agregar_local(local* nuevo_local) {
    if(nuevo_local == nullptr) {
        throw controlador_juego_exeption();
    }else {
        unsigned long y = (unsigned long)nuevo_local->get_coordenada().x();
        unsigned long x = (unsigned long)nuevo_local->get_coordenada().y();
        bool rango_valido = true;
        if(!mapa_callejon_aurum->validar_rango((int)x,(int)y) || !mapa_callejon_aurum->consultar_casillero_libre((int)x,(int)y)){
            rango_valido = false;
        }else{
            this->locales->alta(nuevo_local->get_nombre(),nuevo_local);
            this->mapa_callejon_aurum->agregar_local(nuevo_local);
        }
        return rango_valido;
    }

}

void controlador_juego::agregar_pedido(local *origen, local *destino, size_t peso) {
    if (origen == nullptr || destino == nullptr){
        throw controlador_juego_exeption();
    }else{
        origen->crear_pedido(destino, peso);
        size_t indice_origen = definir_indice(origen->get_coordenada());
        size_t indice_destino = definir_indice(destino->get_coordenada());

        grafo_pedidos.aumentar_arista(indice_origen,indice_destino,1);
        grafo_pedidos.aumentar_arista(indice_destino,indice_origen,1);
    }
}

void controlador_juego::mostrar_callejo_aurum() {
    this->mapa_callejon_aurum->mostrar_mapa();
}

void controlador_juego::realizar_pedidos(local* local) {
    size_t tamanio;
    tamanio = local->get_pedidos_local().tamanio();
    if (!local->get_pedidos_local().vacio()) {
        for (size_t i = 0 ; i < tamanio ;i++ ) {
            this->realizar_pedido(local);
        }
    }else{
        cout << endl;
        cout << "Store without available orders."  << endl;
    }
}

void controlador_juego::realizar_pedidos_de_mayor_prioridad(){
    local* local_a_comparar = nullptr;
    size_t prioridad = 0;
    std::vector<local*> mis_locales;
    mis_locales = this->locales->inorder();
    size_t mayor_prioridad_local;

    for (local* local:mis_locales) {
        if(!local->get_pedidos_local().vacio()){
            mayor_prioridad_local = local->get_pedidos_local().primero().get_prioridad_pedido();
            if(mayor_prioridad_local > prioridad ){
                local_a_comparar = local;
                prioridad = mayor_prioridad_local;
            }
        }
    }
    if(local_a_comparar == nullptr){
        cout << "Store without available orders." << endl;
    }else{
        cout << "ORDER WITH HIGHEST PRIORITY " << endl;
        cout << endl;
        this->realizar_pedido(local_a_comparar);

    }
}

void controlador_juego::realizar_pedido(local* local){
    heap<pedido, comparar_prioridad> pedidos_a_realizar = local->get_pedidos_local();
    vector<coordenada> obstaculos = this->generar_obstaculos();
    pedido pedido_a_entregar = local->get_pedidos_local().primero();
    coordenada origen(pedido_a_entregar.get_origen());
    coordenada destino(pedido_a_entregar.get_destino().x(),pedido_a_entregar.get_destino().y());
    cout << "Origin " << BG_BLUE << "   " << RESET << " : " << origen.x() << " - " << origen.y() << endl;
    cout << "Destination " << BG_MAGENTA << "   " << RESET << " : " << destino.x() << " - " << destino.y() << endl;
    cout << "Order priority: " << pedido_a_entregar.get_prioridad_pedido() << endl;
    std::stack<coordenada> camino;
    a_estrella camino_minimo;
    this->mapa_callejon_aurum->casilleros_mapa_aurum.elemento((size_t)origen.y(),(size_t)origen.x()) = mapa::CAMINO_LIBRE;
    this->mapa_callejon_aurum->casilleros_mapa_aurum.elemento((size_t)destino.y(),(size_t)destino.x()) = mapa::CAMINO_LIBRE;
    do{
        this->colocar_obstaclos_en_mapa(obstaculos);
        camino = camino_minimo.obtener_camino_minimo(origen,
                                                     destino,
                                                     *this->mapa_callejon_aurum,
                                                     distanciaManhattan);
        if(camino.empty()){
            cout << endl;
            cout << "NO PATH FOUND, RETRYING " << endl;
            this->mapa_callejon_aurum->mostrar_mapa();
            this->quitar_obstaculos(obstaculos);
            obstaculos = this->generar_obstaculos();
            cout << endl;
        }
    }while(camino.empty());
    this->mapa_callejon_aurum->casilleros_mapa_aurum.elemento((size_t)origen.y(),(size_t)origen.x()) = mapa::LOCAL;
    this->mapa_callejon_aurum->casilleros_mapa_aurum.elemento((size_t)destino.y(),(size_t)destino.x()) = mapa::LOCAL;
    this->mapa_callejon_aurum->mostrar_camino(camino);
    local->borrar_pedido_local();
    size_t indice_origen = definir_indice(origen);
    size_t indice_destino = definir_indice(destino);
    grafo_pedidos.aumentar_arista(indice_origen,indice_destino,-1);
    grafo_pedidos.aumentar_arista(indice_destino,indice_origen,-1);
    for (auto& obstaculo : obstaculos) {
        cout << "Obstacle: " << obstaculo.first<<" - "<< obstaculo.second << endl;
    }
    cout << endl;
    cout << endl;
    this->quitar_obstaculos(obstaculos);
}


std::vector<coordenada> controlador_juego::generar_obstaculos() {
    std::vector<coordenada> obstaculos;
    bool generados = false;
    std::random_device rd; // Fuente de entropía
    std::mt19937 gen(rd()); // Generador Mersenne Twister
    std::uniform_int_distribution<> columna_aleatorio(0, 17); // Distribución uniforme en el rango
    std::uniform_int_distribution<> fila_aleatorio(0, 23);
    std::uniform_int_distribution<> obstaculos_aleatorios(0,4);
    auto cantidad_obstaculos = (size_t)obstaculos_aleatorios(gen);
    while(!generados){
        if(obstaculos.size() != cantidad_obstaculos) {
            int fila = fila_aleatorio(gen);
            int columna = columna_aleatorio(gen);
            if(this->mapa_callejon_aurum->consultar_casillero_libre(columna,fila)) {
                coordenada posicion_obstaculo(fila,columna);
                obstaculos.push_back(posicion_obstaculo);
            }
        }else {
            generados = true;
        }
    }
    return obstaculos;
}

void controlador_juego::colocar_obstaclos_en_mapa(std::vector<coordenada> obstaculos) {
    for (auto& obstaculo : obstaculos) {
        this->mapa_callejon_aurum->casilleros_mapa_aurum.elemento((size_t)obstaculo.y(),(size_t)obstaculo.x()) = mapa::OBSTACULO;
    }
}

void controlador_juego::quitar_obstaculos(std::vector<coordenada> obstaculos) {
    for (auto& obstaculo : obstaculos) {
        this->mapa_callejon_aurum->casilleros_mapa_aurum.elemento((size_t)obstaculo.y(),(size_t)obstaculo.x()) = mapa::CAMINO_LIBRE;
    }
}

void controlador_juego::generar_locales() {
    local* l1 = new local("BRANCH 1", 150, 0, 9);
    local* l2 = new local("BRANCH 2", 14, 19, 6);
    local* l3 = new local("BRANCH 3", 12, 5, 17);
    local* l4 = new local("BRANCH 4", 17, 14, 12);
    local* l5 = new local("BRANCH 5", 17, 5, 1);
    local* l6 = new local("BRANCH 6", 17, 5, 6);
    this->agregar_local(l1);
    this->agregar_local(l2);
    this->agregar_local(l3);
    this->agregar_local(l4);
    this->agregar_local(l5);
    this->agregar_local(l6);
    minijuego1 = minijuego(locales->inorder());
}



void controlador_juego::mostrar_locales() {
    vector<local*> mis_locales = this->locales->inorder();
    string nombre_local;
    size_t posicion = 1;
    cout << "- STORES -"<< endl;
    cout << endl;
    for(local* local : mis_locales){
        cout << posicion << " - " << local->get_nombre()
        << "(" << local->get_coordenada().x() << "," << local->get_coordenada().y() <<")"
        << "  N° of orders: "<<local->get_pedidos_local().tamanio() << endl;
        posicion++;
    }
}

void controlador_juego::agregar_pedidos_aleatorios() {

    size_t cantidad_pedidos = static_cast<size_t>(rand() % 5 + 1);
    vector<local*> mis_locales = this->locales->inorder();
    for (size_t i = 0; i < cantidad_pedidos; ++i) {
        size_t origen_index = static_cast<unsigned long>(rand()) % mis_locales.size();
        size_t destino_index;
        do {
            destino_index = static_cast<unsigned long>(rand()) % mis_locales.size();
        } while (origen_index == destino_index);
        size_t peso = static_cast<size_t>(rand() % 100 + 1); // Peso aleatorio entre 1 y 100
        cout << "Order added with origin: " << mis_locales[origen_index]->get_nombre()
        << "(" <<mis_locales[origen_index]->get_coordenada().x() << "," << mis_locales[origen_index]->get_coordenada().y()<< ") "
        << " destination: "<< mis_locales[destino_index]->get_nombre() << "(" <<mis_locales[destino_index]->get_coordenada().x() << ","
        << mis_locales[destino_index]->get_coordenada().y()<< ") "<<  "Weight: " << peso << endl;
        this->agregar_pedido(mis_locales[origen_index], mis_locales[destino_index], peso);
    }
}

local* controlador_juego::seleccionar_local(size_t posicion) {
    return this->locales->inorder()[posicion];
}

controlador_juego::~controlador_juego() {

    vector<local*> a_borrar = this->locales->inorder();
    int tamanio = (int)a_borrar.size();
    for(int i = 0 ; i < tamanio ; i++){
       delete a_borrar[static_cast<unsigned long>(i)];
    }
    delete locales;
    delete mapa_callejon_aurum;
}

void controlador_juego::mostrar_minijuego() {
    minijuego1.mostrar_camino_sugerido(grafo_pedidos);
}

grafo controlador_juego::generar_grafo_conexo() {
        size_t cantidad_locales=6;
    auto aux = grafo(cantidad_locales);
    for(size_t i = 0; i < cantidad_locales - 1; i++){
        for(size_t j = i + 1; j < cantidad_locales; j++){
            aux.modificar_arista(i,j,0);
            aux.modificar_arista(j,i,0);
        }
    }
    return aux;
}

size_t controlador_juego::definir_indice(coordenada coordenada_local) {
    size_t indice;
    if(coordenada_local == coordenada(5,17)){
        indice = minijuego::indice_locales::CIAOMI;
    }else if(coordenada_local == coordenada(19,6)){
        indice = minijuego::indice_locales::JUANCETE;
    }else if(coordenada_local == coordenada(14,12)){
        indice = minijuego::indice_locales::MANZANA;
    }else if(coordenada_local == coordenada(0,9)){
        indice = minijuego::indice_locales::RAMIRO;
    }else if(coordenada_local == coordenada(5,1)){
        indice = minijuego::indice_locales::TELE;
    }else{
        indice = minijuego::indice_locales::TELMO;
    }
    return indice;
}
