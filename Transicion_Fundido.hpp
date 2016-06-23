#ifndef TRANSICION_FUNDIDO_H
#define TRANSICION_FUNDIDO_H

#include "Transicion.hpp"

class Transicion_Fundido : public Transicion
{
    public:
        Transicion_Fundido(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones = 60);
    protected:
        void init(int);

        void animar() override;

    private:
        int incremento;
        sf::Color color_primero;
        sf::Color color_segundo;
        int mitad;
        int brillo;
};

#endif // TRANSICION_FUNDIDO_H
