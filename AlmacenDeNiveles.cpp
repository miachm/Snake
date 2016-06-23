#include "AlmacenDeNiveles.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

const string carpeta = "./Niveles/";

// Este nombre de archivo acaba en .map?

bool acabaEnPuntoMap(const string &ruta)
{
    return ruta.size() > 4 && ruta.substr(ruta.size()-4,4) == ".map";
}

// Recorre la carpeta "Niveles", coge todos los archivos acabados en map y los mete en un vector de strings

vector<string> recorrerCarpeta(string nombre)
{
    vector<string> archivos;
    DIR *dir;
    dirent *ent;

    if ((dir = opendir (nombre.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        string ruta = nombre + ent->d_name;

        if (acabaEnPuntoMap(ruta))
        {
            archivos.push_back(ruta);
            //cout<<ruta<<endl;
        }
      }
      closedir (dir);
    }
    else
    {
        throw "No se pudo abrir el directorio";
    }
    return archivos;
}

void AlmacenDeNiveles::cargarNiveles()
{
    niveles.clear();
    archivos = recorrerCarpeta(carpeta); // Obtengo todos los archivos acbados en punto map

    //Alternativa
	//vector<string> archivos = leerIndiceNiveles("./niveles/");

    // Preparo el vector de niveles pero no los inicializo, los cargaré de forma peresoza (cuando no tenga más remedio)
    // Vease el metodo getNivel() de esta misma clase

    niveles.resize(archivos.size());
}

void AlmacenDeNiveles::anyadirNivel(const Nivel & nivel,const string &nombre)
{
    string ruta = carpeta+nombre;
    nivel.guardarArchivo(ruta.c_str());
    niveles.push_back(nivel);
}

void AlmacenDeNiveles::borrarNivel(int opcion)
{
    //string ruta = carpeta+nombre;
    remove(archivos.at(opcion).c_str());

    niveles.erase(niveles.begin()+opcion);
}
/*
vector<string> AlmacenDeNiveles::leerIndiceNiveles(string carpeta)
{
	string ind = carpeta+"nivel.index";
	string niv;
	vector<string> vniveles;

	ifstream fin(ind);

	if(!fin)throw "Indice de niveles no encontrado";

	fin >> nniveles;
	fin.ignore();

	for(int i = 0; i < nniveles;i++)
	{
		getline(fin,niv);
		niv = carpeta+niv;
		vniveles.push_back(niv);
	}

	return vniveles;
}*/
