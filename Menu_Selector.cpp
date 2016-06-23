#include "Menu_Selector.hpp"

Menu_Selector::Menu_Selector(sf::Vector2i pos_primero,sf::Vector2i size,sf::Vector3i limit,sf::Vector3i select)

 : items_por_pagina(limit.x*limit.y),pos_inicial(pos_primero),tam(size),
 limites(limit),  seleccion(select)
{
    //ctor
}

bool Menu_Selector::dentroDeEncuadre(int a,int b)
{
        return a >= pos_inicial.x && b>= pos_inicial.y &&
            a <= (pos_inicial.x+limites.x*tam.x) && b < (pos_inicial.y+limites.y*tam.y);
}

void Menu_Selector::tratarEvento(sf::Event & event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        monotorizarTeclado(event);
    }
	else if(event.type==sf::Event::MouseMoved)
	{
		int a,b;
		a = event.mouseMove.x;
		b = event.mouseMove.y;

		if(dentroDeEncuadre(a,b))//si estamos en la zona de las miniaturas
		{
			a = (a-pos_inicial.x) /tam.x;
			b = (b-pos_inicial.y)/tam.y;

            if (getNumElemento(a,b,seleccion.z) != getNumElemento())
            {
                setPositionX(a);
                setPositionY(b);
            }
		}
	}
	else if(event.type == sf::Event::MouseButtonPressed)
	{
           lanzarInstancia(getNumElemento());
	}
	else if(event.type == sf::Event::MouseWheelScrolled)//para cuendo se use la rueda del ratón
	{
		float delta = event.mouseWheelScroll.delta; //indica la direccion del ratón y el grado(solo usaremos el signo para la dirección)

		if(delta>0 && getPositionZ()>0) //ratón hacia arriba y no estamos en la primera pagina
		{
			decrOpcionZ();//pagina--;
		}
		else if(getPositionZ() < limites.z-1 && delta<0) // no estamos en la ultima pagina y raton hacia abajo
		{
		    incrOpcionZ();
			//pagina++;
		}
	}
}


int Menu_Selector::getNumElemento()
{
    return seleccion.x+seleccion.y*limites.x+seleccion.z*items_por_pagina;
}

int Menu_Selector::getNumElemento(int x,int y,int z)
{
    return x+y*limites.x+z*items_por_pagina;
}

void Menu_Selector::monotorizarTeclado(sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) subirOpcion();
    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) abajoOpcion();
    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) izquierdaOpcion();
    if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) derechaOpcion();
    if (event.key.code == sf::Keyboard::PageDown) paginaSiguiente();
    if (event.key.code == sf::Keyboard::PageUp) paginaAnterior();
    if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
    {
        lanzarInstancia(getNumElemento());
    }
}

void Menu_Selector::subirOpcion()
{
	setPositionY((limites.y+getPositionY()-1)%limites.y);
}

void Menu_Selector::abajoOpcion()
{
    setPositionY((getPositionY()+1)%limites.y);
}

void Menu_Selector::izquierdaOpcion()
{
	if (getPositionX() == 0)
    {
        if (getPositionZ() > 0)
        {
            setPositionX(limites.z-1);
            decrOpcionZ();
        }
    }
    else decrOpcionX();
}

void Menu_Selector::derechaOpcion()
{
	if (getPositionX() == limites.x-1)
    {
        if (getPositionZ() < limites.z-1)
        {
            setPositionX(0);
            incrOpcionZ();
        }
    }
    else incrOpcionX();
}


void Menu_Selector::incrOpcionX()
{
    setPositionX(getPositionX()+1);
}

void Menu_Selector::incrOpcionY()
{
    setPositionY(getPositionY()+1);
}

void Menu_Selector::incrOpcionZ()
{
    setPositionZ(getPositionZ()+1);
}

void Menu_Selector::decrOpcionX()
{
    setPositionX(getPositionX()-1);
}

void Menu_Selector::decrOpcionY()
{
    setPositionY(getPositionY()-1);
}

void Menu_Selector::decrOpcionZ()
{
    setPositionZ(getPositionZ()-1);
}

void Menu_Selector::setPositionX(int x)
{
    seleccion.x = x;
    cambiaOpcion();
}
void Menu_Selector::setPositionY(int y)
{
    seleccion.y = y;
    cambiaOpcion();
}

void Menu_Selector::setPositionZ(int z)
{
    int incr = z > seleccion.z? -1 : 1;
    seleccion.z = z;
    cambiaPagina(incr);
}
