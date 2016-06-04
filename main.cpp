#include <iostream>

#include "gl_3_3.hpp"

using namespace std;

bool init();

int main() {
    cout << "Running init." << endl;
    if (!init()) {
        cout << "Init failed" << endl;
    }
    return 0;
}


bool init() {
    std::cout << "LoadFunc: " << gl::sys::LoadFunctions() << std::endl;
    return true;
}