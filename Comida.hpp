#ifndef COMIDA_H
#define COMIDA_H
#include "Nivel.hpp"
#include <vector>

#include <SFML/Graphics.hpp>

/** \brief Representa a una comida en el campo, se encarga de generarla y estar atento a si el jugador le come
*
*/

class Comida
{
    public:

        /** \brief Construye la comida dado el nivel y una referencia a la cola del jugador, se utilizan para no poner
        *   la comida en una pared o en la misma cola del jugador.
        *
        *   \param Nivel: Referencia al nivel actual.
        *   \param cola: Referencia a la cola del jugador
        */

		Comida(const Nivel&,const std::vector<sf::Sprite> &cola);

		/** \brief Comprueba si la posición dada coincide con la comida, si es así devuelve true y genera una nueva posición para la comida
        *
        *   \param pos: Posición, presuntamente del jugador.
        *   \return Devuelve true si le come y false sino.
        */

        bool teComo(sf::Vector2f pos);


		/** \brief Obtiene el sprite de la comida para su dibujado
        */

        const sf::Sprite& getDibujo() const { return comida;}
    private:

        /** \brief Sprite de la comida, contiene tanto el dibujo como su posición
        */

        sf::Sprite comida;

        /** \brief Textura de la comida
        */

        sf::Texture textura_comida;

        /** \brief Referencia al nivel actual para evitar poner una comida en una pared
        */

        const Nivel &nivel;

        /** \brief Referencia a la cola del jugador para evitar poner una comida en la cola del jugador
        */

		const std::vector<sf::Sprite> &cola_jugador;

        /** \brief Coloca una nueva comida en una posición aleatoria (rand()), evitando poner en paredes o en la cola
            del jugador
        */

        void ponerComida();

        /** \brief Determina si la posición actual del jugador hace colisión con una pared o con la cola del jugador,
            utilizado por ponercomida() para evitar ponerla en esas posiciones

            \return True si hay colisión, false si no la hay
        */

		bool colision();

};

#endif // COMIDA_H
