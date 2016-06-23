#include "Comida.hpp"
#include "Jugador.hpp"
using namespace std;


Comida::Comida(const Nivel &n,const std::vector<sf::Sprite> &cola) : nivel(n),cola_jugador(cola)
{
    // Prepara el sprite de la comida

	sf::RectangleShape rec(sf::Vector2f(9.f,9.f));

	rec.setFillColor(sf::Color::Yellow);

	sf::RenderTexture render;

    render.create(10,10);
    render.clear();
	render.draw(rec);
    render.display();

    textura_comida = render.getTexture();

	comida = sf::Sprite(textura_comida);

	ponerComida();
}

bool Comida::teComo(sf::Vector2f pos)
{
	//int px=comida.getPosition().x-pos.x,py=comida.getPosition().y-pos.y;
	if (comida.getPosition()!= pos)return false;//(px>3||px<-1) &&(py>3 || py <-1)) return false;
    else
    {
        ponerComida();
        return true;
    }
}

void Comida::ponerComida()
{
    do
    {
		comida.setPosition(Jugador::despl*(rand()%(Nivel::TAMX*10/Jugador::despl)),Jugador::despl*(rand()%(Nivel::TAMY*10/Jugador::despl)));
    } while(colision());
}


bool Comida::colision()
{
	sf::Vector2f pos = comida.getPosition();
	if(nivel.colision(pos))
		return true;

	for(auto it = cola_jugador.cbegin(); it!=cola_jugador.cend();it++)
	{
		if(it->getPosition()==pos)
			return true;
	}

	return false;
}
