#include "object.hpp"

Object::Object(std::string objFile){
    std::ifstream obj(objFile);
    
    std::vector<vertex> v;
    std::vector<normal> n;
    std::string line;
    while(!obj.eof()){
        getline(obj, line);
        if(line[0] == 'v' && line[1] == ' '){
            std::stringstream info(line.substr(2, line.size()));
            float x, y, z;
            info >> x >> y >> z;
            v.push_back(vertex(x, y, z));
        }
        else if(line[0] == 'v' && line[1] == 'n'){
            std::stringstream info(line.substr(3, line.size()));
            float x, y, z;
            info >> x >> y >> z;
            n.push_back(normal(x, y, z));
        }
        else if(line[0] == 'f'){
            std::stringstream info(line.substr(2, line.size()));
            face f;
            while(!info.eof()){
                std::string data;
                info >> data;
                unsigned long index_firstSlash = data.find('/');
                int v_index = atoi(data.substr(0, index_firstSlash).c_str()) - 1;
                unsigned long index_secondSlash = data.find('/', index_firstSlash + 1);
                int n_index = atoi(data.substr(index_secondSlash+1, data.size()).c_str()) - 1;
                f.vs.push_back(v[v_index]);
                f.vns.push_back(n[n_index]);
            }
            faces.push_back(f);
        }
    }
    
    obj.close();
}

void Object::setMaterial(float e0, float e1, float e2, float e3, float a0, float a1, float a2, float a3, float d0, float d1, float d2, float d3, float sp0, float sp1, float sp2, float sp3, float sh0){
    emission[0] = e0; emission[1] = e1; emission[2] = e2; emission[3] = e3;
    ambient[0] = a0; ambient[1] = a1; ambient[2] = a2; ambient[3] = a3;
    diffuse[0] = d0; diffuse[1] = d1; diffuse[2] = d2; diffuse[3] = d3;
    specular[0] = sp0; specular[1] = sp1; specular[2] = sp2; specular[3] = sp3;
    shineness[0] = sh0;
}

void Object::draw() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shineness);
    for(int i=0; i<faces.size(); i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < faces[i].vs.size(); j++) {
            glNormal3f(faces[i].vns[j].vec[0], faces[i].vns[j].vec[1], faces[i].vns[j].vec[2]);
            glVertex3f(faces[i].vs[j].pos[0], faces[i].vs[j].pos[1], faces[i].vs[j].pos[2]);
        }
        
        glEnd();
    }
}
