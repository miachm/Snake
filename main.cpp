#include "Modelo.hpp"
#include "Menu.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/** Modelo de programación actual:
*
* - Objecto Modelo que gestiona los accesos a ventana, deja el decidir "qué" se dibuja a los Controladores.
* - Controladores: Ente que recibe los eventos/refrescos de fotograma y responde en consecuencia llamando
    a la API que nos proporciona modelo (dibujar,cerrarventana,addcontroller...).

Problema con esto:

- Se pueden llamar dos veces seguidas a la API (cerrarventana, finishcontroller), con los perjuicios y errores extraños que
    eso resulta.
*/

int main()
{
	try
	{
	    std::srand(std::time(0));
	    Modelo modelo(new Menu(&modelo));
	}
	catch(const char* c)
	{
		std::cout<<"Excepcion ocurrida: "<<c<<std::endl;
	}
	//std::cin.get();
    return 0;
}
