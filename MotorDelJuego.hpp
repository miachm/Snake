#ifndef MOTORDELJUEGO_H
#define MOTORDELJUEGO_H
#include "Controlador.hpp"
#include "Comida.hpp"
#include "Jugador.hpp"
#include "Nivel.hpp"
#include "Modelo.hpp"

class MotorDelJuego : public Controlador
{
    public:
        MotorDelJuego(Modelo* m,const Nivel& n);
        ~MotorDelJuego();

        void tratarEvento(sf::Event &) override;
        void refrescarPantalla() override;
    private:
        Modelo * modelo;
        const Nivel &nivel;
        Jugador jugador;
        Comida comida;
		bool soloCabeza;
		bool recienCrecido;

		sf::Sound comida_sonido;
		sf::Sound muerte_sonido;
        sf::Time tiempo_entre_mov;

        sf::Clock tiempo_pasado;

        bool juego_activo;
};

#endif // MOTORDELJUEGO_H
