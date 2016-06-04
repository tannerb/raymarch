#include <iostream>

#include "gl_3_3.hpp"
#include <GLFW/glfw3.h>

using namespace std;

bool init();
bool run();
bool terminate(const char* msg);

static GLFWwindow* window;

static int fbWidth;
static int fbHeight;

int main() {
    cout << "Running init." << endl;
    if (!init()) {
        cout << "Init failed" << endl;
        return 0;
    }

    if (!run()) {
        terminate("Program ran unsuccessfully");
    } else {
        terminate("Program exited normally");
    }

    return 0;
}


bool init() {
    auto res = gl::sys::LoadFunctions();
    std::cout << "Load OpenGL Functions: " << res.GetNumMissing() << std::endl;

    if (!glfwInit()) {
        return false;
    }

    glfwSetErrorCallback([] (int error, char const* desc) { std::cout << error << " " << desc << std::endl; });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(1280, 720, "Ray Marcher", nullptr, nullptr);

    if (!window) {
        terminate("Couldn't create window");
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, [] (GLFWwindow* win, int key, int code, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    glfwSetFramebufferSizeCallback(window, [&] (GLFWwindow* win, int w, int h) {
        fbWidth = w;
        fbHeight = h;

        gl::Viewport(0, 0, w, h);
    });


    return true;
}


bool run() {
    while (!glfwWindowShouldClose(window)) {

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
}


bool terminate(const char* msg = nullptr) {
    if (msg != nullptr) {
        std::cout << msg << std::endl;
    }
    glfwTerminate();
    return true;
}
