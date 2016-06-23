#include "Menu.hpp"
#include <iostream>
#include "SelectorNiveles.hpp"
#include "AlmacenDeSonidos.hpp"
#include "Creditos.hpp"
#include "AlmacenDeImagenes.hpp"
#include "Opciones.hpp"
#include "AlmacenDeAjustes.hpp"
#include "EditorDeNiveles.hpp"
#include "MenuEditar.hpp"

const int JUGAR = 0;
const int EDITAR = 1;
const int OPCIONES = 2;
const int CREDITOS = 3;
const int SALIR = 4;


Menu::Menu(Modelo* m) : Menu_Selector(sf::Vector2i(0,posIniOpciones),sf::Vector2i(Modelo::fwidth,60),
                                      sf::Vector3i(1,5,1) ),
                       modelo(m)
{
    for (int i = 0;i<NNIVELES;i++)
    {
        pantallas_del_menu[i].setTexture(AlmacenDeImagenes::getInstancia().getImagenMenu(i));
    }

    menu_enter.setBuffer(AlmacenDeSonidos::getInstancia().getMenu_enter());
    menu_mover.setBuffer(AlmacenDeSonidos::getInstancia().getMenu_mover());

}

void Menu::lanzarInstancia(int opcion)
{

    menu_enter.setVolume(AlmacenDeAjustes::getInstancia().getVolumen());
    menu_enter.play();
    switch (opcion)
    {
        case JUGAR:
                modelo->addController(new SelectorNiveles(modelo));
                break;
        case EDITAR:
//                modelo->addController(new EditorDeNiveles(modelo));
                modelo->addController(new MenuEditar(modelo));
                break;

        case OPCIONES:
                modelo->addController(new Opciones(modelo));
                break;
        case CREDITOS:
                modelo->addController(new Creditos(modelo));
                break;
        case SALIR:
                salir();
                break;
    }
}

void Menu::cambiaOpcion()
{

    menu_mover.setVolume(AlmacenDeAjustes::getInstancia().getVolumen());
    if (menu_mover.getStatus() != sf::SoundSource::Playing)
        menu_mover.play();
}

void Menu::salir()
{
    modelo->finishController();
}

void Menu::tratarEvento(sf::Event &event)
{
    if (event.type == sf::Event::Closed) salir();
    Menu_Selector::tratarEvento(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape) salir();
    }
}

void Menu::refrescarPantalla()
{
    modelo->dibujar(pantallas_del_menu[getNumElemento()]);
}

Menu::~Menu()
{
    menu_mover.stop();
    menu_enter.stop();
}
