#ifndef zombie_hpp
#define zombie_hpp

#include "color.hpp"

class Zombie {
public:
    Zombie(){}
    Zombie(int x_, int y_, Color col): x(x_), y(y_), color(col) {}
    
    void moveUP();
    void moveDOWN();
    void moveLEFT();
    void moveRIGHT();
    
    int getX(){return x;}
    int getY(){return y;}
    Color getColor(){return color;}

private:
    int x, y;
    Color color;
};

#endif /* zombie_hpp */
