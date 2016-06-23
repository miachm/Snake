#ifndef EDITORDENIVELES_HPP
#define EDITORDENIVELES_HPP

#include "Controlador.hpp"
#include "Modelo.hpp"
#include "Nivel.hpp"
#include "Menu_Selector.hpp"

class EditorDeNiveles : public Controlador,Menu_Selector
{
    public:
        EditorDeNiveles(Modelo*);
        EditorDeNiveles(Modelo*,Nivel&);

        /** \brief Mediante esta funci�n, se le env�an nuevos eventos al controlador para que los trate y procese
        *   \param Event: El evento a tratar
        */

        void tratarEvento(sf::Event &event) override ;

        /** \brief Esta funci�n ser� llamada por Modelo para refrescar la pantalla, el controlador deber� decirle a Modelo
        *   que cosas pintar
        */

        void refrescarPantalla() override ;

        void lanzarInstancia(int n) override {ponerLadrillo();}
    protected:
    private:
        Modelo* modelo;
        Nivel nivel;

        void salir();
        void SalirSinGuardar(){modelo->finishController();}
        void ponerLadrillo();
        void ponerCabeza();
        void borrar();
};
#endif
