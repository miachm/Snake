#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "AlmacenDeAjustes.hpp"

/** \brief Simboliza al jugador, es decir la serpiente. Lo mueve, lo hace crecer y mantiene su dibujo
*
*/

class Jugador
{
    public:

        /** \brief Construye una serpiente dado sus posiciones_iniciales y a donde se dirige inicialmente
        *
        *   \param pos_inicial: Vector con la posici�n inicial de la cola, normalmente esto vendr� definido en el nivel.
        *   \param sf::Vector2f: A donde se dirige la serpiente inicialmente (arriba,abajo,izquierda o derecha).
        */

        Jugador(const std::vector<sf::Vector2i> & pos_inicial,sf::Vector2f);


        /** \brief Mueve la posici�n de la serpiente, no tiene en cuenta las colisiones, que ser� responsabilidad de otra
        *    clase (MotorDelJuego)
        */

        void mover();

        /** \brief Cambia la direcci�n donde apunta la serpiente (arriba,abajo,izquierda o derecha)
        */

		void setDireccion(sf::Vector2f);

        /** \brief Para que crezca la serpiente, la cantidad que crece la serpiente viene delimitada por los ajustes
        *   (ve�se AlmacenDeAjustes)
        */

        void crecer();

        /** \brief Vector con todas las posiciones de la serpiente, listo para ser dibujado
        */

        const std::vector<sf::Sprite>& getGrafico() const {return cola;}

        /** \brief Devuelve la posici�n de la cabeza
        */

		sf::Vector2f getPosition(){return cola[0].getPosition();}

        /** \brief La cantidad de pixeles que se desplaza cada vez que se llama a mover()
        */

		static const int despl=10;

    private:
        /** \brief Llamado por mover, para mantener la consistencia de la cola despu�s de mover la cabeza (mueve cada cola[i] a cola[i-1])
        */

        void actualizarCola();

        /** \brief Cola de la serpiente misma, esta hecha por sprites para que pueda ser dibujada directamente (pero la textura es
            com�n y compartida)
        */

        std::vector<sf::Sprite> cola;


        /** \brief Se llama as� al desplazamiento de la serpiente expresado en formato vector.
        *
        *   Ejemplo:
        *
        *   Izquierda: (-1,0)
        *   Derecha: (1,0)
        *   Abajo: (0,1)
        *   Arriba: (0,-1)
        */

		sf::Vector2f velocidad;

        /** \brief Utilizado por setDireccion()
        */

		bool movido;

        /** \brief La velocidad anterior
        */

		sf::Vector2f velocidad2;

        /** \brief Textura de la serpiente, compartida entre todos los sprites de la cola
        */

		sf::Texture textura;

        /** \brief Textura de la serpiente, compartida entre todos los sprites de la cola
        */
        int incremento_comida;
};

#endif // JUGADOR_HPP
