#ifndef AYED_TPG_1C2024_HEAP_HPP
#define AYED_TPG_1C2024_HEAP_HPP

#include <vector>
#include <cstdlib>
#include <exception>

class heap_exception : public std::exception {
};



template<typename T, bool comp(T, T)>
class heap {
private:
    std::vector<T> datos;

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Intercambia de lugar los datos de los indices indicados.
    void swap(size_t indice_1, size_t indice_2);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Realiza un "upheap" sobre los índices indicados.
    // (El dato "sube" en el heap.)
    void upheap(size_t& indice);

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Realiza un "downheap" sobre el índice indicado.
    // (El dato "baja" en el heap, intercambiándose con el menor/mayor dato.)
    void downheap(size_t& indice);

    // NOTA: No es necesario que lancen excepciones en estos métodos porque son privados.
    // Deberían siempre asegurar que los índices pasados por parámetros son válidos.
    // Consideren cada caso con detenimiento.
    // Adicionalmente, tengan cuidado con el casteo de las variables, porque son size_t.
    // Hacer, por ejemplo, size_t i = 0; i - 1; produce un underflow.
public:
    // Constructor.
    heap();

    // Pre: -
    // Post: Agrega el dato al heap.
    void alta(T dato);

    // Pre: El heap no puede estar vacío.
    // Post: Elimina y devuelve el primer dato.
    T baja();

    // Método para el informe de complejidad algorítmica. Devuelve la cantidad de "upheaps".
    size_t alta_complejidad(T dato);

    // Método para el informe de complejidad algorítmica. Devuelve la cantidad de "downheaps".
    size_t baja_complejidad();

    // Pre: El heap no puede estar vacío.
    // Post: Devuelve el primer dato.
    T primero();

    // Pre: -
    // Post: Devuelve true si el heap está vacío.
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el heap.
    size_t tamanio();

    // Destructor.
    ~heap();
};

template<typename T, bool (* comp)(T, T)>
heap<T, comp>::heap() {}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::swap(size_t indice_1, size_t indice_2) {
    T temp = datos[indice_1];
    datos[indice_1] = datos[indice_2];
    datos[indice_2] = temp;
}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::upheap(size_t& indice) {
    while (indice > 0) {
        size_t parent = (indice - 1) / 2;
        if (comp(datos[indice], datos[parent])) {
            swap(indice, parent);
            indice = parent;
        } else {
            break;
        }
    }
}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::downheap(size_t& indice) {
    size_t size = datos.size();
    while (2 * indice + 1 < size) {
        size_t left = 2 * indice + 1;
        size_t right = 2 * indice + 2;
        size_t smallest = left;

        if (right < size && comp(datos[right], datos[left])) {
            smallest = right;
        }

        if (comp(datos[smallest], datos[indice])) {
            swap(indice, smallest);
            indice = smallest;
        } else {
            break;
        }
    }
}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::alta(T dato) {
    datos.push_back(dato);
    size_t indice = datos.size() - 1;
    upheap(indice);
}

template<typename T, bool (* comp)(T, T)>
T heap<T, comp>::baja() {
    if (datos.empty()) {
        throw heap_exception();
    }

    T top = datos[0];
    datos[0] = datos.back();
    datos.pop_back();

    if (!datos.empty()) {
        size_t indice = 0;
        downheap(indice);
    }
    return top;
}

template<typename T, bool (* comp)(T, T)>
size_t heap<T, comp>::alta_complejidad(T dato) {
    datos.push_back(dato);
    size_t indice = datos.size() - 1;
    size_t upheaps = 0;

    while (indice > 0) {
        size_t parent = (indice - 1) / 2;
        if (comp(datos[indice], datos[parent])) {
            swap(indice, parent);
            indice = parent;
            upheaps++;
        } else {
            break;
        }
    }

    return upheaps;
}

template<typename T, bool (* comp)(T, T)>
size_t heap<T, comp>::baja_complejidad() {
    if (datos.empty()) {
        throw heap_exception();
    }

    datos[0] = datos.back();
    datos.pop_back();

    size_t indice = 0;
    size_t downheaps = 0;

    while (2 * indice + 1 < datos.size()) {
        size_t left = 2 * indice + 1;
        size_t right = 2 * indice + 2;
        size_t smallest = left;

        if (right < datos.size() && comp(datos[right], datos[left])) {
            smallest = right;
        }

        if (comp(datos[smallest], datos[indice])) {
            swap(indice, smallest);
            indice = smallest;
            downheaps++;
        } else {
            break;
        }
    }

    return downheaps;
}

template<typename T, bool (* comp)(T, T)>
T heap<T, comp>::primero() {
    if (datos.empty()) {
        throw heap_exception();
    }
    return datos[0];
}

template<typename T, bool (* comp)(T, T)>
bool heap<T, comp>::vacio() {
    return datos.empty();
}

template<typename T, bool (* comp)(T, T)>
size_t heap<T, comp>::tamanio() {
    return datos.size();
}

template<typename T, bool (* comp)(T, T)>
heap<T, comp>::~heap() {}

#endif