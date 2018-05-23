#include "game.hpp"

Game::Game(int w, int h): WIDTH(w), HEIGHT(h){
    titleText = Object("models/title.obj");
    cell_on = Object("models/cell_on.obj");
    cell_off = Object("models/cell_off.obj");
    enemy = Object("models/enemy.obj");
    player = Object("models/player.obj");
}
Game::~Game(){
    
}

void Game::init(){
    setBgColor(1.0f, 1.0f, 1.0f);
}

void Game::renderScene(){
    glClearColor(bgColorR, bgColorG, bgColorB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(gameState == TITLE){
        // Lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        float light_ambient[] = {1, 1, 1, 1};
        float light_diffuse[] = {0.7, 0.7, 0.7, 1};
        float light_specular[] = {0.5, 0.5, 0.5, 1};
        float light_position[] = {1, 1, 1, 0};
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHT0);
        // Texture
        GLuint texID;
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, ((float)WIDTH)/(float)HEIGHT, 0.1f, 100.0f);
        // Reset transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 0.5f, 1.3f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);
        
        glPushMatrix();
        glTranslatef(0, 0.2, 0);
        glRotatef(20.0f * sin(1.0f * titleCubeAngle), 1, 0, 0);
        glRotatef(20.0f * sin(0.5f * titleCubeAngle), 0, 1, 0);
        titleText.draw();
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0, -0.5, -1);
        glRotatef(2.0f * titleCubeAngle, 0, 1, 0);
        glColor3f(0, 0, 0);
        glutSolidCube(0.5);
        glPopMatrix();
        
    }
    else if(gameState == PLAY_1P){
        /*
        // Lighting
        glDisable(GL_LIGHT0);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        // Texture
        glDisable(GL_TEXTURE_2D);
        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // Reset transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        */
        
        // Lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        float light_ambient[] = {1, 1, 1, 1};
        float light_diffuse[] = {0.7, 0.7, 0.7, 1};
        float light_specular[] = {0.5, 0.5, 0.5, 1};
        float light_position[] = {1, 1, 1, 0};
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHT0);
        // Texture
        GLuint texID;
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(80.0f, ((float)WIDTH)/(float)HEIGHT, 0.1f, 100.0f);
        // Reset transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float interAnimation = (float)idlePerTerritoryUpdateCount / idlePerTerritoryUpdate;
        gluLookAt(territory->getPlayerGLUX(interAnimation), 1.5f, territory->getPlayerGLUZ(interAnimation) + 0.5f,
                  territory->getPlayerGLUX(interAnimation), 0.0f, territory->getPlayerGLUZ(interAnimation),
                  0.0f, 1.0f, 0.0f);
        
        //territory->drawMap(-1, 1);
        territory->drawMap(interAnimation, cell_on, cell_off, enemy, player);
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
                    int terrW = WIDTH / 10, terrH = HEIGHT / 10;
                    territory = new Territory(terrW, terrH);
                    territory->setPlayerTerritory(terrW/2-5, terrH/2-5, terrW/2+5, terrH/2+5);
                    territory->setPlayerPosition(terrW/2, terrH/2);
                    territory->createZombies(10, 100);
                    setBgColor(1,1,1);
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
            
            break;
        case PLAY_1P:
            switch(key){
                case GLUT_KEY_UP:
                    tempPlayerDirection = UP;
                    break;
                case GLUT_KEY_DOWN:
                    tempPlayerDirection = DOWN;
                    break;
                case GLUT_KEY_LEFT:
                    tempPlayerDirection = LEFT;
                    break;
                case GLUT_KEY_RIGHT:
                    tempPlayerDirection = RIGHT;
                    break;
            }
            
            break;
    }
    
}

void Game::idleFunc(){
    // FPS control
    if(clock() - startTimeForFPS < 1000.0f / FPS) return;
    startTimeForFPS = clock();
    
    switch(gameState){
        case TITLE:
            titleCubeAngle += 0.1f;
            break;
        case PLAY_1P:
            idlePerTerritoryUpdateCount++;
            if(idlePerTerritoryUpdateCount == idlePerTerritoryUpdate){
                territory->update();
                territory->setPlayerDirection(tempPlayerDirection);
                idlePerTerritoryUpdateCount = 0;
            }
            break;
    }
    
    glutPostRedisplay();
    
}

void Game::reshapeFunc(int w, int h){
    switch(gameState){
        case TITLE:
            if(w > MIN_WIDTH) WIDTH = w;
            else WIDTH = MIN_WIDTH;
            if(h > MIN_HEIGHT) HEIGHT = h;
            else HEIGHT = MIN_HEIGHT;
            if(HEIGHT > WIDTH) WIDTH = HEIGHT;
            WIDTH /= 10; HEIGHT /= 10;
            WIDTH *= 10; HEIGHT *= 10;
            break;
        case PLAY_1P:
            break;
    }
    glutReshapeWindow(WIDTH, HEIGHT);
    
    glViewport(0, 0, WIDTH, HEIGHT);
    
    
    glutPostRedisplay();
}
