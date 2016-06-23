#include "AlmacenDeAjustes.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const char* nombre_ajustes = "ajustes_serpiente.ini";


/** Convierte de string a float
*/

float convertir(const string &a)
{
    float valor = 0;
    stringstream stream(a);
    stream>>valor;
    return valor;
}

/** Constructor, carga el archivo de ajustes
*/

AlmacenDeAjustes::AlmacenDeAjustes()
{
    ifstream fin(nombre_ajustes);

    /** Inicializa primero los ajustes por defecto
    */

    ajustesPorDefecto();

    /** Si no existe el archivo...
    */

    if (!fin)
    {
        cout<<"Archivo ajustes no abierto"<<endl;

    }
    else
    {
        // Si existe el archivo...

        string linea;

        //Leyendo cabecera...

        getline(fin,linea);

        // Si no tiene la cabecera, entonces nada

        if (linea != "[Serpiente]")
        {
            cout<<"Cabecera no coincide"<<endl;
            //ajustesPorDefecto();
        }
        else
        {
            /** El archivo de configuración es en modo texto, funciona de la siguiente manera:
            *
            * La primera línea es la cabecera, debe ser [Serpiente] , de lo contrario se asume que el archivo no es de la
            * serpiente, y no se continua
            *
            * Las siguientes lineas seran los ajustes, se componen de la siguiente manera:
            *
            * nombre_de_la_variable = valor
            *
            *
            * Por ejemplo, para poner el volumen a 40:
            *
            * volumen = 40
            *
            *
            * Las variables cuyo nombres no existan (o no tengan =) se ignoran, si el valor es de un tipo
            * distinto (una palabra y se esperaba un numero) la variable no se actualiza
            */

            string variable;

            // El simbolo = del medio

            char simbolo = 0;

            // Hasta que acabemos el archivo

            while (fin)
            {
                // Leemos el nombre de la palabra:

                fin>>variable>>simbolo;

                if (simbolo != '=')
                {
                    cout<<"Se obtubo un: "<<simbolo<<" pero se esperaba un ="<<endl;
                    cout<<"El nombre de variable leido es: "<<variable<<endl;
                    continue;
                }
                else
                {
                    if (variable == "delay")
                    {
                        fin>>delay;
                    }
                    else if (variable == "nacrecer")
                    {
                        fin>>NaCrecer;
                    }
                    else if (variable == "volumen")
                    {
                        fin>>volumen;
                    }
                    else if (variable == "incr_crecer")
                    {
                        fin>>incrCrecer;
                    }
                    else if (variable == "ticks_transicion")
                    {
                        fin>>ticks_transicion;
                    }
                    else
                    {
                        cout<<"Error, variable no reconocida: "<<variable<<endl;
                    }
                }
            }
        }
    }
}

AlmacenDeAjustes::~AlmacenDeAjustes()
{
    guardar();
}

void AlmacenDeAjustes::guardar()
{
    ofstream fout(nombre_ajustes);
    fout<<"[Serpiente]"<<endl;
    fout<<"delay = "<< delay<<endl;
    fout<<"incr_crecer = "<<incrCrecer<<endl;
    fout<<"nacrecer = "<<NaCrecer<<endl;
    fout<<"volumen = "<<volumen<<endl;
    fout<<"ticks_transicion = "<<ticks_transicion<<endl;
}

void AlmacenDeAjustes::ajustesPorDefecto()
{
    delay = 60;
    incrCrecer = 10;
    NaCrecer = 0;
    volumen = 100.0;
    ticks_transicion = 45;
    musica = true;
    color_jugador = sf::Color(sf::Color::Red);
}
