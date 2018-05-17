#include "territory.hpp"

Territory::Territory(int w, int h): width(w), height(h) {
    map = new int*[width];
    for(int i=0; i<width; i++) {
        map[i] = new int[height];
        for(int j=0; j<height; j++) map[i][j] = 0;
    }
}
Territory::~Territory(){
    if(map != nullptr){
        for(int i=0; i<width; i++) delete[] map[i];
        delete[] map;
    }
}
Territory::Territory(const Territory& t){
    width = t.width; height = t.height;
    map = new int*[width];
    for(int i=0; i<width; i++){
        map[i] = new int[height];
        for(int j=0; j<height; j++) map[i][j] = t.map[i][j];
    }
}
Territory& Territory::operator=(const Territory& t){
    if(map != nullptr){
        for(int i=0; i<width; i++) delete[] map[i];
        delete[] map;
    }
    width = t.width; height = t.height;
    map = new int*[width];
    for(int i=0; i<width; i++){
        map[i] = new int[height];
        for(int j=0; j<height; j++) map[i][j] = t.map[i][j];
    }
    return *this;
    }

void Territory::setPlayerPosition(int x, int y){
    playerX = x;
    playerY = y;
    map[x][y] = CELL_PLAYER;
}

void Territory::setPlayerTerritory(int x1, int y1, int x2, int y2){
    for(int i=x1; i<=x2; i++){
        for(int j=y1; j<=y2; j++){
            map[i][j] = CELL_TERRITORY;
        }
    }
}

void Territory::createZombies(int n, int maxSpeed){
    if(!zombies.empty()) zombies.clear();
    
    for(int i=1; i<=n; i++){
        int x = rand() % width, y = rand() % height;
        while(map[x][y] != CELL_EMPTY){
            x = rand() % width;
            y = rand() % height;
        }
        zombies.push_back(Zombie(x, y, maxSpeed, Color(randFloat(), randFloat(), randFloat())));
        map[x][y] = -i; // - zombie number
    }
    
}

void Territory::drawMap(float pixelPerCell, float pixelX, float pixelY){
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            float x = pixelX + pixelPerCell * j;
            float y = pixelY - pixelPerCell * i;
            drawCell(map[i][j], pixelPerCell, x, y);
        }
    }
}

void Territory::drawCell(int state, float pixelPerCell, float pixelX, float pixelY){
    switch(state){
        case CELL_EMPTY:
            return;
        case CELL_PLAYER:
            glColor3f(1, 0, 0);
            glBegin(GL_QUADS);
            glVertex2f(pixelX, pixelY);
            glVertex2f(pixelX, pixelY - pixelPerCell);
            glVertex2f(pixelX + pixelPerCell, pixelY - pixelPerCell);
            glVertex2f(pixelX + pixelPerCell, pixelY);
            glEnd();
            return;
        case CELL_TERRITORY:
            glBegin(GL_QUADS);
            glColor3f(0.5, 0, 0.5);
            glVertex2f(pixelX, pixelY); // RECTANGLE
            glVertex2f(pixelX, pixelY - pixelPerCell);
            glVertex2f(pixelX + pixelPerCell, pixelY - pixelPerCell);
            glVertex2f(pixelX + pixelPerCell, pixelY);
            glEnd();
            return;
        case CELL_TRACE:
            glBegin(GL_QUADS);
            glColor3f(0.8, 0, 0);
            glVertex2f(pixelX + pixelPerCell/2, pixelY); // DIAMOND
            glVertex2f(pixelX, pixelY - pixelPerCell/2);
            glVertex2f(pixelX + pixelPerCell/2, pixelY - pixelPerCell);
            glVertex2f(pixelX + pixelPerCell, pixelY - pixelPerCell/2);
            glEnd();
            return;
        default:
            if(state < 0){ // zombies
                glBegin(GL_TRIANGLES);
                Color zomCol = zombies[-state-1].getColor();
                glColor3f(zomCol.getR(), zomCol.getG(), zomCol.getB());
                glVertex2f(pixelX + pixelPerCell/2, pixelY); // TRIANGLE
                glVertex2f(pixelX, pixelY - pixelPerCell);
                glVertex2f(pixelX + pixelPerCell, pixelY - pixelPerCell);
                glEnd();
                return;
            }
            
    }
}

void Territory::update(){
    
}






