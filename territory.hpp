#ifndef territory_hpp
#define territory_hpp

#include <stdio.h>

class Territory {
public:
    Territory(int w, int h);
    ~Territory();
    Territory(const Territory& t);
    Territory& operator=(const Territory& t);
    
    int operator()(unsigned int i, unsigned int j){return map[i][j];}
    
    
private:
    int width, height;
    int** map;
    
};

#endif /* territory_hpp */
