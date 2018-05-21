#ifndef object_hpp
#define object_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#ifdef _WIN32
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif
#include "color.hpp"

class vertex{
public:
    vertex(){}
    vertex(float x, float y, float z){pos[0] = x; pos[1] = y; pos[2] = z;}
    float pos[3];
};

class normal{
public:
    normal(){}
    normal(float x, float y, float z){vec[0] = x; vec[1] = y; vec[2] = z;}
    float vec[3];
};

class material {
public:
    material(){}
    material(float e0, float e1, float e2, float e3, float a0, float a1, float a2, float a3, float d0, float d1, float d2, float d3, float sp0, float sp1, float sp2, float sp3, float sh0) {
        emission[0] = e0; emission[1] = e1; emission[2] = e2; emission[3] = e3;
        ambient[0] = a0; ambient[1] = a1; ambient[2] = a2; ambient[3] = a3;
        diffuse[0] = d0; diffuse[1] = d1; diffuse[2] = d2; diffuse[3] = d3;
        specular[0] = sp0; specular[1] = sp1; specular[2] = sp2; specular[3] = sp3;
        shininess[0] = sh0;
    }
    float emission[4], ambient[4], diffuse[4], specular[4], shininess[1];
};

class face {
public:
    face() {}
    std::vector<vertex> vs;
    std::vector<normal> vns;
    bool matChanged = false;
    material mat;
};

class Object {
public:
    Object(){}
    Object(std::string objFile);
    void draw();
    
private:
    std::vector<face> faces;
    
};

#endif /* object_hpp */
