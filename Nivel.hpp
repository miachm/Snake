#ifndef NIVEL_H
#define NIVEL_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include "Jugador.hpp"
#include <algorithm>

class Nivel
{
    public:
        Nivel();
        Nivel(const char*);
        Nivel(const std::string &);

        Nivel& cargarDesdeArchivo(const char*);
        Nivel& recargarDesdeArchivo(const char* n)
        {
            inicializado = false;
            return cargarDesdeArchivo(n);
        }

        void guardarArchivo(const char*) const;
        sf::Vector2f getPosicionInicialJugador() const {return Posicion_Jugador;}
        sf::Vector2f getVelocidad() const { return Movimiento_Inicial;}
		std::vector<sf::Vector2i> getCola() const { return colaJugador;}

		bool colision(sf::Vector2f pos) const
		{
			int posx = (int)pos.x/10;
			int posy = (int)pos.y/10;
			int dx=(int)(pos.x)%10,dy = (int)(pos.y)%10;
			if(mat[posx][posy]=='X')
				return true;
			if(posx < TAMX-1 && mat[posx+1][posy]=='X' && dx>1)
				return true;
			if(posx < TAMY-1 && mat[posx][posy+1]== 'X' && dy>1)
				return true;
			return false;
		}
        void setCasilla(int i,int j,char valor)
        {
        	setCasilla(sf::Vector2i(i,j),valor);
        }
    	void setCasilla(sf::Vector2i pos,char valor)
    	{
    	    inicializado = true;
    		mat[pos.x][pos.y]= valor;
            //generarImagen();
    	}

        void anyadirCasillaJugador(sf::Vector2i pos)
    	{
    	    colaJugador.push_back(pos);
    	}

        void generarImagen();

        void generarImagenJugador()
        {
            generarImagen();

            //pintamos la cabeza primero sino coincidirá con la posicion del jugador (la cabeza)

            sf::RectangleShape rectangulo(sf::Vector2f(10,10));
            rectangulo.setFillColor(sf::Color::Yellow);

            sf::RenderTexture render;

            render.create(Modelo::fwidth,Modelo::fheight);

            render.draw(sf::Sprite(Imagen));

            for (auto it = colaJugador.begin();it != colaJugador.end();it++)//aqui para el resto del jugador que compare (la cola)
            {
                rectangulo.setPosition(it->x*10,it->y*10);
                render.draw(rectangulo);
            }

            render.display();

            Imagen = sf::Texture(render.getTexture());
        }

        void borrar(int i,int j)
        {
            borrar(sf::Vector2i(i,j));
        }

        void borrar(sf::Vector2i pos){
            auto it = find(colaJugador.begin(),colaJugador.end(),pos);

            if (it != colaJugador.end())
            {
                colaJugador.erase(it);
            }
        }

        void setMovimientoInicial(sf::Vector2f v)
        {
            Movimiento_Inicial=v;
        }

        const sf::Texture& getRepresentacion() const {return Imagen;}

        bool operator==(const Nivel& nivel)
        {
            if (nivel.colaJugador != colaJugador) return false;
            else
            {
                for (int i = 0;i<TAMX;i++)
                {
                    for (int j = 0;j<TAMY;j++)
                    {
                        if (mat[i][j] != nivel.mat[i][j]) return false;
                    }
                }
                return true;
            }
        }

        static const int TAMX = 64;
        static const int TAMY = 48;
    private:
    	sf::Vector2f Posicion_Jugador;
    	sf::Vector2f Movimiento_Inicial;
        sf::Texture Imagen;
    	char mat[TAMX][TAMY];

		static const char fillChar = '-';

		std::vector<sf::Vector2i> colaJugador;
		bool inicializado;

};

#endif // NIVEL_H
