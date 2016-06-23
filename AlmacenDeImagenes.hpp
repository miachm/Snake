#ifndef ALMACENDEIMAGENES_HPP
#define ALMACENDEIMAGENES_HPP

#include "Almacen.hpp"


class AlmacenDeImagenes : public Almacen
{
public:
    /** \brief Obtiene una instancia de AlmacenDeImagenes, si no existía aún lo crea y si existía lo crea y devuelve la referencia.
    */
    static const AlmacenDeImagenes& getInstancia()
    {
        static const AlmacenDeImagenes instancia;
        return instancia;
    }

    const sf::Texture& getImagenMenu(int i) const {return imagenes_del_menu[i];}
    const sf::Texture& getFlecha() const {return flecha;}
    const sf::Texture& getCreditos() const {return creditos;}

    const sf::Image& getIcono() const {return icono;}

    private:
        AlmacenDeImagenes()
        {
            if (!imagenes_del_menu[0].loadFromFile("./Imagenes/Menu1001.png")) std::cout<<"Imagen Menu1001 no encontrada"<<std::endl;
            if (!imagenes_del_menu[1].loadFromFile("./Imagenes/Menu1002.png")) std::cout<<"Imagen Menu1002 no encontrada"<<std::endl;
            if (!imagenes_del_menu[2].loadFromFile("./Imagenes/Menu1003.png")) std::cout<<"Imagen Menu1003 no encontrada"<<std::endl;
            if (!imagenes_del_menu[3].loadFromFile("./Imagenes/Menu1004.png")) std::cout<<"Imagen Menu1004 no encontrada"<<std::endl;
            if (!imagenes_del_menu[4].loadFromFile("./Imagenes/Menu1005.png")) std::cout<<"IMagen Menu1005 no encontrada"<<std::endl;

            if (!creditos.loadFromFile("./Imagenes/Creditos.png")) std::cout<<"Imagenes Creditos no encontrada"<<std::endl;

            if (!flecha.loadFromFile("./Imagenes/flecha.png")) std::cout<<"Imagen flecha no encontrada"<<std::endl;

            if (!icono.loadFromFile("./Imagenes/Icono.png")) std::cout<<"Imagen icono no encontrado"<<std::endl;
        }
        sf::Texture imagenes_del_menu[5];
        sf::Texture creditos;
        sf::Texture flecha;
        sf::Image icono;
};

#endif // ALMACENDEIMAGENES_HPP
