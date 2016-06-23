#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <SFML/Graphics.hpp>

/** \brief Interfaz controlador, que representar�a una escena. Atiende los eventos y se encarga de pintar los fotogramas.
*   Los controladores son usados por la clase modelo para que les diga que pintar.
*/


class Controlador
{
    public:

        /** \brief Mediante esta funci�n, se le env�an nuevos eventos al controlador para que los trate y procese
        *   \param Event: El evento a tratar
        */

        virtual void tratarEvento(sf::Event &) = 0;

        /** \brief Esta funci�n ser� llamada por Modelo para refrescar la pantalla, el controlador deber� decirle a Modelo
        *   que cosas pintar
        */

        virtual void refrescarPantalla() = 0;

        /** \brief Destructor virtual para poder ser sobreescrito por sus hijos
        *
        */

        virtual ~Controlador(){}
};

#endif // CONTROLADOR_H
