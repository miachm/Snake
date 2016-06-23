#ifndef ALMACENDESONIDOS_H
#define ALMACENDESONIDOS_H
#include <SFML/Audio.hpp>
#include "Almacen.hpp"

/** \brief Objeto single-tin (objeto de una solo creacción), para almacenar los sonidos.
*   Todos los sonidos son externos, el constructor carga los sonidos de su Carpeta.
*
*/

class AlmacenDeSonidos : public Almacen
{
    public:

        /** \brief Obtiene una instancia de AlmacenDeSonidos, si no existía aún lo crea y si existía lo crea y devuelve la referencia.
        *
        */
        static const AlmacenDeSonidos& getInstancia()
        {
            static const AlmacenDeSonidos instancia;
            return instancia;
        }

        /** \brief Obtiene una referencia a menu_mover, que corresponde con el sonido que emite un menú al cambiar de opción
        */

        const sf::SoundBuffer& getMenu_mover() const {return menu_mover;}

        /** \brief Obtiene una referencia a menu_enter, que corresponde con el sonido que emite el menú al hacer enter/click
        *   en él
        */

        const sf::SoundBuffer& getMenu_enter() const {return menu_enter;}

        /** \brief Obtiene una referencia a muerte, que corresponde con el sonido que emite cuando la serpiente muere
        */

        const sf::SoundBuffer& getMuerte() const {return muerte;}

        /** \brief Obtiene una referencia a comida, que corresponde con el sonido que emite cuando la serpiente come una comida
        */

        const sf::SoundBuffer& getComida() const {return comida;}

    private:

        /** \brief PRIVADO, carga los sonidos de su carpeta (Sonido)
        */

        AlmacenDeSonidos()
        {
            const std::string carpeta = "./Sonido/";
            menu_mover.loadFromFile(carpeta+"Menu_mover.wav");
            menu_enter.loadFromFile(carpeta+"Menu_sonido.wav");
            comida.loadFromFile(carpeta+"Comida.wav");
            muerte.loadFromFile(carpeta+"Muerte.wav");
        }

        /** \brief Corresponde con el sonido que emite el menú al cambiar de opción
        */

        sf::SoundBuffer menu_mover;

        /** \brief Corresponde con el sonido que emite el menú al hacer enter/click
        */

        sf::SoundBuffer menu_enter;

        /** \brief Corresponde con el sonido que emite cuando la serpiente muere
        */

        sf::SoundBuffer muerte;

        /** \brief Corresponde con el sonido que emite cuando la serpiente come una comida
        */

        sf::SoundBuffer comida;
};

#endif // ALMACENDESONIDOS_H
