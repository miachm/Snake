#ifndef ALMACEN_H
#define ALMACEN_H

/**
*   @brief Representa un objeto single-tin (objeto de una solo creacción), la copia está desactivada y el constructor por defecto está protegido
    \note Las clases hijas deben añadir una instancia estática en su clase que podrán devolver al usuario con un método getInstancia().
          Este tipo de clases, están pensadas para ser usados en objetos donde la copia/duplicidad de los datos, no es admisible. Por ejemplo,
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
        @brief Constructor protegido, para evitar su instanciación desde fuera
        **/
        Almacen(){}
};

#endif // ALMACENDEAJUSTES_H
