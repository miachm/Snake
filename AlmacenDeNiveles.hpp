#ifndef ALMACENDENIVELES_H
#define ALMACENDENIVELES_H
#include "Almacen.hpp"
#include "Nivel.hpp"
#include <string>

/**
*   @brief Objeto single-tin (objeto de una solo creacción), para almacenar y administrar los niveles.
*   Todos los niveles son externos, el constructor carga los niveles de su Carpeta y los guarda.
**/

class AlmacenDeNiveles : public Almacen
{
    public:

        /** \brief Obtiene una instancia de AlmacenDeNiveles, si no existía aún lo crea y si existía devuelve la referencia.
        */
        static AlmacenDeNiveles& getInstancia()
        {
            static AlmacenDeNiveles instancia;
            return instancia;
        }

        /** \brief Carga todos niveles que estén en la carpeta "niveles" del disco, los niveles tienen formato .map.
            Antes de cargarlos, se libera la lista de niveles, por lo que no hay riesgo de que los niveles se cargen dos veces
        */

        void cargarNiveles();

        /** \brief Añade un nuevo nivel a la base de datos (esto crea el archivo .map también).
            \param nivel: El nivel a añadir.
            \param nombre: El nombre del archivo en el que se guardará.
        */

        void anyadirNivel(const Nivel & nivel,const std::string &nombre);

        void borrarNivel(int opcion);

        /** \brief Obtiene el nivel por su número de index (sigue la misma numeración que el vector de getNiveles()).
        *   \param index: Numero de nivel que se quiere obtener
        */

        Nivel& getNivel(int index)
        {
            /** Los niveles aquí se carga de forma "perezosa".
            *
            *   Es decir, hasta que un nivel sea referenciado no se cargan, de esa forma se pueden tener 10.000 niveles
            *   en la base de datos, que se irán cargando conforme se vayan necesitando.
            *
            *   CargarDesdeArchivo() hace las comprobaciones necesarias para evitar recargar el mismo nivel dos veces
            */

            return niveles.at(index).cargarDesdeArchivo(archivos[index].c_str());
        }

        int size() const {return niveles.size();}

    private:
        /** \brief Inicializa la base de datos y carga los niveles
        */

        AlmacenDeNiveles()
        {
            cargarNiveles();
        }

        /** \brief Vector con todos los niveles
        */

        std::vector<Nivel> niveles;
        std::vector<std::string> archivos;
};

#endif // ALMACENDENIVELES_H
