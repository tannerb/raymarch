#include <iostream>
#include <vector>
#include <chrono>

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DebugFunc.h"
#include "shader.h"
#include "model.h"
#include "camera.h"

using namespace std;
using namespace glm;

bool init();
bool run();
bool terminate(const char* msg);

static GLFWwindow* window;

static auto fbWidth = 1920;
static auto fbHeight = 1080;

static camera cam = {
        { 0.0f, -3.0f, 0.0f }, // position
        { 0.0f, 1.0f, 0.0f },  // up
        { 0.5f, 0.5f, 0.0f },
        lens {}}; // direction


int main() {
    auto& c = cam;
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


void cam_func(int key, int code, int action, int mods) {
    switch (key) {
        case GLFW_KEY_W:
            cam.position += cam.direction;
            break;
        case GLFW_KEY_A:
            cam.position += cross(cam.up, cam.direction);
            break;
        case GLFW_KEY_S:
            cam.position -= cam.direction;
            break;
        case GLFW_KEY_D:
            cam.position -= cross(cam.up, cam.direction);
            break;
        default:
            break;
    }
}

bool init() {
    if (!glfwInit()) {
        cout << "Failed to initialize glfw" << endl;
        return false;
    }

    glfwSetErrorCallback([] (int error, char const* desc) {
        cout << error << " " << desc << endl;
    });

//    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

    window = glfwCreateWindow(fbWidth, fbHeight, "Ray Marcher", nullptr, nullptr);

    if (!window) {
        terminate("Couldn't create window");
    }

    glfwMakeContextCurrent(window);

    auto res = ogl_LoadFunctions();
    cout << "Load OpenGL Functions: " << ogl_LoadStatus() << endl;
    cout << "Initialized OpenGL v" << ogl_GetMajorVersion() << "." << ogl_GetMinorVersion() << endl;

    glDebugMessageCallbackARB(&DebugFunc, nullptr);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CW);

    glViewport(0, 0, fbWidth, fbHeight);
    cout << "Setting callbacks" << endl;
    glfwSetFramebufferSizeCallback(window, [&] (GLFWwindow* win, int w, int h) {
        fbWidth = w;
        fbHeight = h;
    });

    glfwSetKeyCallback(window, [&] (GLFWwindow* win, int key, int code, int action, int mods) {
        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_W:
                case GLFW_KEY_A:
                case GLFW_KEY_S:
                case GLFW_KEY_D:
                    cam_func(key, code, action, mods);
                    break;
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                default:
                    break;
            }
        }
    });

    cout << "Done Setting callbacks" << endl;
    return true;
}


bool run() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto p = program {"resources/glsl/vert.vert", "resources/glsl/frag.frag"};

    auto plane = model { { 0.75f, 0.75f, 0.0f, 1.0f,
                           0.75f, -0.75f, 0.0f, 1.0f,
                           -0.75f, -0.75f, 0.0f, 1.0f },
                         { },
                         { 0, 1, 2 } };

    mat4 modelMatrix;

    cout << "Loading test obj" << endl;
    model cube("resources/models/cubeT.obj");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glUseProgram(p.pid);
        GLint mvpUniformLoc = glGetUniformLocation(p.pid, "MVP");
        glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, value_ptr(modelMatrix));

//        cube.render();

        plane.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
}


bool terminate(const char* msg = nullptr) {
    if (msg != nullptr) {
        cout << msg << endl;
    }
    glfwTerminate();
    return true;
}
