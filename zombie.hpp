#ifndef zombie_hpp
#define zombie_hpp

#include "color.hpp"

class Zombie {
public:
    Zombie(): x(0), y(0), maxSpeed(0) {}
    Zombie(int x_, int y_, int maxspd, Color col): x(x_), y(y_), maxSpeed(maxspd){
        color = col;
    }
    
    void set(int x_, int y_, int maxspd){
        x = x_; y = y_; maxSpeed = maxspd;
    }
    void setColor(Color col){
        color = col;
    }
    Color getColor(){
        return color;
    }
    
private:
    int x, y, maxSpeed;
    Color color;
    
};

#endif /* zombie_hpp */
