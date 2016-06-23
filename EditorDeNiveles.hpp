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

        /** \brief Mediante esta función, se le envían nuevos eventos al controlador para que los trate y procese
        *   \param Event: El evento a tratar
        */

        void tratarEvento(sf::Event &event) override ;

        /** \brief Esta función será llamada por Modelo para refrescar la pantalla, el controlador deberá decirle a Modelo
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
