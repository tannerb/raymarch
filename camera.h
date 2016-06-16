//
// Created by Tanner on 6/8/2016.
//

#ifndef RAYMARCHER_CAMERA_H
#define RAYMARCHER_CAMERA_H

#include "lens.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct camera {
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 direction;

    lens lens_;

    inline
    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + normalize(direction), up);
    }
};

#endif //RAYMARCHER_CAMERA_H
