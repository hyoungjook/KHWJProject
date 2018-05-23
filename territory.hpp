#ifndef territory_hpp
#define territory_hpp

#include <vector>
#include <tuple>
#include <queue>
#ifdef _WIN32
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif
#include "color.hpp"
#include "zombie.hpp"
#include "object.hpp"

enum Direction{
    STOP, UP, DOWN, LEFT, RIGHT
};

class Territory {
public:
    Territory(int w, int h);
    ~Territory();
    Territory(const Territory& t);
    Territory& operator=(const Territory& t);
    int operator()(unsigned int i, unsigned int j){return map[i][j];}
    void setPlayerDirection(Direction dir){playerDirection = dir;}
    float getPlayerGLUX(float inter){
        float adder = 0;
        if(playerDirection == RIGHT) adder = 0.2f * inter;
        if(playerDirection == LEFT) adder = -0.2f * inter;
        return 0.2f * (float)(playerX - width/2) + adder;
    }
    float getPlayerGLUZ(float inter){
        float adder = 0;
        if(playerDirection == DOWN) adder = 0.2f * inter;
        if(playerDirection == UP) adder = -0.2f * inter;
        return 0.2f * (float)(playerY - height/2) + adder;
    }
    
private:
    int width, height; // 칸 수
    bool** map; // 플레이어 영토 정보
    std::vector<Zombie> zombies;
    int playerX, playerY;
    int playerInitialX, playerInitialY;
    Direction playerDirection = STOP;
    std::vector<std::tuple<int, int> > trace; // 플레이어 흔적 정보
    int lives = 3;
    
    
public:
    void setPlayerPosition(int x, int y);
    void setPlayerTerritory(int x1, int y1, int x2, int y2);
    void createZombies(int n, int maxSpeed);
    void drawMap(float inter, Object& cell_on, Object& cell_off, Object& enemy, Object& player);
    void update();
    
private:
    float randFloat(){
        return (float)(rand() % 1001) / 1000.0f;
    }
    void dead();
    void updateTerritory();
    void BFSFill(int i, int j, bool** bdChk);
    
};

#endif /* territory_hpp */
