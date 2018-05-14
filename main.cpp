#include <iostream>
#include <GLUT/glut.h>

#include "game.hpp"


const int WIDTH = 600, HEIGHT = 600;
game mainGame(WIDTH, HEIGHT);

void init(){
    
}

void renderScene(){mainGame.renderScene();}
void normalKeys(unsigned char key, int x, int y){mainGame.normalKeys(key, x, y);}
void specialKeys(int key, int x, int y){mainGame.specialKeys(key, x, y);}
void idleFunc(){mainGame.idleFunc();}
void reshapeFunc(int w, int h){mainGame.reshapeFunc(w, h);}

int main(int argc, char** argv) {
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(mainGame.getWidth()/5, mainGame.getHeight()/5);
    glutInitWindowSize(mainGame.getWidth(), mainGame.getHeight());
    glutCreateWindow("Territory Expansion Game");
    init();
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idleFunc);
    glutReshapeFunc(reshapeFunc);
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 0;
}
