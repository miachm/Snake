#ifndef TRANSICION_H
#define TRANSICION_H

#include "Controlador.hpp"
#include "Modelo.hpp"

/** \brief Clase, invocada por modelo cuando se añade/elimina controladores, representa una transición animada entre dos controladores

    \note Notesé que actua como un controlador más, es una clase abstracta, sus hijos definirán que efecto se aplicará (fundido, volteado...)
**/

class Transicion : public Controlador
{
    public:

        /**
        \brief Construye la transicion y la prepara.
        \param m: Referencia al Modelo
        \param anterior: Imagen/Captura del controlador que se va a quitar
        \param siguiente: Imagen/captura del controlador que se va a poner
        \param iteraciones: Numero de fotogramas que tendrá la transición
        **/
        Transicion(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones = 60);

        /**
        \brief Actúa como un controlador, por lo que tiene que tratar y recibir los eventos, en este caso solo procesa los eventos
        de cierre de ventana
        **/

        virtual void tratarEvento(sf::Event & event) override
        {
            if (event.type == sf::Event::Closed) modelo->cerrarVentana();
        }

        /**
        \brief Actúa como un controlador, pinta en pantalla el siguiente fotograma. Cuando se acaben las "iteraciones" el controlador
        se cerrará.
        **/

        void refrescarPantalla() override;

        /**
        \brief Cuantas iteraciones quedan
        **/

        int getTicks() const{return ticks;}

    protected:
        sf::Sprite primero,segundo;

        /**
        \brief Función que implementará el hijo de la clase para la animación, se le llamará una vez por cada fotograma
        **/

        virtual void animar() = 0;
    private:

        const sf::Texture textura_primero;
        const sf::Texture textura_segundo;
        Modelo* modelo;
        int ticks;
};

#endif // TRANSICION_H
