#include "game.hpp"

void game::renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch(gameState){
        case TITLE:
            
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
    glutSwapBuffers();
}

void game::normalKeys(unsigned char key, int x, int y){
    
    switch(gameState){
        case TITLE:
            
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}

void game::specialKeys(int key, int x, int y){
    
    switch(gameState){
        case TITLE:
            
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}

void game::idleFunc(){
    
    switch(gameState){
        case TITLE:
            
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}

void game::reshapeFunc(int w, int h){
    
    switch(gameState){
        case TITLE:
            
            
            break;
        case PLAY_1P:
            
            
            break;
    }
    
}
