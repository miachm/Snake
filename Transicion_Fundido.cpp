#include "Transicion_Fundido.hpp"

Transicion_Fundido::Transicion_Fundido(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones)
: Transicion(m,anterior,siguiente,iteraciones)
{
      init(iteraciones);
}

void Transicion_Fundido::init(int iteraciones)
{
     incremento = 2*255/iteraciones; // 255 es el brillo original, hay que quitarlo y volverlo a poner de nuevo
    mitad = iteraciones/2;

    primero.setPosition(0,0);
    segundo.setPosition(0,0);

    color_primero = primero.getColor();


    segundo.setColor(sf::Color(0,0,0,0));
    color_segundo = segundo.getColor();
    brillo = 1;
}

void Transicion_Fundido::animar()
{
    if (getTicks() > mitad)
    {
        primero.setColor(color_primero-sf::Color(brillo,brillo,brillo,0));
        brillo+= incremento;
    }
    else if (getTicks() == mitad)
    {
        primero.setColor(sf::Color(0,0,0,0));
        segundo.setColor(sf::Color(0,0,0,255));
        brillo = 1;
    }
    else
    {
        segundo.setColor(color_segundo+sf::Color(brillo,brillo,brillo));
        brillo+= incremento;
    }
}
