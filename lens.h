//
// Created by Tanner on 6/15/2016.
//

#ifndef RAYMARCHER_CAMERA_VIEW_H
#define RAYMARCHER_CAMERA_VIEW_H


#include <glm/glm.hpp>

struct lens {
    double aspectRatio;
    double fieldOfView;
    double nearClipping;
    double farClipping;

    explicit lens(double aspectRatio = 1.77, double fov = 75.0, double nearClipping = 0.0, double farClipping = 1000.0) :
            aspectRatio(aspectRatio), fieldOfView(fov), nearClipping(nearClipping), farClipping(farClipping) {
    }

    const glm::mat4 view() const;
};


#endif //RAYMARCHER_CAMERA_VIEW_H
