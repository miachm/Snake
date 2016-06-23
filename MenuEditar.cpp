#include "MenuEditar.hpp"
#include "AlmacenDeFuentes.hpp"
#include "EditorDeNiveles.hpp"
#include "SelectorNiveles.hpp"

MenuEditar::MenuEditar(Modelo* m):Menu_Selector(sf::Vector2i(0,120),sf::Vector2i(Modelo::fwidth,100),
                                      sf::Vector3i(1,3,1))
                       ,modelo(m)
{
    normal.setFont(AlmacenDeFuentes::getInstancia().getCalibri());
    seleccionado.setFont(AlmacenDeFuentes::getInstancia().getCalibri());

    normal.setCharacterSize(48);
    seleccionado.setCharacterSize(48);
    seleccionado.setColor(sf::Color::Yellow);
}

void MenuEditar::refrescarPantalla()
{
    int despl= 100;
    int posy=100;
    int posx = 100;

    normal.setString(std::string("Nuevo"));
    normal.setPosition(posx,posy);
    modelo->dibujar(normal);


    normal.setString(std::string("Editar"));
    normal.setPosition(posx,posy+despl);
    modelo->dibujar(normal);


    normal.setString(std::string("Borrar"));
    normal.setPosition(posx,posy+2*despl);
    modelo->dibujar(normal);

    switch(getPositionY())
    {
        case 0:
            seleccionado.setString(std::string("Nuevo"));
            seleccionado.setPosition(posx,posy);
            modelo->dibujar(seleccionado);
            break;
        case 1:
            seleccionado.setString(std::string("Editar"));
            seleccionado.setPosition(posx,posy+despl);
            modelo->dibujar(seleccionado);
            break;
        case 2:
            seleccionado.setString(std::string("Borrar"));
            seleccionado.setPosition(posx,posy+2*despl);
            modelo->dibujar(seleccionado);
            break;
    }

}

void MenuEditar::lanzarInstancia(int opcion)
{
    switch(opcion)
    {
        case 0:
            modelo->addController(new EditorDeNiveles(modelo));
            break;
        case 1:
            modelo->addController(new SelectorNiveles(modelo,1));
            break;
        case 2:

            modelo->addController(new SelectorNiveles(modelo,2));
            break;
    }
}

MenuEditar::~MenuEditar()
{
    //dtor
}
