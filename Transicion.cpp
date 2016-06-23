#include "Transicion.hpp"

Transicion::Transicion(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones)
                      : textura_primero(anterior),textura_segundo(siguiente),modelo(m),
                        ticks (iteraciones)
{
    primero.setTexture(textura_primero);
    segundo.setTexture(textura_segundo);

//    modelo->dibujar(segundo);
//    std::cin.get();
}

void Transicion::refrescarPantalla()
{
    if (ticks == -1)
    {
        segundo.setPosition(0,0);
        modelo->dibujar(segundo);
        modelo->finishController();
    }
    else
    {
        animar();
        modelo->dibujar(primero);
       modelo->dibujar(segundo);
        ticks--;
    }
}
