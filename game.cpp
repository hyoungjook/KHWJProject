#include "game.hpp"

Game::Game(int w, int h): WIDTH(w), HEIGHT(h){
    
}
Game::~Game(){
    
}

void Game::init(){
    setBgColor(1.0f, 1.0f, 1.0f);
}

void Game::renderScene(){
    glClearColor(bgColorR, bgColorG, bgColorB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch(gameState){
        case TITLE:
            drawString("TERRITORY", 0.0f, 0.3f, 0.1f, Color(0.0f, 1.0f, 0.0f));
            drawString("EXPANSION", 0.0f, 0.15f, 0.1f, Color(0.0f, 1.0f, 0.0f));
            drawString("GAME", 0.0f, 0.0f, 0.15f, Color(0.0f, 1.0f, 0.0f));
            drawString("Press Enter to Start", 0.0f, -0.4f, 0.05f, Color(0.0f, 1.0f, 0.0f));
            break;
        case PLAY_1P:
            territory->drawMap(0.03333333f, -1, 1);
            
            break;
    }
    
    glutSwapBuffers();
}

void Game::normalKeys(unsigned char key, int x, int y){
    
    
    
    switch(key){
        case '\e': // ESC
            exit(0);
            break;
    }
    
    switch(gameState){
        case TITLE:
            switch(key){
                case '\r': // ENTER
                    // PLAY_1P로 전환
                    gameState = PLAY_1P;
                    territory = new Territory(WIDTH/10, HEIGHT/10);
                    territory->setPlayerTerritory(WIDTH/20-5, HEIGHT/20-5, WIDTH/20+5, HEIGHT/20+5);
                    territory->setPlayerPosition(WIDTH/20, HEIGHT/20);
                    territory->createZombies(10, 100);
                    setBgColor(0, 0, 0);
                    glutPostRedisplay();
                    break;
                    
            }
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}

void Game::specialKeys(int key, int x, int y){
    
    switch(gameState){
        case TITLE:
            switch(key){
                case GLUT_KEY_UP:
                    break;
                case GLUT_KEY_DOWN:
                    break;
            }
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}

void Game::idleFunc(){
    
    switch(gameState){
        case TITLE:
            
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}

void Game::reshapeFunc(int w, int h){
    switch(gameState){
        case TITLE:
            if(w > MIN_WIDTH) WIDTH = w;
            else WIDTH = MIN_WIDTH;
            if(h > MIN_HEIGHT) HEIGHT = h;
            else HEIGHT = MIN_HEIGHT;
            break;
    }
    glutReshapeWindow(WIDTH, HEIGHT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    
    
    glutPostRedisplay();
}
