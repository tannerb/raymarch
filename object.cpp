//
// Created by Tanner on 6/8/2016.
//

#include "object.h"

static auto nextId = 0UL;

object::object() : id(nextId++) {

}

