#ifndef territory_hpp
#define territory_hpp

#include <vector>
#ifdef _WIN32
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif
#include "zombie.hpp"

#define CELL_EMPTY 0
#define CELL_PLAYER 1
#define CELL_TERRITORY 2
#define CELL_TRACE 3
#define CELL_ZOMBIE -1
// 좀비는 -1, -2, -3, ... 해서 좀비 넘버에 따라 색깔이 다름.

class Territory {
public:
    Territory(int w, int h);
    ~Territory();
    Territory(const Territory& t);
    Territory& operator=(const Territory& t);
    int operator()(unsigned int i, unsigned int j){return map[i][j];}
    
private:
    int width, height;
    int** map;
    std::vector<Zombie> zombies;
    int playerX, playerY;
    
public:
    void setPlayerPosition(int x, int y);
    void setPlayerTerritory(int x1, int y1, int x2, int y2);
    void update();
    void createZombies(int n, int maxSpeed);
    void drawMap(float pixelPerCell, float pixelX, float pixelY);
    
private:
    float randFloat(){
        return (float)(rand() % 1001) / 1000.0f;
    }
    void drawCell(int state, float pixelPerCell, float pixelX, float pixelY);
    
};

#endif /* territory_hpp */
