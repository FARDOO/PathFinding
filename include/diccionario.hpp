#ifndef AYED_TPG_1C2024_DICCIONARIO_HPP
#define AYED_TPG_1C2024_DICCIONARIO_HPP

#include <exception>
#include <cstdlib>
#include <vector>
#include <queue>
#include <iostream>
#include "nodo.hpp"

class diccionario_exception : public std::exception {
};


template<typename c, typename T, bool comp(c, c)>
class diccionario {
private:
    // comp es la función de comparación para las claves.
    // La clave debe implementar el operator==().
    nodo<c, T, comp>* raiz;
    std::size_t cantidad_datos;

    void alta(c clave, T dato, nodo<c, T, comp>* nodo);

    nodo<c,T,comp>* baja(c clave, nodo<c, T, comp>* nodo);

    void inorder(nodo<c, T, comp>* nodo, std::vector<T>* datos);

    void preorder(nodo<c, T, comp>* nodo, std::vector<T>* datos);

    void postorder(nodo<c, T, comp>* nodo, std::vector<T>* datos);

    T& buscar_por_clave(nodo<c, T, comp>* nodo, c clave);

    nodo<c,T,comp>* buscar_nodo_minimo(nodo<c, T, comp>* nodo);

    void destruir_nodos(nodo<c, T, comp>* nodo);
public:
    // Constructor.
    diccionario();

    // Pre: La clave no puede existir en el árbol.
    // Post: Agrega el dato asociado a la clave al árbol. Si no hay datos, crea una nueva raíz.
    void alta(c clave, T dato);

    // Pre: -
    // Post: Elimina el dato asociado a la clave del árbol. Si no existe, no hace nada.
    // NOTA: El caso de baja con dos hijos se resuelve con sucesor inmediato. Se puede hacer swap del dato.
    void baja(c clave);

    // Pre: La clave debe existir en el árbol.
    // Post: Devuelve una referencia al valor asociado a la clave.
    T& operator[](c clave);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    std::vector<T> inorder();

    // Pre: -
    // Post: Devuelve el recorrido preorder.
    std::vector<T> preorder();

    // Pre: -
    // Post: Devuelve el recorrido postorder.
    std::vector<T> postorder();

    // Pre: -
    // Post: Devuelve el recorrido en ancho.
    std::vector<T> ancho();

    // Pre: -
    // Post: Ejecuta el método/función en cada valor del árbol.
    /* NOTA: No abusar de este método, está solamente para simplificar algunas cosas,
     * como liberar la memoria de los nodos de usar punteros o imprimir por pantalla el contenido.
     * Pueden usar cualquier recorrido. */
    void ejecutar(void funcion(T));

    // Pre: -
    // Post: Devuelve la cantidad de datos en el árbol.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el árbol está vacío.
    bool vacio();

    // El constructor de copia está deshabilitado.
    diccionario(const diccionario& abb) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const diccionario& abb) = delete;

    // Destructor.
    ~diccionario();
};

template<typename c, typename T, bool (* comp)(c, c)>
diccionario<c, T, comp>::diccionario() {
    this->raiz = nullptr;
    this->cantidad_datos = 0;
}

