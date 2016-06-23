#ifndef SELECTORNIVELES_H
#define SELECTORNIVELES_H

#include "Controlador.hpp"
#include "Modelo.hpp"
#include "Nivel.hpp"
#include "Menu_Selector.hpp"
#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include "Transicion_Desplazamiento.hpp"


class SelectorNiveles : public Controlador,Menu_Selector
{
    public:
        SelectorNiveles(Modelo* m, int op = 0);
        ~SelectorNiveles();

        void tratarEvento(sf::Event &) override;
        void refrescarPantalla() override;

    private:
        Transicion* transicion;

        int opcionLanzarInstancia;

        const sf::Font& fuente;
        sf::Sound menu_mover;
        sf::Sound menu_enter;

		static const int hnivel=140;
		static const int wnivel=180;
		static const int LIMIT_X = 3;
		static const int LIMIT_Y = 3;
		static const int niveles_por_pagina = LIMIT_X*LIMIT_Y;

        Modelo* modelo;
		//const std::vector<Nivel>& niveles;
		int nniveles;
		Nivel *seleccionado;

        void salir();
        void cerrarVentana();
        void lanzarInstancia(int) override;
        void cambiaOpcion() override;
        void cambiaPagina(int incr) override
        {
            cambiaOpcion();
            refrescarPantalla();
            transicion = new Transicion_Desplazamiento(modelo,captura_anterior,captura,sf::Vector2i(incr,0),AlmacenDeAjustes::getInstancia().getTicks_transicion());
        }

        sf::Sprite flecha_izquierda;
        sf::Sprite flecha_derecha;

        sf::Texture captura;
        sf::Texture captura_anterior;
        sf::RenderTexture capturador;

        static constexpr float escala = 0.25;
};

#endif // SELECTORNIVELES_H
