#include "EditorDeNiveles.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "AlmacenDeNiveles.hpp"
using namespace std;

EditorDeNiveles::EditorDeNiveles(Modelo* m) : Menu_Selector(sf::Vector2i(0,0),sf::Vector2i(10,10),sf::Vector3i(64,48,1))
                                            ,modelo(m)
{
    //ctor
    nivel.setCasilla(getPosition().x,getPosition().y,' ');
    nivel.setMovimientoInicial(sf::Vector2f(1,0));

}

EditorDeNiveles::EditorDeNiveles(Modelo* m,Nivel& n) : Menu_Selector(sf::Vector2i(0,0),sf::Vector2i(10,10),sf::Vector3i(64,48,1))
                                            ,modelo(m)
{
    //ctor
    nivel = n;
    nivel.setCasilla(getPosition().x,getPosition().y,'-');
    nivel.setMovimientoInicial(sf::Vector2f(1,0));

}

void EditorDeNiveles::tratarEvento(sf::Event &event)
{
    if (event.type == sf::Event::Closed) modelo->cerrarVentana();
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape) salir();
//        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
//        {
//            if (seleccion.x > 0) seleccion.x--;
//        }
//        else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
//        {
//            if (seleccion.x < Nivel::TAMX-1) seleccion.x++;
//        }
//        else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
//        {
//            if (seleccion.y > 0) seleccion.y--;
//        }
//        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
//        {
//            if (seleccion.y < Nivel::TAMY-1) seleccion.y++;
//        }
        else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
        {
            ponerLadrillo();
        }
        else if (event.key.code == sf::Keyboard::H)
        {
            ponerCabeza();
        }

        else if(event.key.code==sf::Keyboard::E) SalirSinGuardar();
        else Menu_Selector::tratarEvento(event);
    }
    else Menu_Selector::tratarEvento(event);


//    else if(event.type = sf::Event::MouseMoved)
//    {
//        int x y;
//
//        x = event.
//
//    }
}

string convertir(int a)
{
    stringstream stream;
    stream<< (a<10?"00":(a<100?"0":"")) << a;
    return stream.str();
}


void EditorDeNiveles::salir()
{
   // nivel.guardarArchivo("./Niveles/Ficherito.map");
   ifstream fin;
   int n = -1;
   string nombre = "Nivel";
   do
   {
       fin.clear();
        n++;
       fin.close();
       fin.open(string(string("./Niveles/")+nombre+convertir(n)+".map").c_str());
   }
    while (fin);
    cout<<string(nombre+convertir(n)+".map").c_str()<<endl;

    //nivel.guardarArchivo(string(nombre+convertir(n)+".map").c_str());
    nivel.generarImagen();
    AlmacenDeNiveles::getInstancia().anyadirNivel(nivel,string(nombre+convertir(n)+".map").c_str());
    modelo->finishController();
}

void EditorDeNiveles::ponerLadrillo()
{
    nivel.setCasilla(getPosition().x,getPosition().y,'X');
}

void EditorDeNiveles::ponerCabeza()
{
    //nivel.setCasilla(getPosition().x,getPosition().y,'H');
    nivel.anyadirCasillaJugador(sf::Vector2i(getPosition().x,getPosition().y));
}

void EditorDeNiveles::borrar()
{
    nivel.setCasilla(getPosition().x,getPosition().y,'-');
    nivel.borrar(getPosition().x,getPosition().y);
}

void EditorDeNiveles::refrescarPantalla()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) ponerLadrillo();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) borrar();

    nivel.generarImagenJugador();
    modelo->dibujar(sf::Sprite(nivel.getRepresentacion()));

    sf::RectangleShape seleccion_c(sf::Vector2f(10,10));

    seleccion_c.setFillColor(sf::Color::Red);
    //seleccion_c.setOutlineColor(sf::Color::Red);
    seleccion_c.setPosition(getPosition().x*10,getPositionY()*10);
    modelo->dibujar(seleccion_c);


}
