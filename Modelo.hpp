#ifndef MODELO_H
#define MODELO_H
#include "Controlador.hpp"
#include <memory>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

//class Transicion;

/**
 * @brief Representa a un modelo de ventana, encapsula los eventos/el dibujado,
 * dejando a los controladores como dibujar y como tratar cada evento. Los controladores se apilan como una pila
 */

class Modelo
{
    public:
		static const int fwidth=640;
		static const int fheight=480;

		/**
         * @brief Crea la ventana y bloquea la llamada hasta que la ventana sea cerrada
         * @param controlador: El controlador inicial que controlar� la ventana.
         */

        Modelo(Controlador* controlador);

        /**
         * @brief A�ade un nuevo controlador a la ventana, el controlador que estaba activo queda suspendido.
         * \note Se realiza un efecto gr�fico de transicion para pasar al siguiente controlador, no se debe llamar dos veces desde el mismo
         * controlador.
         */

        void addController(Controlador*);

        void replaceController(Controlador* contr)
        {
            desplazar_controlador = true;
            addController(contr);
        }

        /**
         * @brief Elimina el �ltimo controlador a�adido y se reactiva el anterior en la pila. Si ya no quedan controladores en la pila,
         * la ventana se cierra
         * \note Una llamada a este metodo cuando no hay controlador activo no tiene efecto
         */

        void finishController();

        /**
         * @brief Cierra la ventana, la ventana deja de ser apta para su uso.
         */

        void cerrarVentana();

        /**
         * @brief Dibuja un objeto en la ventana, este metodo deberia llamarse desde el controlador para ir dibujando los objetos del fotograma
         *
         * \param dibujo: El dibujo a dibujar
         */

        void dibujar(const sf::Drawable & dibujo)
        {
            if (!capturando)
            {
                window.draw(dibujo);
            }
            else
            {
                capturador.draw(dibujo);
            }
        }

        /**
         * @brief Obtiene las coordenadas relativas del mouse respecto a la ventana que gestiona modelo
         */

        sf::Vector2i getMousePosition() const
        {
            return sf::Mouse::getPosition(window);
        }

    private:

        /**
         * \brief Inicia la ventana, y se queda bloqueado hasta su cierre. Se llamar� al controlador para que respondan
         *  a los eventos y refresquen la pantalla
         */

        void start();

        /**
         * \brief Flag que indica que las siguientes llamadas a dibujar, deben dibujar en pantalla o capturar
         */

        bool capturando;

        /**
         * \brief Indica si el �ltimo controlador a�adido fue una transici�n, evita que al borrar una transici�n
         *  se a�ada otra nueva como respuesta a esta y as� indefinidamente
         */

        bool fue_transicion;

        /**
         * \brief Render que cuando el flag capturando = true ,captura un fotograma. Se usa para sacar
         *  capturas para las transiciones
         */

        sf::RenderTexture capturador;

        /**
         * \brief Index del controlador que se est� usando actualmente en el vector de controladores
         */

        int index;

        /**
         * \brief La propia ventana
         */

        sf::RenderWindow window;

        /**
         * \brief Vector de controladores, se van a�adiendo nuevos controladores con addController(),
         * pero no se borran al hacer finishController(), sino que se dejan guardados hasta que sean reemplazados por uno nuevo.
         *  Esto permite al controlador terminar sus cosas despu�s de llamar a finishController()
         */

        std::vector<std::unique_ptr<Controlador> > controlador;

        /**
         * \brief Adiccional a addController, pero tiene un flag que indica si el controlador que se est� a�adiendo es una transici�n
         *  o no. Evita que se a�adan nuevas transiciones como respuesta a a�adir la nueva transici�n
         *
         *  \param Controlador: El controlador a a�adir.
         *  \param bool: Flag que indica si es una transici�n o no, false para indicar que no lo es y true para indicar que lo es
         */

        void addController(Controlador*,bool);

        /**
         * \brief Optione una captura de pantalla de un determinado controlador.
         *
         *  \param micontrolador: El controlador sobre el que se quiere capturar la pantalla.
         *  \return Devuelve la captura en formato textura, llamadas adicionales a capturarPantalla la sobreescribir�n,
         *  por lo que es necesario hacer una copia de esta una vez obtenida.
         */

        const sf::Texture& capturarPantalla(Controlador * micontrolador);

        /**
         * \brief Dibuja en pantalla, usando ese controlador para pedirle el fotograma.
         *
         *  \param El controlador al que se le pedir� el fotograma
         */

        void dibujarPantalla(Controlador* micontrolador);

        bool desplazar_controlador;
};

#endif // MODELO_H
