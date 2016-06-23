#ifndef MENU_H
#define MENU_H
#include "Modelo.hpp"
#include "Menu_Selector.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/** \brief Controlador que gestiona el menú principal, se lanza nada más iniciar el juego y posee 4 opciones:
 *  Jugar,Editor De niveles, Opciones, Créditos y Salir
 */


class Menu : public Controlador,Menu_Selector
{
    public:

        /** \brief Construye el menú, carga las imagenes del disco duro (carpeta Imagenes) y lo deja listo para ser dibujado
         *  \param m: Puntero al modelo que lleva la ventana, se usa para poder enviarle las ordenes (dibujar, cerrarventana,
         *  añadir controlador, eliminar este controlador, etc...).
         */

        Menu(Modelo* m);

        /** \brief Detiene/Para cualquier sonido que estuviera activo, de esa forma se evita que el sonido siga reproduciendose
         *  cuando el controlador se ha destruido
         */

        ~Menu();

        /** \brief Trata los eventos de la ventana, esta función también redirige algunos eventos a Menu_Selector
         *  para su gestión
         */

        void tratarEvento(sf::Event &) override;

        /** \brief Pinta la pantalla.
         */

        void refrescarPantalla() override;
    private:

        /** \brief Referencia al modelo que gestiona la ventana, para mandarle ordenes */

        Modelo* modelo;

        /** \brief Wrapper en sprite para las 5 imagenes del menú, para que puedan ser dibujadas
        */

        sf::Sprite pantallas_del_menu[5];

        /** \brief Sonido que se reproduce cuando se cambia una opción del menú, notesé que no es lo mismo sound (controlador de sonido) que
        *   soundbuffer (datos del sonido), el soundbuffer es un objeto pesado y que se encuentra unicamente en el AlmacenDeSonidos
        */

        sf::Sound menu_mover;

        /** \brief Sonido que se reproduce cuando se hace click/enter en una opción del menú, notesé que no es lo mismo sound (controlador de sonido) que
        *   soundbuffer (datos del sonido), el soundbuffer es un objeto pesado y que se encuentra unicamente en el AlmacenDeSonidos
        */

        sf::Sound menu_enter;

        /** \brief Sobreescribe el callback lanzarinstancia, que es lanzado por menu_selector cuando se selecciona una opción del menú
        */

        void lanzarInstancia(int) override;

        /** \brief Sobreescribe el callback lanzarinstancia, que es lanzado por menu_selector cuando se cambia de opción del menú
        */

        void cambiaOpcion() override;

        /** \brief Para salir del menú, se usa tanto cuando se selecciona la opción Salir como cuando se pulsa escape,
        *   esta función lo que hace es llamar a modelo para que le borre como controlador (finishController)
        */

        void salir();

        /** \brief Numero de opciones que tiene el menú
        */

		static const int NNIVELES = 5;

        /** \brief Coordenada (Y) desde donde empieza el menú
        */

		static const int posIniOpciones=140;

        /** \brief Coordenada (Y) desde donde termina el menú
        */

		static const int posFinOpciones=480;
};

#endif // MENU_H
