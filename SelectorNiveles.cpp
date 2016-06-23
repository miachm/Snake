#include "SelectorNiveles.hpp"
#include <SFML/Graphics.hpp>
#include "MotorDelJuego.hpp"
#include "AlmacenDeSonidos.hpp"
#include "AlmacenDeNiveles.hpp"
#include "AlmacenDeFuentes.hpp"
#include "AlmacenDeImagenes.hpp"
#include "EditorDeNiveles.hpp"
#include <sstream>
using namespace std;

SelectorNiveles::SelectorNiveles(Modelo* m, int op) : Menu_Selector(sf::Vector2i(0,0),sf::Vector2i(10+Modelo::fwidth*escala,10+Modelo::fheight*escala),
                                     sf::Vector3i(LIMIT_X,LIMIT_Y,1)),
                                      fuente(AlmacenDeFuentes::getInstancia().getArial()),modelo(m), opcionLanzarInstancia(op)
                                     // niveles(AlmacenDeNiveles::getInstancia().getNiveles())

{
    transicion = nullptr;


    const int tam = AlmacenDeNiveles::getInstancia().size();
	setPaginas((tam/(niveles_por_pagina))+1);
	capturador.create(Modelo::fwidth,Modelo::fheight);

    menu_enter.setBuffer(AlmacenDeSonidos::getInstancia().getMenu_enter());
    menu_mover.setBuffer(AlmacenDeSonidos::getInstancia().getMenu_mover());

    menu_enter.setVolume(AlmacenDeAjustes::getInstancia().getVolumen());
    menu_mover.setVolume(AlmacenDeAjustes::getInstancia().getVolumen());

    //textura_flecha.loadFromFile("./Imagenes/flecha.png");
    flecha_izquierda.setTexture(AlmacenDeImagenes::getInstancia().getFlecha());
    flecha_derecha.setTexture(AlmacenDeImagenes::getInstancia().getFlecha());

    flecha_izquierda.rotate(180.0);   //getTransform().rotate(180.0);

    flecha_izquierda.setPosition(30,Modelo::fheight-10);
    flecha_derecha.setPosition(Modelo::fwidth-30,Modelo::fheight-40);
}

void SelectorNiveles::lanzarInstancia(int opcion)
{

    menu_enter.play();


    const int tam = AlmacenDeNiveles::getInstancia().size();


    if(opcionLanzarInstancia==0)
    {
        if (opcion < tam)
            modelo->addController(new MotorDelJuego(modelo,AlmacenDeNiveles::getInstancia().getNivel(opcion)));
        else
            modelo->addController(new MotorDelJuego(modelo,AlmacenDeNiveles::getInstancia().getNivel(rand()%tam)));
    }
    else if (opcionLanzarInstancia==1)// editar
    {
        if (opcion < tam)
            modelo->replaceController(new EditorDeNiveles(modelo,AlmacenDeNiveles::getInstancia().getNivel(opcion)));
    }
    else// borrar
    {
         //   std::cout<<"Borrar"<<std::endl;
         if (opcion < tam)
         {
            AlmacenDeNiveles::getInstancia().borrarNivel(opcion);
            modelo->finishController();
         }
        //if (opcion < tam)
            //modelo->replaceController(new EditorDeNiveles(modelo,AlmacenDeNiveles::getInstancia().getNivel(opcion)));
    }
}

void SelectorNiveles::tratarEvento(sf::Event & event)
{
    if (event.type == sf::Event::Closed) cerrarVentana();
    if (transicion == nullptr)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            int a,b;
            a = modelo->getMousePosition().x;//event.mouseMove.x;
            b = modelo->getMousePosition().y;

            if (flecha_izquierda.getGlobalBounds().contains(a,b))
            {
                paginaAnterior();
    //            refrescarPantalla();
    //            transicion = new Transicion_Desplazamiento(modelo,captura_anterior,captura,sf::Vector2i(1,0),45);

            }
            else if (flecha_derecha.getGlobalBounds().contains(a,b))
            {
               //
                paginaSiguiente();
    //            refrescarPantalla();
    //            transicion = new Transicion_Desplazamiento(modelo,captura_anterior,captura,sf::Vector2i(-1,0),45);
            }
            else Menu_Selector::tratarEvento(event);
        }
        else Menu_Selector::tratarEvento(event);

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) salir();
        }
    }
}

