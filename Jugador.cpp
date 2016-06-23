#include "Jugador.hpp"

#include <iostream>
#include "Nivel.hpp"
using namespace std;

Jugador::Jugador(const std::vector<sf::Vector2i> & pos_inicial,sf::Vector2f vel) : velocidad(sf::Vector2f(Jugador::despl*vel.x,Jugador::despl*vel.y))
{
    cola.resize(pos_inicial.size());

    incremento_comida = 0;

	sf::RectangleShape rec(sf::Vector2f(9.0f,9.0f));
	rec.setFillColor(AlmacenDeAjustes::getInstancia().getColorJugador());
	rec.move(0.5f,0.5f);

	sf::RenderTexture render;
    render.create(10,10);
    render.clear();
	render.draw(rec);
    render.display();

	textura = sf::Texture(render.getTexture());

	sf::Vector2f vec;

    for (unsigned int i = 0;i<pos_inicial.size();i++)
    {
		vec = sf::Vector2f((float)10*pos_inicial[i].x+(10*pos_inicial[i].x)%despl,(float)10*pos_inicial[i].y+(10*pos_inicial[i].y)%despl);
        cola[i].setPosition(sf::Vector2f(vec));
		cola[i].setTexture(textura);
    }
}

void Jugador::setDireccion(sf::Vector2f vec)
{
	if(movido || (velocidad2.x != -vec.x && velocidad2.y != -vec.y) )
	{
		if(velocidad.x != -vec.x && velocidad.y != -vec.y)
		{
			velocidad2=velocidad;
			velocidad = vec;
			movido=false;
		}
	}
}

void Jugador::mover()
{
	actualizarCola();
	cola[0].move(velocidad);
	sf::Vector2f pos = cola[0].getPosition();
	if(pos.x<0 )
		pos.x = 10*(Nivel::TAMX)-despl;
	if(pos.x>=10*Nivel::TAMX)
		pos.x=0;
	if(pos.y <0)
		pos.y = 10*(Nivel::TAMY)-despl;
	if(pos.y >= 10*Nivel::TAMY)
		pos.y=0;
	cola[0].setPosition(pos);
	movido=true;

}

void Jugador::actualizarCola()
{
    for (int i = cola.size()-1;i> 0;i--)
    {
		cola[i].setPosition(cola[i-1].getPosition());
    }
}

void Jugador::crecer()
{
    int N = AlmacenDeAjustes::getInstancia().getIncrCrecer() + incremento_comida;
    incremento_comida += AlmacenDeAjustes::getInstancia().getNaCrecer();

    sf::Vector2f pos(-10,-10);// = cola[cola.size()-1].getPosition();
    cola.resize(cola.size()+N);

    for (unsigned int j = cola.size()-N;j<cola.size();j++)
    {
        cola[j].setPosition(pos);
		cola[j].setTexture(textura);
    }
}
