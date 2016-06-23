#ifndef ALMACENDEAJUSTES_H
#define ALMACENDEAJUSTES_H

#include "Almacen.hpp"
#include "SFML/Graphics.hpp"
#include "Opciones.hpp"

/**
*   @brief Objeto single-tin (objeto de una solo creacción), para almacenar y administrar los ajustes, los datos.
*   El constructor carga un archivo de configuración ini, el archivo de configuración indica de forma textual a que
*   equivale cada variable. Ejemplo:
*
*       [Serpiente]
*       delay = 60
*       incr_crecer = 8
*
*
*   Las variables que no han sido configuradas (ej: el color del jugador) tienen un valor por defecto. Las líneas con fallos
*   sintacticos se ignoran
**/

class AlmacenDeAjustes : public Almacen
{
    public:

        /** \brief Obtiene una instancia de AlmacenAjustes, si no existía aún lo crea y si existía lo crea y devuelve la referencia.
        *
        */
        static AlmacenDeAjustes& getInstancia()
        {
            static AlmacenDeAjustes instancia;
            return instancia;
        }

        /** \brief Obtiene el valor de la variable Delay, que corresponde al tiempo que pasará entre dos movimientos de la
        *   serpiente (cuando menos, más rápido irá).
        */

        int getDelay() const {return delay;}

        /** \brief Obtiene el valor de la variable naCrecer, que corresponde a la cantidad de cuadrados que crece la serpiente
        *   al comer algo.
        */

        int getNaCrecer() const {return NaCrecer;}

        /** \brief Obtiene el valor de la variable ColorJugador, que corresponde al color de la serpiente
        */

        sf::Color getColorJugador() const {return color_jugador;}

        int getVolumen() const {return volumen;}

        bool getMusica() const {return musica;}

        int getIncrCrecer() const {return incrCrecer;}

        int getTicks_transicion() const {return ticks_transicion;}

        /** \brief Destructor, llama a la función guardar para guardar los cambios actualizados
        */

        ~AlmacenDeAjustes();

    private:

        /** \brief Guarda los ajustes en el disco
        */

        void guardar();

        /** \brief PRIVADO, inicializa los ajustes por defecto y carga el archivo de configuración ini (ya explicado en la descripción
        *   de la clase).
        */

        AlmacenDeAjustes();


        /** \brief Aplica los ajustes por defecto a todas las variables
        */

        void ajustesPorDefecto();


        /** \brief Volumen de los sonidos
        */

        float volumen;
        void incrVolumen(int incr){if (volumen+incr >= 0 && volumen +incr <= 100) volumen += incr;}

        /** \brief ¿Musica? (no implementado)
        */

        bool musica;

        /** \brief Variable delay, que corresponde al tiempo que pasará entre dos movimientos de la
        *   serpiente (cuando menos, más rápido irá).
        */

        int delay;
        void incrDelay(int incr){if (delay+incr > 0) delay += incr;}

        /** \brief Variable incrCrecer, que corresponde a la cantidad de cuadrados que crece la serpiente
        *   al comer algo.
        */

        int incrCrecer;
        void incrementarCrecer(int incr){if (incrCrecer+incr >= 0) incrCrecer += incr;}

        /** \brief Variable NaCrecer, corresponde al crecimiento gradual, es decir. Cuanto va a aumentando
        incrCrecer cada vez que la serpiente come algo, por defecto es cero.
        */

        int NaCrecer;
        void incrNaCrecer(int incr){if (NaCrecer+incr >= 0) NaCrecer += incr;}

        /** \brief Variable color_jugador, que corresponde al color de la serpiente
        */

        sf::Color color_jugador;

        int ticks_transicion;
        void incrTicks_transicion(int incr){if (ticks_transicion+incr >= 0 && ticks_transicion+incr <= 180) ticks_transicion += incr;}

        friend class Opciones;
};

#endif // ALMACENDEAJUSTES_H