void SelectorNiveles::salir()
{
    modelo->finishController();
}

void SelectorNiveles::cambiaOpcion()
{
    //if (menu_mover.getStatus() != sf::SoundSource::Playing)
    menu_mover.stop();
    menu_mover.play();
}

void SelectorNiveles::cerrarVentana()
{
    modelo->cerrarVentana();
}

std::string toString(int N)
{
    std::stringstream ss;
    ss<<N;
    return ss.str();
}

std::string obtenerNivel(int N)
{
    std::stringstream ss;
    ss<<"Nivel "<<N;
    return ss.str();
}

void SelectorNiveles::refrescarPantalla()
{
    if (transicion == nullptr)
    {
        captura_anterior = captura;

        capturador.clear();

        int pagina = getPositionZ();
        sf::Text texto;
        texto.setFont(fuente);
        texto.setColor(sf::Color::Green);
        texto.setCharacterSize(12);

        sf::Text texto_paginas;
        texto_paginas.setFont(fuente);
        texto_paginas.setCharacterSize(10);
        texto_paginas.setString(std::string("Pagina: ") + toString(pagina+1) + "/" + toString(getLimites().z));
        texto_paginas.setPosition(Modelo::fwidth/2-50,Modelo::fheight-20);
        modelo->dibujar(texto_paginas);
        capturador.draw(texto_paginas);

        if (pagina > 0)
        {
            modelo->dibujar(flecha_izquierda);
            capturador.draw(flecha_izquierda);
        }

        if (pagina < getLimites().z-1)
        {
            modelo->dibujar(flecha_derecha);
            capturador.draw(flecha_derecha);
        }

        sf::Sprite nivel;
        nivel.setScale(escala,escala);

        sf::RectangleShape seleccion_c(sf::Vector2f((float)wnivel+10,(float)hnivel+10));
        seleccion_c.setFillColor(sf::Color::Red);
        seleccion_c.setPosition(getPositionX()*wnivel,getPositionY()*hnivel);

        modelo->dibujar(seleccion_c);
        capturador.draw(seleccion_c);
        //int max = (pagina+1)*niveles_por_pagina > niveles.size() ? niveles.size() : (pagina+1)*niveles_por_pagina;

        for (int i = LIMIT_X-1;i>=0;i--)
        {
            for (int j = LIMIT_Y-1;j>=0;j--)
            {
                if (i+j*LIMIT_X+getPositionZ()*niveles_por_pagina < AlmacenDeNiveles::getInstancia().size())
                {
                    const sf::Texture& tex = AlmacenDeNiveles::getInstancia().getNivel(getNumElemento(i,j,getPositionZ())).getRepresentacion();
                    nivel.setTexture(tex);
                    nivel.setPosition((float)i*wnivel+10,(float)j*hnivel+10);
                    texto.setPosition((float)i*wnivel+10,(float)j*hnivel+hnivel-10);
                    texto.setString(obtenerNivel(getNumElemento(i,j,getPositionZ())));

                    modelo->dibujar(nivel);
                    capturador.draw(nivel);

                    modelo->dibujar(texto);
                    capturador.draw(texto);
                }
            }
        }

        capturador.display();
        captura = sf::Texture(capturador.getTexture());
    }
    else
    {
        transicion->refrescarPantalla();

        if (!transicion->getTicks())
        {
            delete transicion;
            transicion = nullptr;
        }
    }
}

SelectorNiveles::~SelectorNiveles()
{
    menu_mover.stop();
    menu_enter.stop();
    delete transicion;
}
