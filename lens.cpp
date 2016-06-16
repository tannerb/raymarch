//
// Created by Tanner on 6/15/2016.
//

#include "lens.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <c++/4.8.3/algorithm>

const glm::mat4 lens::view() const {
    return glm::perspective(this->fieldOfView, this->aspectRatio, this->nearClipping, this->farClipping);
}