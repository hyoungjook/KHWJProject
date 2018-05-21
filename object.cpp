#include "object.hpp"

Object::Object(std::string objFile){
    std::ifstream obj(objFile);
    
    std::vector<vertex> v;
    std::vector<normal> n;
    std::vector<std::tuple<std::string, material> > m;
    std::string line;
    bool matChanged = false;
    material changedMat;
    while(!obj.eof()){
        getline(obj, line);
        if(line.size() > 6 && line.substr(0, 6).compare("mtllib") == 0){
            std::string mtlFile = "models/" + line.substr(7, line.size());
            std::ifstream mtl(mtlFile);
            
            std::string matName = "";
            float kE[3], kA[3], kD[3], kS[3], nS = 0.0f;
            
            std::string matLine;
            while(!mtl.eof()){
                getline(mtl, matLine);
                if(matLine.size() > 6 && matLine.substr(0, 6).compare("newmtl") == 0){
                    if(matName.size() > 0){
                        m.push_back(std::tuple<std::string, material>(
                            matName,
                            material(
                                kE[0], kE[1], kE[2], 1,
                                kA[0], kA[1], kA[2], 1,
                                kD[0], kD[1], kD[2], 1,
                                kS[0], kS[1], kS[2], 1,
                                nS
                            )));
                    }
                    matName = matLine.substr(7, matLine.size());
                }
                else if(matLine.size() > 2 && matLine.substr(0, 2).compare("Ns") == 0){
                    nS = atof(matLine.substr(3, matLine.size()).c_str());
                }
                else if(matLine.size() > 2 && matLine.substr(0, 2).compare("Ka") == 0){
                    std::stringstream info(matLine.substr(3, matLine.size()));
                    info >> kA[0] >> kA[1] >> kA[2];
                }
                else if(matLine.size() > 2 && matLine.substr(0, 2).compare("Kd") == 0){
                    std::stringstream info(matLine.substr(3, matLine.size()));
                    info >> kD[0] >> kD[1] >> kD[2];
                }
                else if(matLine.size() > 2 && matLine.substr(0, 2).compare("Ks") == 0){
                    std::stringstream info(matLine.substr(3, matLine.size()));
                    info >> kS[0] >> kS[1] >> kS[2];
                }
                else if(matLine.size() > 2 && matLine.substr(0, 2).compare("Ke") == 0){
                    std::stringstream info(matLine.substr(3, matLine.size()));
                    info >> kE[0] >> kE[1] >> kE[2];
                }
                
            }
            if(matName.size() > 0){
                m.push_back(std::tuple<std::string, material>(
                    matName,
                    material(
                        kE[0], kE[1], kE[2], 1,
                        kA[0], kA[1], kA[2], 1,
                        kD[0], kD[1], kD[2], 1,
                        kS[0], kS[1], kS[2], 1,
                        nS
                    )));
            }
        }
        else if(line.size() > 2 && line.substr(0,2).compare("v ") == 0){
            std::stringstream info(line.substr(2, line.size()));
            float x, y, z;
            info >> x >> y >> z;
            v.push_back(vertex(x, y, z));
        }
        else if(line.size() > 3 && line.substr(0,3).compare("vn ") == 0){
            std::stringstream info(line.substr(3, line.size()));
            float x, y, z;
            info >> x >> y >> z;
            n.push_back(normal(x, y, z));
        }
        else if(line.size() > 2 && line.substr(0,2).compare("f ") == 0){
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
            if(matChanged){
                f.mat = changedMat;
                f.matChanged = true;
                matChanged = false;
            }
            faces.push_back(f);
        }
        else if(line.size() > 6 && line.substr(0,6).compare("usemtl") == 0){
            std::string matName = line.substr(7, line.size());
            matChanged = true;
            for(int i=0; i<m.size(); i++){
                if(std::get<0>(m[i]).compare(matName) == 0){
                    changedMat = std::get<1>(m[i]);
                }
            }
        }
    }
    
    obj.close();
}


void Object::draw() {
    for(int i=0; i<faces.size(); i++) {
        if(faces[i].matChanged){
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, faces[i].mat.emission);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, faces[i].mat.diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, faces[i].mat.specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, faces[i].mat.ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, faces[i].mat.shininess);
            /*
            float mE[4] = {0, 0, 0, 1};
            float mA[4] = {0, 0, 1};
            float mD[4] = {0, 0, 0, 1};
            float mS[4] = {0, 0, 0, 1};
            float mSh[1] = {50};*/
        }
        glBegin(GL_POLYGON);
        for (int j = 0; j < faces[i].vs.size(); j++) {
            glNormal3f(faces[i].vns[j].vec[0], faces[i].vns[j].vec[1], faces[i].vns[j].vec[2]);
            glVertex3f(faces[i].vs[j].pos[0], faces[i].vs[j].pos[1], faces[i].vs[j].pos[2]);
        }
        
        glEnd();
    }
}
