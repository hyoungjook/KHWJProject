#include <iostream>
#include <GLUT/glut.h>

#define WIDTH 600
#define HEIGHT 600

void init(){
    
}

void renderScene(){
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw Game
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(650, 300);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Territory Expansion Game");
    init();
    
    // register callbacks
    glutDisplayFunc(renderScene);
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 0;
}
