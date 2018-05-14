#ifndef game_hpp
#define game_hpp

#include <GLUT/glut.h>

enum GameState{
    TITLE, PLAY_1P
};

class game {
public:
    game(int w, int h): WIDTH(w), HEIGHT(h) {};
    void setSize(int w, int h) {WIDTH = w; HEIGHT = h;};
    int getWidth() const {return WIDTH;}
    int getHeight() const {return HEIGHT;}
    
private:
    int WIDTH, HEIGHT;
    GameState gameState;
    
public:
    void renderScene();
    void normalKeys(unsigned char key, int x, int y);
    void specialKeys(int key, int x, int y);
    void idleFunc();
    void reshapeFunc(int w, int h);
    
};

#endif
