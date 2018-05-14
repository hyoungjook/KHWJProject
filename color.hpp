#ifndef color_hpp
#define color_hpp

class Color {
public:
    Color(): R(0), G(0), B(0) {};
    Color(float r, float g, float b): R(r), G(g), B(b) {}
    void setColor(float r, float g, float b){
        R = r; G = g; B = b;
    }
    float getR(){return R;}
    float getG(){return G;}
    float getB(){return B;}
private:
    float R, G, B;
};

#endif /* color_hpp */
