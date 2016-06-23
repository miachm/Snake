#ifndef OPCIONES_HPP
#define OPCIONES_HPP

#include "Controlador.hpp"
#include "Modelo.hpp"
#include "Menu_Selector.hpp"

/**         POR IMPLEMENTAR

**/

class Opciones : public Controlador,Menu_Selector
{
    public:
        Opciones(Modelo* m);

        void tratarEvento(sf::Event &) override;
        void refrescarPantalla() override;

        void lanzarInstancia(int n) override;
    private:

        void cambiaOpcion(int);

        Modelo* modelo;

        sf::Text normal;
        sf::Text seleccionado;

        sf::Sprite flecha_izquierda;
        sf::Sprite flecha_derecha;
};

#endif // OPCIONES_HPP
