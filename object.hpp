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

class face {
public:
    face() {}
    std::vector<vertex> vs;
    std::vector<normal> vns;
};

class Object {
public:
    Object(){}
    Object(std::string objFile);
    void draw();
    void setMaterial(float e0, float e1, float e2, float e3, float a0, float a1, float a2, float a3, float d0, float d1, float d2, float d3, float sp0, float sp1, float sp2, float sp3, float sh0);
    
private:
    std::vector<face> faces;
    float emission[4], ambient[4], diffuse[4], specular[4], shineness[1];
    
};

#endif /* object_hpp */
