#ifndef MENUEDITAR_HPP
#define MENUEDITAR_HPP
#include "Controlador.hpp"
#include "Menu_Selector.hpp"
#include <SFML/Graphics.hpp>
#include "Modelo.hpp"

class MenuEditar : public Controlador, Menu_Selector
{
    protected:
        sf::Text normal, seleccionado;

        Modelo* modelo;
    public:
        MenuEditar(Modelo*);
        ~MenuEditar();
        void lanzarInstancia(int) override;
        void refrescarPantalla() override;
        void tratarEvento(sf::Event & event)override
        {
            if (event.type == sf::Event::Closed) modelo->cerrarVentana();
            Menu_Selector::tratarEvento(event);

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) modelo->finishController();
            }
        }
    private:
};

#endif // MENUEDITAR_HPP
