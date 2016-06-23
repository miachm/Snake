#ifndef ALMACEN_H
#define ALMACEN_H

/**
*   @brief Representa un objeto single-tin (objeto de una solo creacci�n), la copia est� desactivada y el constructor por defecto est� protegido
    \note Las clases hijas deben a�adir una instancia est�tica en su clase que podr�n devolver al usuario con un m�todo getInstancia().
          Este tipo de clases, est�n pensadas para ser usados en objetos donde la copia/duplicidad de los datos, no es admisible. Por ejemplo,
          un objeto que almacene los ajustes del juego.
**/

class Almacen
{

    Almacen(Almacen &) = delete;
    void operator=(Almacen &) = delete;
    Almacen(const Almacen &) = delete;
    void operator=(const Almacen &) = delete;

    protected:

        /**
        @brief Constructor protegido, para evitar su instanciaci�n desde fuera
        **/
        Almacen(){}
};

#endif // ALMACENDEAJUSTES_H
