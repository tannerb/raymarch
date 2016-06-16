//
// Created by Tanner on 6/4/2016.
//

#ifndef RAYMARCHER_SHADER_H
#define RAYMARCHER_SHADER_H

#include <vector>

class program {
    unsigned int programStatus;
public:
    const unsigned int pid;
    program(const char* vs, const char* fs);
    ~program();
};


#endif //RAYMARCHER_SHADER_H
