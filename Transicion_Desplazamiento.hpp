#ifndef TRANSICION_DESPLAZAMIENTO_HPP
#define TRANSICION_DESPLAZAMIENTO_HPP

#include "Transicion.hpp"

class Transicion_Desplazamiento : public Transicion
{
    public:
        Transicion_Desplazamiento(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,
                                  sf::Vector2i velocidad,const int iteraciones = 60);
    protected:
        void init(int);
        void animar() override;

    private:
        sf::Vector2f incr;
        sf::Vector2i mivelocidad;
};

#endif
