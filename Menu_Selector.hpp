#ifndef MENU_SELECTOR_H
#define MENU_SELECTOR_H

#include <SFML/Graphics.hpp>

/** \brief Esta clase simboliza un menu selector, es decir, un conjunto de opciones que puedes ir seleccionando con teclado+ratón.
 *          Las opciones pueden estar representadas hasta en 3 dimensiones distintas (x,y,pagina), para usar este menu_selector se debe
 *          heredar la clase y implementar sus callbacks. Notesé que menu_selector no dibuja (de eso se encarga el controlador)
 *
 */


class Menu_Selector
{
    public:

        /** \brief Construye un menu_selector, dado la posición X,Y donde está la primera opción, el número de dimensiones
         *  y la opción seleccionada por defecto
         *
         * \param pos_primero: Indica donde se encuentra físicamente la posición X,Y del plano de la primera opción.
         *   Esto se necesita para implementar el ratón, los demás elementos se asumiran que forman una cuadrícula descendente de igual tamaño
         * \param size: Dimensiones físicas de cada elemento
         * \param limit: Número de dimensiones que hay (inicialmente).
         * \param select: Elemento seleccionado inicialmente (por sus coordenadas X,Y,Z).
         */

        Menu_Selector(sf::Vector2i pos_primero,sf::Vector2i size,sf::Vector3i limit,
                      sf::Vector3i select = sf::Vector3i(0,0,0));

    protected:

        /** \brief Aquí le pasas los eventos y actualiza el menú selector si ha habido cambios en el ratón/teclado
         * \param Event: El evento nuevo a tratar
         *
         */


        void tratarEvento(sf::Event &);

        /**\brief Metodo callback que se lanza cuando el usuario selecciona una opción, los hijos de esta clase deben implementar
         *        esta callback.
         * \param int: Numero de opción que estaba seleccionada (veáse getNumElemento).
         *
         */

        virtual void lanzarInstancia(int) = 0;

        /**\brief Metodo callback que se lanza cuando el usuario cambia de opción (X,Y), los hijos de esta clase pueden implementar
         *        esta callback.
         *
         */

        virtual void cambiaOpcion(){}

        /**\brief Metodo callback que se lanza cuando el usuario cambia de opción (Z), los hijos de esta clase pueden implementar
         *        esta callback.
         *
         * \param incr: 1 si la página se ha incrementado, -1 si la página se ha decrementado
         */

        virtual void cambiaPagina(int incr){}

        /**\brief Actualiza el número de páginas, si el nuevo limite es menor que la seleccion actual, actualiza seleccion
         *        a z-1
         *
         */

        void setPaginas(int z){limites.z = z; if (seleccion.z >= z) seleccion.z = z-1;}

        /**\brief Obtiene el nº de elemento seleccionado actualmente, esta función hace el pase de las coordenadas (X,Y,Z) a un entero
         *  simple, para obtener la posición mire getPosition()
         *
         */

        int getNumElemento();

        /**\brief Obtiene el nº de elemento seleccionado a partir de unas coordenadas x,y,z dadas, esta función hace el pase
         *  de las coordenadas (X,Y,Z) a un entero simple.
         *
         */

        int getNumElemento(int x,int y,int z);

        /**\brief Obtiene el elemento seleccionado actual
         *
         */

        sf::Vector3i getPosition() const {return seleccion;}

        /**\brief Shortcout para getPosition().x
         *
         */

        int getPositionX() const {return seleccion.x;}

        /**\brief Shortcout para getPosition().y
         *
         */

        int getPositionY() const {return seleccion.y;}

        /**\brief Shortcout para getPosition().z
         *
         */

        int getPositionZ() const {return seleccion.z;}

        /** \brief Obtiene los limites actuales
        *
        */

        sf::Vector3i getLimites() const {return limites;}

        /** \brief Pasa a la pagina siguiente
        *
        */

        void paginaSiguiente()
        {
            if (seleccion.z < limites.z-1)
                incrOpcionZ();
        }

        /** \brief Pasa a la pagina anterior
        *
        */

        void paginaAnterior()
        {
            if (seleccion.z > 0)
                decrOpcionZ();
        }

    private:
        /** \brief Numero de items que contiene cada página (equivalente a limites.x*limites.y)
        */

        const int items_por_pagina;

        /** \brief Coordenadas XY donde está el primer elemento del menú
        */

        const sf::Vector2i pos_inicial;

        /** \brief Tamaño de cada elemento del menú, si fuera 40,40. Indicaría que cada elemento del menú
        *   forma un cuadrado 40x40.
        */

        const sf::Vector2i tam;

        /** \brief Número de elementos que hay en cada coordenada x,y,z.
        *
        *   Por ejemplo, si fuese 4,4,5. Significaría que hay 5 páginas con 4x4 elementos en cada una.
        */

        sf::Vector3i limites;

        /** \brief Indica que opción está seleccionada actualmente
        */

        sf::Vector3i seleccion;

        /** \brief Función auxiliar de tratarevento que se encarga unicamente de tratar los eventos de teclado
        */

        void monotorizarTeclado(sf::Event &event);

        /** \brief Se llama cuando el usuario va hacia arriba una opción, provoca el callback a cambiaOpcion
        */

        void subirOpcion();

        /** \brief Se llama cuando el usuario va hacia abajo una opción, este método provoca el callback a cambiaOpcion()
        */

        void abajoOpcion();

        /** \brief Se llama cuando el usuario va hacia la izquierda una opción, este método provoca el callback a cambiaOpcion()
        */

        void izquierdaOpcion();

        /** \brief Se llama cuando el usuario va hacia la derecha una opción, este método provoca el callback a cambiaOpcion()
        */

        void derechaOpcion();

        /** \brief Incrementa la selección en una coordenada X, a diferencia de derechaOpcion(), no hace checkeos adicionales
        *   ni cambia de página cuando se sale de los bordes
        */

        void incrOpcionX();

        /** \brief Incrementa la selección en una coordenada Y, a diferencia de arrinaOpcion, no hace checkeos adicionales
        */

        void incrOpcionY();

        /** \brief Incrementa la selección en una coordenada Z, a diferencia de arribaOpcion(), no hace checkeos adicionales
        */

        void incrOpcionZ();

        /** \brief Decrementa la selección en una coordenada Z
        */

        void decrOpcionX();

        /** \brief Decrementa la selección en una coordenada Y, a diferencia de abajoOpcion(), no hace checkeos adicionales
        */

        void decrOpcionY();

        /** \brief Decrementa la selección en una coordenada Z
        */

        void decrOpcionZ();

        /** \brief Asigna a la posición X está coordenada, provoca el callback a cambiaOpcion()
        */

        void setPositionX(int);

        /** \brief Asigna a la posición Y está coordenada, provoca el callback a cambiaOpcion()
        */

        void setPositionY(int);

        /** \brief Asigna a la posición Z está coordenada, provoca el callback a cambiaOpcion()
        */

        void setPositionZ(int);

        /** \brief Determina si unas determinadas coordenadas X,Y forma parte del encuadre de una opción,
        *   se utiliza por el ratón
        *
        *   \return True si forma parte del encuadre de una opción, false sino
        */

        bool dentroDeEncuadre(int,int);
};

#endif // MENU_SELECTOR_H
