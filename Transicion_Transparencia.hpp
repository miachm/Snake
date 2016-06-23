#ifndef TRANSICION_TRANSPARENCIA_HPP
#define TRANSICION_TRANSPARENCIA_HPP

#include "Transicion.hpp"


class Transicion_Transparencia : public Transicion
{
    public:
        Transicion_Transparencia(Modelo* m,const sf::Texture& anterior,const sf::Texture& siguiente,const int iteraciones = 60);
    protected:
        void init(int);
        void animar() override;
    private:
        int transparencia;
        int incr;
};

#endif // TRANSICION_TRANSPARENCIA_HPP
