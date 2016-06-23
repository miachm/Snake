#include "Nivel.hpp"
#include <fstream>
#include <iostream>
using namespace std;

std::unique_ptr<sf::Texture> imagen_ladrillo;

void cargarImagenLadrillo()
{
    if (imagen_ladrillo == nullptr)
    {
        sf::RenderTexture render;
        render.create(10,10);
        render.clear();

        //tamaño total -> resultado n x n
        int n= 10;

        float marg=3.f;

        sf::Color c1 = sf::Color::Blue;
        sf::Color c2(0,255,255);// = sf::Color::Teal;

        sf::RectangleShape rec1(sf::Vector2f((float)n,(float)n));
        rec1.setPosition(0,0);
        rec1.setFillColor(c1);

        sf::RectangleShape rec2(sf::Vector2f((float)n*(10-marg)/10,(float)n*(10-marg)/10));

        rec2.setPosition(marg*n/20,marg*n/20);
        rec2.setFillColor(c2);

        sf::RectangleShape rec3(sf::Vector2f((float)n*3/10,(float)n/10));
        rec3.setFillColor(c1);
        rec3.setPosition((float)(n*(10-2.9294)/10),(float)(n*9/10));
        rec3.setRotation(-45);

        render.draw(rec1);
        render.draw(rec2);
        render.draw(rec3);

        render.display();
        imagen_ladrillo = std::unique_ptr<sf::Texture>(new sf::Texture(render.getTexture()));
    }
}

Nivel::Nivel()
{
	for (int i = 0; i < TAMX; ++i)
	{
	    for (int j = 0; j < TAMY; ++j)
	    {
	    	mat[i][j] = '-';
	    }
	}
	cargarImagenLadrillo();

	inicializado = false;
}

Nivel::Nivel(const char* nombre)
{
    cargarImagenLadrillo();
    cargarDesdeArchivo(nombre);
}

Nivel::Nivel(const string & nombre)
{
    cargarImagenLadrillo();
    cargarDesdeArchivo(nombre.c_str());
}

Nivel& Nivel::cargarDesdeArchivo(const char* nombre)
{
    if (inicializado) return *this;

	std::ifstream fin(nombre);

	if (!fin) throw "Archivo no encontrado";

	fin>>Posicion_Jugador.x>>Posicion_Jugador.y;
	fin>>Movimiento_Inicial.x>>Movimiento_Inicial.y;

    int tam;
	fin >> tam;
	int numx,numy;

	colaJugador.push_back((sf::Vector2i)Posicion_Jugador);
	for(int i = 0; i < tam; i++)
	{
		fin >> numx >> numy;
		colaJugador.push_back(sf::Vector2i(numx,numy));
	}

	fin.ignore();
	string linea;
	for (int i = 0; i < TAMX; ++i)
	{
		getline(fin,linea);
	    for (int j = 0; j < TAMY; ++j)
	    {
			mat[i][j]=linea[j];
			if(mat[i][j]==fillChar)
				mat[i][j]='-';
	    }
	}

	inicializado = true;
	generarImagen();

	return *this;
}

void Nivel::guardarArchivo(const char* nombre) const
{
	std::ofstream fout(nombre);

	fout<<colaJugador[0].x<< " " <<colaJugador[0].y<<endl;
	fout<<Movimiento_Inicial.x<< " " <<Movimiento_Inicial.y<<endl;

	fout << colaJugador.size()-1 << endl;

	for(unsigned int i = 1; i <colaJugador.size(); i++)
	{
		fout << colaJugador[i].x << ' ' << colaJugador[i].y << endl;
	}

	for (int j = 0; j < TAMX; ++j)
	{
	    for (int i = 0; i < TAMY; ++i)
	    {
	    	fout<<mat[j][i];
	    }
	    fout<<endl;
	}

}

void Nivel::generarImagen()
{
    if (!inicializado) throw "Error en Nivel::generarImagen, el nivel no esta inicializado";

	sf::RenderTexture renderizador;
	renderizador.create(640,480);

	sf::Sprite ladrillo;
	ladrillo.setTexture(*imagen_ladrillo);

	renderizador.clear();

	for (int j = 0; j < TAMY; ++j)
	{
	    for (int i = 0; i < TAMX; ++i)
	    {
	    	if (mat[i][j] == 'X')
	    	{
	    		ladrillo.setPosition((float)i*10,(float)j*10);
	    		//circulo.setPosition((float)i*10,(float)j*10);
	    		renderizador.draw(ladrillo);
	    	}
	    }
	}

	renderizador.display();
	Imagen = sf::Texture(renderizador.getTexture());
}
