#ifndef TRANSICION_H
#define TRANSICION_H

#include "Controlador.hpp"
#include "Modelo.hpp"

/** \brief Clase, invocada por modelo cuando se a�ade/elimina controladores, representa una transici�n animada entre dos controladores

    \note Notes� que actua como un controlador m�s, es una clase abstracta, sus hijos definir�n que efecto se aplicar� (fundido, volteado...)
**/

class Transicion : public Controlador
{
    public:

        /**
        \brief Construye la transicion y la prepara.
        \param m: Referencia al Modelo
        \param anterior: Imagen/Captura del controlador que se va a quitar
        \param siguiente: Imagen/captura del controlador que se va a poner
        \param iteraciones: Numero de fotogramas que tendr� la transici�n
        **/
        Transicion(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones = 60);

        /**
        \brief Act�a como un controlador, por lo que tiene que tratar y recibir los eventos, en este caso solo procesa los eventos
        de cierre de ventana
        **/

        virtual void tratarEvento(sf::Event & event) override
        {
            if (event.type == sf::Event::Closed) modelo->cerrarVentana();
        }

        /**
        \brief Act�a como un controlador, pinta en pantalla el siguiente fotograma. Cuando se acaben las "iteraciones" el controlador
        se cerrar�.
        **/

        void refrescarPantalla() override;

        /**
        \brief Cuantas iteraciones quedan
        **/

        int getTicks() const{return ticks;}

    protected:
        sf::Sprite primero,segundo;

        /**
        \brief Funci�n que implementar� el hijo de la clase para la animaci�n, se le llamar� una vez por cada fotograma
        **/

        virtual void animar() = 0;
    private:

        const sf::Texture textura_primero;
        const sf::Texture textura_segundo;
        Modelo* modelo;
        int ticks;
};

#endif // TRANSICION_H
