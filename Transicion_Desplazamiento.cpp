#include "Transicion_Desplazamiento.hpp"

Transicion_Desplazamiento::Transicion_Desplazamiento(Modelo* m,const sf::Texture& anterior,
                                                     const sf::Texture& siguiente,sf::Vector2i velocidad,
                                                     const int iteraciones)
: Transicion(m,anterior,siguiente,iteraciones)
{
    mivelocidad = velocidad;

    init(iteraciones);
}

void Transicion_Desplazamiento::init(int ticks)
{
    float cast = ticks;
    incr = sf::Vector2f(mivelocidad.x*Modelo::fwidth/cast,mivelocidad.y*Modelo::fheight/cast);

    primero.setPosition(0,0);
    segundo.setPosition(-mivelocidad.x*Modelo::fwidth,-mivelocidad.y*Modelo::fheight);
}

void Transicion_Desplazamiento::animar()
{
    primero.move(incr);
    segundo.move(incr);
}
