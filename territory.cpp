#include "territory.hpp"

Territory::Territory(int w, int h): width(w), height(h) {
    map = new bool*[width];
    for(int i=0; i<width; i++) {
        map[i] = new bool[height];
        for(int j=0; j<height; j++) map[i][j] = false;
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
    map = new bool*[width];
    for(int i=0; i<width; i++){
        map[i] = new bool[height];
        for(int j=0; j<height; j++) map[i][j] = t.map[i][j];
    }
}
Territory& Territory::operator=(const Territory& t){
    if(map != nullptr){
        for(int i=0; i<width; i++) delete[] map[i];
        delete[] map;
    }
    width = t.width; height = t.height;
    map = new bool*[width];
    for(int i=0; i<width; i++){
        map[i] = new bool[height];
        for(int j=0; j<height; j++) map[i][j] = t.map[i][j];
    }
    return *this;
    }

void Territory::setPlayerPosition(int x, int y){
    playerInitialX = x;
    playerInitialY = y;
    playerX = x;
    playerY = y;
}

void Territory::setPlayerTerritory(int x1, int y1, int x2, int y2){
    for(int i=x1; i<=x2; i++){
        for(int j=y1; j<=y2; j++){
            map[i][j] = true;
        }
    }
}

void Territory::createZombies(int n, int maxSpeed){
    if(!zombies.empty()) zombies.clear();
    
    for(int i=1; i<=n; i++){
        int x = rand() % width, y = rand() % height;
        while(map[x][y] != false){
            x = rand() % width;
            y = rand() % height;
        }
        zombies.push_back(Zombie(x, y, Color(randFloat(), randFloat(), randFloat())));
    }
    
}

void Territory::drawMap(float gluX, float gluY){
    float gluPerCellX = 2.0f / width, gluPerCellY = 2.0f / height;
    
    // 플레이어 영토
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            float x = gluX + gluPerCellX * i;
            float y = gluY - gluPerCellY * j;
            if(map[i][j] == true){
                glColor3f(1, 0, 0);
                glBegin(GL_QUADS);
                glColor3f(0.5, 0, 0.5);
                glVertex2f(x, y); // RECTANGLE
                glVertex2f(x, y - gluPerCellY);
                glVertex2f(x + gluPerCellX, y - gluPerCellY);
                glVertex2f(x + gluPerCellX, y);
                glEnd();
            }
        }
    }
    
    // 좀비
    for(int i=0; i<zombies.size(); i++){
        float x = gluX + gluPerCellX * zombies[i].getX();
        float y = gluY - gluPerCellY * zombies[i].getY();
        glBegin(GL_TRIANGLES);
        Color zomCol = zombies[i].getColor();
        glColor3f(zomCol.getR(), zomCol.getG(), zomCol.getB());
        glVertex2f(x + gluPerCellX/2, y); // TRIANGLE
        glVertex2f(x, y - gluPerCellY);
        glVertex2f(x + gluPerCellX, y - gluPerCellY);
        glEnd();
    }
    
    // 플레이어 흔적
    for(int i=0; i<trace.size(); i++){
        float x = gluX + gluPerCellX * std::get<0>(trace[i]);
        float y = gluY - gluPerCellY * std::get<1>(trace[i]);
        glBegin(GL_QUADS);
        glColor3f(0.8, 0, 0);
        glVertex2f(x + gluPerCellX/2, y); // DIAMOND
        glVertex2f(x, y - gluPerCellY/2);
        glVertex2f(x + gluPerCellX/2, y - gluPerCellY);
        glVertex2f(x + gluPerCellX, y - gluPerCellY/2);
        glEnd();
    }
    
    // 플레이어
    {
        float x = gluX + gluPerCellX * playerX;
        float y = gluY - gluPerCellY * playerY;
        glColor3f(1, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y - gluPerCellY);
        glVertex2f(x + gluPerCellX, y - gluPerCellY);
        glVertex2f(x + gluPerCellX, y);
        glEnd();
    }
    
    
}

