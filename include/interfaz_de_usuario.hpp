#ifndef AYED_TPG_1C2024_INTERFAZ_DE_USUARIO_HPP
#define AYED_TPG_1C2024_INTERFAZ_DE_USUARIO_HPP
#include "controlador_juego.hpp"
class interfaz_de_usuario{
private:
    controlador_juego juego;
    //pre:-
    //pos:muesta por pantalla el menu de realizar pedidos
    void menu_realizar_pedidos();
    //pre:-
    //pos:valida que el numero ingresado este entre el rango de 'mayor' y 'menor'
    int validar_rango_entre(int menor, int mayor, std::string mensaje);
    //pre:-
    //pos:valida que el dato ingresado por teclado sea un numero
    int validar_numero();
public:
    //pre:-
    //pos:inicia el juego mostrando el menu principal
    void iniciar();
};

#endif //AYED_TPG_1C2024_INTERFAZ_DE_USUARIO_HPP
