#include "Transicion_Transparencia.hpp"

Transicion_Transparencia::Transicion_Transparencia(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones)
                                            :  Transicion(m,anterior,siguiente,iteraciones)
{
    init(iteraciones);
}

void Transicion_Transparencia::init(int iteraciones)
{

    incr = 255/iteraciones;
    primero.setColor(sf::Color(255,255,255,255));
    segundo.setColor(sf::Color(255,255,255,0));

    transparencia = incr;
}

void Transicion_Transparencia::animar()
{
   // primero.setColor(sf::Color(255,255,255,255-transparencia));
    segundo.setColor(sf::Color(255,255,255,transparencia));
    transparencia += incr;
}