void Territory::update(){
    // 좀비 무브
    for(int i=0; i<zombies.size(); i++){
        int direction = rand() % 4;
        switch(direction){
            case 0: // UP
                if(zombies[i].getY() > 0) zombies[i].moveUP();
                if(map[zombies[i].getX()][zombies[i].getY()] == true){
                    zombies[i].moveDOWN();
                }
                break;
            case 1: // DOWN
                if(zombies[i].getY() < height - 1) zombies[i].moveDOWN();
                if(map[zombies[i].getX()][zombies[i].getY()] == true){
                    zombies[i].moveUP();
                }
                break;
            case 2: // LEFT
                if(zombies[i].getX() > 0) zombies[i].moveLEFT();
                if(map[zombies[i].getX()][zombies[i].getY()] == true){
                    zombies[i].moveRIGHT();
                }
                break;
            case 3: // RIGHT
                if(zombies[i].getX() < width - 1) zombies[i].moveRIGHT();
                if(map[zombies[i].getX()][zombies[i].getY()] == true){
                    zombies[i].moveLEFT();
                }
                break;
        }
        for(int j=0; j<trace.size(); j++){
            if(zombies[i].getX() == std::get<0>(trace[j]) && zombies[i].getY() == std::get<1>(trace[j])){
                dead();
                return;
            }
        }
    }
    
    
    // 플레이어 무브
    bool isPlayerMoved = false;
    switch(playerDirection){
        case UP:
            if(playerY > 0){
                playerY -= 1;
                isPlayerMoved = true;
            }
            break;
        case DOWN:
            if(playerY < height - 1){
                playerY += 1;
                isPlayerMoved = true;
            }
            break;
        case LEFT:
            if(playerX > 0){
                playerX -= 1;
                isPlayerMoved = true;
            }
            break;
        case RIGHT:
            if(playerX < width - 1){
                playerX += 1;
                isPlayerMoved = true;
            }
            break;
        case STOP:
            break;
    }
    
    if(isPlayerMoved){
        // 자기 trace에 닿았는지 체크
        for(int i=0; i<trace.size(); i++){
            if(playerX == std::get<0>(trace[i]) && playerY == std::get<1>(trace[i])){
                // 라이프 잃는다
                dead();
                return;
            }
        }
        
        // 자기 영토에 닿았는지 체크
        if(map[playerX][playerY] == true){
            if(!trace.empty()){
                // update territory
                updateTerritory();
                trace.clear();
                
                // 좀비 제거
                for(int i=0; i<zombies.size(); i++){
                    if(map[zombies[i].getX()][zombies[i].getY()] == true){
                        zombies.erase(zombies.begin() + i);
                    }
                }
                
                return;
            }
        }
        else {
            // 안닿았다면
            trace.push_back(std::tuple<int, int>(playerX, playerY));
        }
        
    }
    
    
}

void Territory::dead(){
    if(lives == 0){
        // GAME OVER
        exit(0);
    }
    else {
        lives--;
        playerX = playerInitialX;
        playerY = playerInitialY;
        playerDirection = STOP;
        trace.clear();
    }
}

void Territory::updateTerritory(){
    for(int i=0; i<trace.size(); i++){
        map[std::get<0>(trace[i])][std::get<1>(trace[i])] = true;
    }
    
    bool** bdChk = new bool*[width];
    for(int i=0; i<width; i++){
        bdChk[i] = new bool[height];
        for(int j=0; j<height; j++){
            if(map[i][j] == true) bdChk[i][j] = true;
        }
    }
    
    for(int i=0; i<width; i++){
        BFSFill(i, 0, bdChk);
        BFSFill(i, height-1, bdChk);
    }
    for(int j=0; j<height; j++){
        BFSFill(0, j, bdChk);
        BFSFill(width-1, j, bdChk);
    }
    
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            if(bdChk[i][j] == false) map[i][j] = true;
        }
    }
    
    for(int i=0; i<width; i++){
        delete[] bdChk[i];
    }
    delete[] bdChk;
    
}

void Territory::BFSFill(int i, int j, bool **bdChk){
    if(bdChk[i][j] == true) return;
    
    bdChk[i][j] = true;
    
    std::queue<std::tuple<int, int> > bfsQ;
    bfsQ.push(std::tuple<int, int>(i, j));
    
    while(!bfsQ.empty()){
        int tx, ty;
        std::tie(tx, ty) = bfsQ.front();
        bfsQ.pop();
        
        if(ty > 0 && bdChk[tx][ty-1] == false) {
            bfsQ.push(std::tuple<int, int>(tx, ty-1));
            bdChk[tx][ty-1] = true;
        }
        if(ty < height - 1 && bdChk[tx][ty+1] == false) {
            bfsQ.push(std::tuple<int, int>(tx, ty+1));
            bdChk[tx][ty+1] = true;
        }
        if(tx > 0 && bdChk[tx-1][ty] == false) {
            bfsQ.push(std::tuple<int, int>(tx-1, ty));
            bdChk[tx-1][ty] = true;
        }
        if(tx < width - 1 && bdChk[tx+1][ty] == false) {
            bfsQ.push(std::tuple<int, int>(tx+1, ty));
            bdChk[tx+1][ty] = true;
        }
        
    }
    
    
}

