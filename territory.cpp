#include "territory.hpp"

Territory::Territory(int w, int h): width(w), height(h) {
    map = new int*[width];
    for(int i=0; i<width; i++) map[i] = new int[height];
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
