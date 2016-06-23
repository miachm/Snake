#include "AlmacenDeSonidos.hpp"
#include "AlmacenDeAjustes.hpp"
#include <SFML/Audio.hpp>
#include "MotorDelJuego.hpp"
#include "AlmacenDeFuentes.hpp"

MotorDelJuego::MotorDelJuego(Modelo* m,const Nivel &n) : modelo(m),nivel(n),jugador(n.getCola(),n.getVelocidad()),comida(n,jugador.getGrafico())
                                                        ,juego_activo(true)
{
    //ctor
	soloCabeza = n.getCola().size()==1;

	comida_sonido.setBuffer(AlmacenDeSonidos::getInstancia().getComida());
	muerte_sonido.setBuffer(AlmacenDeSonidos::getInstancia().getMuerte());
    comida_sonido.setVolume(AlmacenDeAjustes::getInstancia().getVolumen());
	muerte_sonido.setVolume(AlmacenDeAjustes::getInstancia().getVolumen());

	tiempo_entre_mov = sf::milliseconds(AlmacenDeAjustes::getInstancia().getDelay());
}

void MotorDelJuego::tratarEvento(sf::Event &event)
{
    if (event.type == sf::Event::Closed) modelo->cerrarVentana();
    if (event.type == sf::Event::KeyPressed)
    {
        if (!juego_activo || event.key.code == sf::Keyboard::Escape) modelo->finishController();
        else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            jugador.setDireccion(sf::Vector2f(0,(float)-Jugador::despl));
        else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            jugador.setDireccion(sf::Vector2f((float)-Jugador::despl,0));
        else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            jugador.setDireccion(sf::Vector2f((float)Jugador::despl,0));
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            jugador.setDireccion(sf::Vector2f(0,(float)Jugador::despl));
    }
}

void MotorDelJuego::refrescarPantalla()
{
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::W )|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up ))
    jugador.setDireccion(sf::Vector2f(0,(float)-Jugador::despl));
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A )|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left ))
   jugador.setDireccion(sf::Vector2f((float)-Jugador::despl,0));
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D )|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right ))

    jugador.setDireccion(sf::Vector2f((float)Jugador::despl,0));
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S )|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  jugador.setDireccion(sf::Vector2f(0,(float)Jugador::despl));

    modelo->dibujar(sf::Sprite(nivel.getRepresentacion()));


    auto miVector = jugador.getGrafico();

    sf::Vector2f posj = jugador.getPosition();

    bool colision=false;

    //pintamos la cabeza primero sino coincidirá con la posicion del jugador (la cabeza)
    auto it = miVector.begin();
    modelo->dibujar(*it);
    it++;

    for (;it != miVector.end();it++)//aqui para el resto del jugador que compare (la cola)
    {
        if(it->getPosition()==posj)
        {
            colision=true;
//            break;
        }
        modelo->dibujar(*it);
    }

	if (juego_activo)
    {

        if (tiempo_pasado.getElapsedTime() >= tiempo_entre_mov)
        {
            jugador.mover();
            tiempo_pasado.restart();
        }

        //cuando crezca desde sólo la cabeza detectara la cola en la misma posicion
        //entonces ignoramos esa colisión

        if( colision)
        {
            if(!soloCabeza)//si no solo tenia la cabeza
            {
                muerte_sonido.play();
                juego_activo = false;
            }
            else//si solo tenia la cabeza y acaba de crecer, lo ignoramos y ponemos el flag a false
                soloCabeza=false;
        }
        else if(comida.teComo(jugador.getPosition()))
        {
            comida_sonido.play();
            jugador.crecer();
        }
        else if (nivel.colision(jugador.getPosition()))
        {
            muerte_sonido.play();

            juego_activo = false;
        }
    }
	else
    {
        sf::Text texto("Juego perdido",AlmacenDeFuentes::getInstancia().getArial());
        texto.setPosition(100,100);
        modelo->dibujar(texto);
    }

        modelo->dibujar(comida.getDibujo());
}

MotorDelJuego::~MotorDelJuego()
{
    comida_sonido.stop();
    muerte_sonido.stop();
}
