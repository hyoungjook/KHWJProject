#ifndef game_hpp
#define game_hpp

#include <string>
#include <time.h>
#include <cmath>

#ifdef _WIN32
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

#include "color.hpp"
#include "territory.hpp"
#include "object.hpp"

#define BIG_FONT GLUT_BITMAP_TIMES_ROMAN_24
#define SMALL_FONT GLUT_BITMAP_TIMES_ROMAN_10
#define MIN_WIDTH 300
#define MIN_HEIGHT 300

enum GameState{
    TITLE, PLAY_1P
};

class Game {
public:
    Game(int w, int h);
    ~Game();
    void setSize(int w, int h) {WIDTH = w; HEIGHT = h;};
    int getWidth() const {return WIDTH;}
    int getHeight() const {return HEIGHT;}
    
    void init();
    
private:
    void drawString(std::string str, float x, float y, float size, Color c){
        // (x,y): center position, size: size of each letter
        glColor3f(c.getR(), c.getG(), c.getB());
        glPushMatrix();
        glTranslatef(x-size*str.size()/2.0f, y-size/2.0f, 0.0f);
        float ratio = size / 100.0f;
        glScalef(ratio, ratio, ratio);
        glRasterPos2f(0, 0);
        for(int i=0; i<str.size(); i++)
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[i]);
        glPopMatrix();
    }
    void setBgColor(float r, float g, float b){
        bgColorR = r; bgColorG = g; bgColorB = b;
    }
    
private:
    int WIDTH, HEIGHT;
    GameState gameState;
    float bgColorR, bgColorG, bgColorB;
    Territory* territory;
    float FPS = 60.0f;
    clock_t startTimeForFPS = clock();
    int idlePerTerritoryUpdateCount = 0;
    const int idlePerTerritoryUpdate = 3;
    float titleCubeAngle = 0.0f;
    Object titleText;
    
    
public:
    void renderScene();
    void normalKeys(unsigned char key, int x, int y);
    void specialKeys(int key, int x, int y);
    void idleFunc();
    void reshapeFunc(int w, int h);
    
};

#endif
