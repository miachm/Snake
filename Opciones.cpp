#include "Opciones.hpp"
#include "AlmacenDeAjustes.hpp"
#include "AlmacenDeImagenes.hpp"
#include "AlmacenDeFuentes.hpp"

#include <sstream>

Opciones::Opciones(Modelo* m) : Menu_Selector(sf::Vector2i(0,20),sf::Vector2i(Modelo::fwidth,52),sf::Vector3i(1,7,1)),modelo(m)
{
    //Normal = Texto para las opciones no seleccionadas
    //Seleccionado = Texto para las opciones seleccionadas

    normal.setFont(AlmacenDeFuentes::getInstancia().getCalibri());
    seleccionado.setFont(AlmacenDeFuentes::getInstancia().getCalibri());

    normal.setCharacterSize(48);
    seleccionado.setCharacterSize(48);
    seleccionado.setColor(sf::Color::Yellow);

    /** Sprites de flechas
    *
    */

    flecha_izquierda.setTexture(AlmacenDeImagenes::getInstancia().getFlecha());
    flecha_derecha.setTexture(AlmacenDeImagenes::getInstancia().getFlecha());

    flecha_izquierda.rotate(180.0);

    flecha_izquierda.setPosition(30,Modelo::fheight-10);
    flecha_derecha.setPosition(Modelo::fwidth-30,Modelo::fheight-40);
}

void Opciones::tratarEvento(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        modelo->cerrarVentana();
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape) modelo->finishController();
        else if (event.key.code == sf::Keyboard::Left) cambiaOpcion(-1);
        else if (event.key.code == sf::Keyboard::Right) cambiaOpcion(1);
        else
            Menu_Selector::tratarEvento(event);
    }
    else
    {
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            float a=event.mouseWheelScroll.delta;
            //if(a>0)
                cambiaOpcion(a);
            //else
              //  cambiaOpcion(-1);
        }
        else
            Menu_Selector::tratarEvento(event);
    }
  //  else if (event.type)
}

void Opciones::cambiaOpcion(int incr)
{
    switch(getPositionY())
    {
        case 0:
            AlmacenDeAjustes::getInstancia().incrVolumen(incr);
            break;
        case 1:
            AlmacenDeAjustes::getInstancia().incrDelay(incr);
            break;
        case 2:
            AlmacenDeAjustes::getInstancia().incrementarCrecer(incr);
            break;
        case 3:
            AlmacenDeAjustes::getInstancia().incrNaCrecer(incr);
            break;
        case 4:
            AlmacenDeAjustes::getInstancia().incrTicks_transicion(incr);
            break;
    }

}

void Opciones::lanzarInstancia(int n)
{
    switch(n)
    {
    case 5:
        AlmacenDeAjustes::getInstancia().ajustesPorDefecto();
        break;
    case 6:
        modelo->finishController();
        break;
    }
}

std::string pasarAString(int N)
{
    std::stringstream ss;
    ss<<N;
    return ss.str();
}

void Opciones::refrescarPantalla()
{
    int dato;
    int y = 20;
    const int x = 10;
    const int incr = 48;

    dato = AlmacenDeAjustes::getInstancia().getVolumen();
    normal.setString(std::string("Volumen :   ") + pasarAString(dato));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

    y += incr;

    dato = AlmacenDeAjustes::getInstancia().getDelay();
    normal.setString(std::string("Delay : ") + pasarAString(dato));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

       y += incr;

    dato = AlmacenDeAjustes::getInstancia().getIncrCrecer();
    normal.setString(std::string("Crecimiento : ") + pasarAString(dato));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

      y += incr;

    dato = AlmacenDeAjustes::getInstancia().getNaCrecer();
    normal.setString(std::string("Crecimiento gradual: ") + pasarAString(dato));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

    y += incr;

    dato = AlmacenDeAjustes::getInstancia().getTicks_transicion();
    normal.setString(std::string("Ticks transicion: ") + pasarAString(dato));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

    y += incr;
    normal.setString(std::string("Ajustes predeterminados"));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

    y += incr;
    normal.setString(std::string("Salir"));
    normal.setPosition(x,y);
    modelo->dibujar(normal);

    switch(getPositionY())
    {
        case 0:
            dato = AlmacenDeAjustes::getInstancia().getVolumen();
            seleccionado.setString(std::string("Volumen :   ") + pasarAString(dato));
            seleccionado.setPosition(x,20);
            break;
        case 1:
            dato = AlmacenDeAjustes::getInstancia().getDelay();
            seleccionado.setString(std::string("Delay : ") + pasarAString(dato));
            seleccionado.setPosition(x,20+incr);
            break;
        case 2:
            dato = AlmacenDeAjustes::getInstancia().getIncrCrecer();
            seleccionado.setString(std::string("Crecimiento : ") + pasarAString(dato));
            seleccionado.setPosition(x,20+2*incr);
            break;
        case 3:
            dato = AlmacenDeAjustes::getInstancia().getNaCrecer();
            seleccionado.setString(std::string("Crecimiento gradual: ") + pasarAString(dato));
            seleccionado.setPosition(x,20+3*incr);
            break;

        case 4:
            dato = AlmacenDeAjustes::getInstancia().getTicks_transicion();
            seleccionado.setString(std::string("Ticks transicion: ") + pasarAString(dato));
            seleccionado.setPosition(x,20+4*incr);
            break;
        case 5:
            seleccionado.setString(std::string("Ajustes predeterminados"));
            seleccionado.setPosition(x,20+5*incr);
            break;
        case 6:
            seleccionado.setString(std::string("Salir"));
            seleccionado.setPosition(x,20+6*incr);
            break;
    }

    modelo->dibujar(seleccionado);
}
