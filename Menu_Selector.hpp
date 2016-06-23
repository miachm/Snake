#ifndef MENU_SELECTOR_H
#define MENU_SELECTOR_H

#include <SFML/Graphics.hpp>

/** \brief Esta clase simboliza un menu selector, es decir, un conjunto de opciones que puedes ir seleccionando con teclado+rat�n.
 *          Las opciones pueden estar representadas hasta en 3 dimensiones distintas (x,y,pagina), para usar este menu_selector se debe
 *          heredar la clase y implementar sus callbacks. Notes� que menu_selector no dibuja (de eso se encarga el controlador)
 *
 */


class Menu_Selector
{
    public:

        /** \brief Construye un menu_selector, dado la posici�n X,Y donde est� la primera opci�n, el n�mero de dimensiones
         *  y la opci�n seleccionada por defecto
         *
         * \param pos_primero: Indica donde se encuentra f�sicamente la posici�n X,Y del plano de la primera opci�n.
         *   Esto se necesita para implementar el rat�n, los dem�s elementos se asumiran que forman una cuadr�cula descendente de igual tama�o
         * \param size: Dimensiones f�sicas de cada elemento
         * \param limit: N�mero de dimensiones que hay (inicialmente).
         * \param select: Elemento seleccionado inicialmente (por sus coordenadas X,Y,Z).
         */

        Menu_Selector(sf::Vector2i pos_primero,sf::Vector2i size,sf::Vector3i limit,
                      sf::Vector3i select = sf::Vector3i(0,0,0));

    protected:

        /** \brief Aqu� le pasas los eventos y actualiza el men� selector si ha habido cambios en el rat�n/teclado
         * \param Event: El evento nuevo a tratar
         *
         */


        void tratarEvento(sf::Event &);

        /**\brief Metodo callback que se lanza cuando el usuario selecciona una opci�n, los hijos de esta clase deben implementar
         *        esta callback.
         * \param int: Numero de opci�n que estaba seleccionada (ve�se getNumElemento).
         *
         */

        virtual void lanzarInstancia(int) = 0;

        /**\brief Metodo callback que se lanza cuando el usuario cambia de opci�n (X,Y), los hijos de esta clase pueden implementar
         *        esta callback.
         *
         */

        virtual void cambiaOpcion(){}

        /**\brief Metodo callback que se lanza cuando el usuario cambia de opci�n (Z), los hijos de esta clase pueden implementar
         *        esta callback.
         *
         * \param incr: 1 si la p�gina se ha incrementado, -1 si la p�gina se ha decrementado
         */

        virtual void cambiaPagina(int incr){}

        /**\brief Actualiza el n�mero de p�ginas, si el nuevo limite es menor que la seleccion actual, actualiza seleccion
         *        a z-1
         *
         */

        void setPaginas(int z){limites.z = z; if (seleccion.z >= z) seleccion.z = z-1;}

        /**\brief Obtiene el n� de elemento seleccionado actualmente, esta funci�n hace el pase de las coordenadas (X,Y,Z) a un entero
         *  simple, para obtener la posici�n mire getPosition()
         *
         */

        int getNumElemento();

        /**\brief Obtiene el n� de elemento seleccionado a partir de unas coordenadas x,y,z dadas, esta funci�n hace el pase
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
        /** \brief Numero de items que contiene cada p�gina (equivalente a limites.x*limites.y)
        */

        const int items_por_pagina;

        /** \brief Coordenadas XY donde est� el primer elemento del men�
        */

        const sf::Vector2i pos_inicial;

        /** \brief Tama�o de cada elemento del men�, si fuera 40,40. Indicar�a que cada elemento del men�
        *   forma un cuadrado 40x40.
        */

        const sf::Vector2i tam;

        /** \brief N�mero de elementos que hay en cada coordenada x,y,z.
        *
        *   Por ejemplo, si fuese 4,4,5. Significar�a que hay 5 p�ginas con 4x4 elementos en cada una.
        */

        sf::Vector3i limites;

        /** \brief Indica que opci�n est� seleccionada actualmente
        */

        sf::Vector3i seleccion;

        /** \brief Funci�n auxiliar de tratarevento que se encarga unicamente de tratar los eventos de teclado
        */

        void monotorizarTeclado(sf::Event &event);

        /** \brief Se llama cuando el usuario va hacia arriba una opci�n, provoca el callback a cambiaOpcion
        */

        void subirOpcion();

        /** \brief Se llama cuando el usuario va hacia abajo una opci�n, este m�todo provoca el callback a cambiaOpcion()
        */

        void abajoOpcion();

        /** \brief Se llama cuando el usuario va hacia la izquierda una opci�n, este m�todo provoca el callback a cambiaOpcion()
        */

        void izquierdaOpcion();

        /** \brief Se llama cuando el usuario va hacia la derecha una opci�n, este m�todo provoca el callback a cambiaOpcion()
        */

        void derechaOpcion();

        /** \brief Incrementa la selecci�n en una coordenada X, a diferencia de derechaOpcion(), no hace checkeos adicionales
        *   ni cambia de p�gina cuando se sale de los bordes
        */

        void incrOpcionX();

        /** \brief Incrementa la selecci�n en una coordenada Y, a diferencia de arrinaOpcion, no hace checkeos adicionales
        */

        void incrOpcionY();

        /** \brief Incrementa la selecci�n en una coordenada Z, a diferencia de arribaOpcion(), no hace checkeos adicionales
        */

        void incrOpcionZ();

        /** \brief Decrementa la selecci�n en una coordenada Z
        */

        void decrOpcionX();

        /** \brief Decrementa la selecci�n en una coordenada Y, a diferencia de abajoOpcion(), no hace checkeos adicionales
        */

        void decrOpcionY();

        /** \brief Decrementa la selecci�n en una coordenada Z
        */

        void decrOpcionZ();

        /** \brief Asigna a la posici�n X est� coordenada, provoca el callback a cambiaOpcion()
        */

        void setPositionX(int);

        /** \brief Asigna a la posici�n Y est� coordenada, provoca el callback a cambiaOpcion()
        */

        void setPositionY(int);

        /** \brief Asigna a la posici�n Z est� coordenada, provoca el callback a cambiaOpcion()
        */

        void setPositionZ(int);

        /** \brief Determina si unas determinadas coordenadas X,Y forma parte del encuadre de una opci�n,
        *   se utiliza por el rat�n
        *
        *   \return True si forma parte del encuadre de una opci�n, false sino
        */

        bool dentroDeEncuadre(int,int);
};

#endif // MENU_SELECTOR_H
