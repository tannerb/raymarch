#include <iostream>
#include <string>

#include "gl_core_3_3.h"


void APIENTRY DebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                        const GLchar *message, const GLvoid *userParam)
{
    std::string srcName;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API_ARB:
            srcName = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
            srcName = "Window System";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
            srcName = "Shader Compiler";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
            srcName = "Third Party";
            break;

        case GL_DEBUG_SOURCE_APPLICATION_ARB:
            srcName = "Application";
            break;

        case GL_DEBUG_SOURCE_OTHER_ARB:
            srcName = "Other";
            break;
    }

    std::string errorType;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR_ARB:
            errorType = "Error";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
            errorType = "Deprecated Functionality";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
            errorType = "Undefined Behavior";
            break;

        case GL_DEBUG_TYPE_PORTABILITY_ARB:
            errorType = "Portability";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE_ARB:
            errorType = "Performance";
            break;

        case GL_DEBUG_TYPE_OTHER_ARB:
            errorType = "Other";
            break;
    }

    std::string typeSeverity;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH_ARB:
            typeSeverity = "High";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM_ARB:
            typeSeverity = "Medium";
            break;

        case GL_DEBUG_SEVERITY_LOW_ARB:
            typeSeverity = "Low";
            break;
    }

    printf("%s from %s,\t%s priority\nMessage: %s\n",
           errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
}