//ALTA RECURSIVA

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::alta(c clave, T dato) {
    if (this->vacio()){
        this->raiz = new nodo<c, T, comp>(clave, dato);
        this->cantidad_datos++;
    }else{
        alta(clave, dato, this->raiz);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::alta(c clave, T dato, nodo<c, T, comp>* nodo) {
    if (comp(clave , nodo->clave)) {
        if (nodo->hijo_izquierdo == nullptr) {
            nodo->hijo_izquierdo = new ::nodo<c, T, comp>(clave, dato);
            this->cantidad_datos++;
        } else {
            alta(clave, dato, nodo->hijo_izquierdo);
        }
    } else if (comp(nodo->clave,clave)) {
        if (nodo->hijo_derecho == nullptr) {
            nodo->hijo_derecho = new ::nodo<c, T, comp>(clave, dato);
            this->cantidad_datos++;
        } else {
            alta(clave, dato, nodo->hijo_derecho);
        }
    }else{
        throw diccionario_exception();
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::baja(c clave) {
    if (this->vacio()){
        throw diccionario_exception();
    } else{
        baja(clave, this->raiz);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
nodo<c,T,comp>* diccionario<c, T, comp>::baja(c clave, nodo<c, T, comp>* nodo) {

    if (nodo == nullptr) {
    }else if (comp(clave,nodo->clave)) {
        nodo->hijo_izquierdo = baja(clave, nodo->hijo_izquierdo);
    } else if (comp(nodo->clave,clave)) {
        nodo->hijo_derecho = baja(clave, nodo->hijo_derecho);
    } else {
        if (nodo->hijo_izquierdo == nullptr && nodo->hijo_derecho == nullptr) {
            delete nodo;
            this->cantidad_datos--;
            nodo = nullptr;
        } else if (nodo->hijo_izquierdo == nullptr) {
            auto nodo_temporal = nodo->hijo_derecho;
            delete nodo;
            this->cantidad_datos--;
            nodo = nodo_temporal;
        } else if (nodo->hijo_derecho == nullptr) {
            auto nodo_temporal = nodo->hijo_izquierdo;
            delete nodo;
            this->cantidad_datos--;
            nodo = nodo_temporal;
        } else {
            auto nodo_minimo = buscar_nodo_minimo(nodo->hijo_derecho);
            nodo->clave = nodo_minimo->clave;
            nodo->dato = nodo_minimo->dato;
            nodo->hijo_derecho = baja(nodo_minimo->clave, nodo->hijo_derecho);
        }
    }
    return nodo;
}

template<typename c, typename T, bool (* comp)(c, c)>
nodo<c,T,comp>* diccionario<c, T, comp>::buscar_nodo_minimo(nodo<c, T, comp>* nodo) {
    while (nodo->hijo_derecho != nullptr) {
        nodo = nodo->hijo_izquierdo;
    }
    return nodo;
}

template<typename c, typename T, bool (* comp)(c, c)>
T& diccionario<c, T, comp>::operator[](c clave) {
    if(this->vacio()) {
        throw diccionario_exception();
    }else{
        return this->buscar_por_clave(this->raiz, clave);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
T& diccionario<c, T, comp>::buscar_por_clave(nodo<c, T, comp> *nodo, c clave) {

    if (nodo == nullptr) {
        throw diccionario_exception();
    }

    if (comp(clave,nodo->clave)) {
        return buscar_por_clave(nodo->hijo_izquierdo,clave);
    } else if (comp(nodo->clave,clave)) {
        return buscar_por_clave(nodo->hijo_derecho,clave);
    } else {
        return nodo->dato;
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::inorder() {
    std::vector<T>* datos = new std::vector<T>();
    inorder(this->raiz, datos);
    std::vector<T> datos_temporales = *datos;
    delete datos;
    return datos_temporales;
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::inorder(nodo<c, T, comp>* nodo, std::vector<T>* datos) {
    if (nodo != nullptr) {
        inorder(nodo->hijo_izquierdo, datos);
        datos->push_back(nodo->dato);
        inorder(nodo->hijo_derecho, datos);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::preorder() {
    std::vector<T>* datos = new std::vector<T>();
    preorder(this->raiz, datos);
    std::vector<T> datos_temporales = *datos;
    delete datos;
    return datos_temporales;
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::preorder(nodo<c, T, comp>* nodo, std::vector<T>* datos) {
    if (nodo != nullptr) {
        datos->push_back(nodo->dato);
        preorder(nodo->hijo_izquierdo, datos);
        preorder(nodo->hijo_derecho, datos);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::postorder() {
    auto* datos = new std::vector<T>();
    postorder(this->raiz, datos);
    std::vector<T> datos_temporales = *datos;
    delete datos;
    return datos_temporales;
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::postorder(nodo<c, T, comp>* nodo, std::vector<T>* datos) {
    if (nodo != nullptr) {
        postorder(nodo->hijo_izquierdo, datos);
        postorder(nodo->hijo_derecho, datos);
        datos->push_back(nodo->dato);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::ancho() {
    std::vector<T> vec;
    std::queue<nodo<c,T,comp>*> cola;
    if (raiz == nullptr) {
        throw diccionario_exception();
    }
    cola.push(raiz);
    while (!cola.empty()) {
        nodo<c,T,comp>* actual = cola.front();
        cola.pop();

        vec.push_back(actual->dato);

        if (actual->hijo_izquierdo != nullptr) {
            cola.push(actual->hijo_izquierdo);
        }
        if (actual->hijo_derecho != nullptr) {
            cola.push(actual->hijo_derecho);
        }
    }
    return vec;
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::ejecutar(void (* funcion)(T)) {
    std::cout << "EJECUTO";
}

template<typename c, typename T, bool (* comp)(c, c)>
std::size_t diccionario<c, T, comp>::tamanio() {
    return cantidad_datos;
}

template<typename c, typename T, bool (* comp)(c, c)>
bool diccionario<c, T, comp>::vacio() {
    return (this->raiz == nullptr);
}

template<typename c, typename T, bool (* comp)(c, c)>
diccionario<c, T, comp>::~diccionario() {
    destruir_nodos(raiz);
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::destruir_nodos(nodo<c,T,comp>* nodo) {

    if (nodo != nullptr) {
        destruir_nodos(nodo->hijo_izquierdo);
        destruir_nodos(nodo->hijo_derecho);
        delete nodo;
    }
}

#endif