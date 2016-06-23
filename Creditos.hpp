#ifndef CREDITOS_H
#define CREDITOS_H

#include "Modelo.hpp"
#include "AlmacenDeImagenes.hpp"

/** \brief Controlador que muestra la pantalla de créditos
 */


class Creditos : public Controlador
{
    public:
        /** \brief Constructor, carga los créditos desde una imagen (Creditos.bmp)
        */

        Creditos(Modelo* m) : modelo(m)
        {
            pantalla.setTexture(AlmacenDeImagenes::getInstancia().getCreditos());
        }

        /** \brief Eventos, captura el cierre de ventana y termina el controlador si se pulsa
        *   una tecla o el ratón
        */

        void tratarEvento(sf::Event & event) override
        {
            if (event.type == sf::Event::Closed) modelo->cerrarVentana();
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) modelo->finishController();
        }

        /** \brief Refresca la pantalla, en este unicamente se pinta la imagen anterior
        */

        void refrescarPantalla() override
        {
            modelo->dibujar(pantalla);
        }
    private:
    sf::Texture imagen;
    sf::Sprite pantalla;
    Modelo* modelo;
};

#endif // CREDITOS_H
