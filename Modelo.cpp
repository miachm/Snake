#include "Modelo.hpp"
#include "Menu.hpp"
#include "AlmacenDeAjustes.hpp"
#include "AlmacenDeImagenes.hpp"
#include "Transicion_Desplazamiento.hpp"
#include "Transicion_Fundido.hpp"
#include "Transicion_Transparencia.hpp"

Modelo::Modelo(Controlador* controlador) : capturando(false),fue_transicion(false),index(-1),window(sf::VideoMode(fwidth,fheight),"Serpiente")
{
    window.setIcon(32,32,AlmacenDeImagenes::getInstancia().getIcono().getPixelsPtr());

    capturador.create(fwidth,fheight);
    desplazar_controlador = false;
    addController(controlador);
    start();
}

void Modelo::start()
{
    window.setFramerateLimit(60);

    while (index >= 0 && window.isOpen())
    {
        dibujarPantalla(controlador[index].get());

        sf::Event event;
        while (window.pollEvent(event) && index >= 0)
        {
            controlador[index]->tratarEvento(event);
        }
    }

    window.close();
}

void Modelo::cerrarVentana()
{
    window.close();
}

void Modelo::dibujarPantalla(Controlador* micontrolador)
{
    window.clear();
    micontrolador->refrescarPantalla();
    window.display();
}

const sf::Texture& Modelo::capturarPantalla(Controlador * micontrolador)
{
    capturando = true;
    capturador.clear();
    micontrolador->refrescarPantalla();
    capturador.display();
    capturando = false;
    return  capturador.getTexture();
}

void Modelo::addController(Controlador* miControlador)
{
    addController(miControlador,index < 0);
}

void Modelo::addController(Controlador* miControlador,bool transicion_puesta)
{
    index++;
    if (index >= controlador.size())
    {
        std::unique_ptr<Controlador> nuevoControlador(miControlador);
        controlador.push_back(std::move(nuevoControlador));
    }
    else
    {
        controlador[index].reset(miControlador);
    }

    if (!transicion_puesta)
    {
        const sf::Texture primero = capturarPantalla(controlador[index-1].get());
        const sf::Texture segundo = capturarPantalla(controlador[index].get());

        fue_transicion = true;

        addController(new Transicion_Desplazamiento(this,primero,segundo,sf::Vector2i(0,-1),AlmacenDeAjustes::getInstancia().getTicks_transicion())
                      ,true);
    //    addController(new Transicion_Fundido(this,primero,segundo,60),true);
       //addController(new Transicion_Transparencia(this,primero,segundo,60),true);
    }
}

void Modelo::finishController()
{
    if (capturando) return;
    //controlador.pop();
    index--;
    if (index <= -1)
    {
        window.close();
    }
    else if (!fue_transicion)
    {
        const sf::Texture primero = capturarPantalla(controlador[index+1].get());
        const sf::Texture segundo = capturarPantalla(controlador[index].get());
        fue_transicion = true;
        addController(new Transicion_Desplazamiento(this,primero,segundo,sf::Vector2i(0,1),AlmacenDeAjustes::getInstancia().getTicks_transicion()),
                      true);
//addController(new Transicion_Fundido(this,primero,segundo,60),true);
        //addController(new Transicion_Transparencia(this,primero,segundo,60),true);
    }
    else
    {
        fue_transicion = false;

        if (desplazar_controlador)
        {
            desplazar_controlador = false;
            controlador[index-1].reset(controlador[index].release());
            index--;
        }
    }
}

//void Modelo::anyadirTransicion(Transicion* miTransicion)
//{
//    const sf::Texture primero = capturarPantalla(controlador[index-1].get());
//    const sf::Texture segundo = capturarPantalla(controlador[index].get());
//    fue_transicion = true;
//    addController(miTransicion,true);
//}
