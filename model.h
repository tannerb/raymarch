//
// Created by Tanner on 6/5/2016.
//

#ifndef RAYMARCHER_MODEL_H
#define RAYMARCHER_MODEL_H

#include <vector>


#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include "gl_core_3_3.h"

using namespace std;
using namespace glm;

class model {
public:
    vector<float> vertices;
    vector<float> normals;
    vector<unsigned> indices;

    unsigned vao, vbo, ibo;

    model() {
        cout << "Creating model" << endl;
    }

    model(const model& other) {
        std::copy(other.vertices.begin(), other.vertices.end(), std::back_inserter(vertices));
        std::copy(other.normals.begin(), other.normals.end(), std::back_inserter(normals));
        std::copy(other.indices.begin(), other.indices.end(), std::back_inserter(indices));

        init();
    }

    model(const char* path) {
        loadObjFile(path);
    }

    model(vector<float> vertices, vector<float> normals, vector<unsigned> indices) :
            vertices(vertices), normals(normals), indices(indices) {
        cout << "Creating model" << endl;

        init();
    }

    void init() {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), getVertexPtr(), GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), getIndicePtr(), GL_STATIC_DRAW);
    }

    ~model() {
        cout << "Deleting model" << endl;
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
        glDeleteVertexArrays(1, &vao);
    }

    int render() const {
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//        glCullFace(GL_BACK);
//        glFrontFace(GL_CW);
        glDrawElements(GL_TRIANGLES,
                       (GLsizei)indices.size(),
                       GL_UNSIGNED_INT,
                       (void*)0);

        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

private:

    const float* getVertexPtr() const {
        return &(vertices[0]);
    }
    const float* getNormalsPtr() const {
        return &(normals[0]);
    }
    const unsigned* getIndicePtr() const {
        return &(indices[0]);
    }


    template <typename T, class S>
    static void extract(int num, S& s, vector<T>& vec)
    {
        T x, y, z;
        s >> x >> y >> z;
        vec.insert(vec.end(), {x, y, z});
    }
    void loadObjFile(const char* file_path) {
        //TODO:
        //  -Support more formats of faces
        //  -Parse texture vertices
        //  -Read mtl files

        auto done = false;


        ifstream file_stream {file_path};

        if (!file_stream.is_open()) {
            cout << "Could not load model: " << file_path << endl;
            throw std::exception();
        }

        string line;
        char prefix[10] = { '\0' };

        while (getline(file_stream, line) && !done)
        {
            istringstream in_stream { line };
            in_stream >> prefix;

            switch (prefix[0])
            {
                case 'v':
                    switch (prefix[1])
                    {
                        case 't':
                            break;
                        case 'n':
                            extract(3, in_stream, normals);
                            break;
                        default:
                            extract(3, in_stream, vertices);
                    }
                    break;

                case 'f':
                {
                    unsigned int av, bv, cv;
                    unsigned int an, bn, cn;
                    unsigned int at, bt, ct;

                    sscanf(line.c_str(),
                           "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &av, &at, &an,
                           &bv, &bt, &bn,
                           &cv, &ct, &cn);

                    indices.push_back(av - 1);
                    indices.push_back(bv - 1);
                    indices.push_back(cv - 1);
                }
                    break;

                default:
                    if (!indices.empty())
                        done = true;
            }
        }
        init();
    }
};


#endif //RAYMARCHER_MODEL_H
