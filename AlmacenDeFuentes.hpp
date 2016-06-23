#ifndef ALMACENDEFUENTES_H
#define ALMACENDEFUENTES_H

#include "Almacen.hpp"

/**
*   @brief Objeto single-tin (objeto de una sola creacción), para almacenar las fuentes de texto, hereda de Almacen
*   por lo que su copia está prohibida y su constructor está protegido. Debe instanciarse con el método getInstancia()
**/

class AlmacenDeFuentes : public Almacen
{
    public:

    /** \brief Obtiene una instancia de AlmacenDeFuentes, si no existía aún lo crea y si existía lo crea y devuelve la referencia.
    *
    */
    static const AlmacenDeFuentes& getInstancia()
    {
        static const AlmacenDeFuentes instancia;
        return instancia;
    }


    /** \brief Obtiene la fuente Arial
    */

    const sf::Font& getArial() const {return arial;}

    /** \brief Obtiene la fuente Calibri
    */
    const sf::Font& getCalibri() const {return calibri;}
    private:

        /** \brief Carga las fuentes desde disco. Lanza excepción si fuente no encontrada.
        */

        AlmacenDeFuentes()
        {
            if (!arial.loadFromFile("./Fonts/arial.ttf")) throw "Fuente arial no encontrada";
            if (!calibri.loadFromFile("./Fonts/calibri.ttf")) throw "Fuente calibri no encontrada";
        }


        /** \brief Fuente de texto Arial.
        */

        sf::Font arial;

        /** \brief Fuente de texto Calibri.
        */

        sf::Font calibri;
};

#endif // ALMACENDEFUENTES_H
