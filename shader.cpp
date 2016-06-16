//
// Created by Tanner on 6/4/2016.
//

#include <fstream>
#include <iostream>
#include <vector>

#include "shader.h"


#include "gl_core_3_3.h"

namespace {
    std::string getFileContents(const char *path) {
        std::string code;
        std::ifstream vsf(path, std::ios::in);
        if (vsf.is_open()) {
            std::string line = "";

            while (getline(vsf, line)) {
                code += "\n" + line;
            }
            vsf.close();
        } else {
            std::cout << "Could not open " << path << std::endl;
            return std::string("");
        }

        return code;
    }


    bool compileShader(GLuint shader_id, const char* name, std::string code) {
        GLint res = GL_FALSE;

        std::cout << "Compiling shader: " << name << std::endl;

        char const* vsp = code.c_str();
        glShaderSource(shader_id, 1, &vsp, nullptr);
        glCompileShader(shader_id);

        int log_length;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);

        if (res == 0) {
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
            if (log_length > 0) {
                std::vector<char> shader_error_msg((unsigned) log_length + 1);
                glGetShaderInfoLog(shader_id, log_length, nullptr, &shader_error_msg[0]);
                std::cout << "Info Log for " << name << std::endl << &shader_error_msg[0];
            }

            return false;
        }

        return true;
    }

    bool linkProgram(GLuint pid, GLuint vsid, GLuint fsid) {
        glAttachShader(pid, vsid);
        glAttachShader(pid, fsid);

        glBindAttribLocation(pid, 0, "in_Position");

        glLinkProgram(pid);

        GLint result;
        GLsizei log_length;
        glGetProgramiv(pid, GL_LINK_STATUS, &result);

        glValidateProgram(pid);
        if (!result) {
            glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &log_length);
            std::vector<char> link_error_msg((unsigned) log_length + 1);
            glGetProgramInfoLog(pid, log_length, nullptr, &link_error_msg[0]);
            std::cout << "Info Log for program link: " << &link_error_msg[0] << std::endl;
            std::cout << result << "End info log" << std::endl;
        }

        glDetachShader(pid, vsid);
        glDetachShader(pid, fsid);

        glDeleteShader(vsid);
        glDeleteShader(fsid);

        return true;
    }


    bool createShader(GLuint &id, GLenum type, const char* path) {
        id = glCreateShader(type);

        auto shader_code = getFileContents(path);
        if (shader_code.empty()) {
            std::cout << "Shader empty" << std::endl;
            return false;
        }
        if (!compileShader(id, path, shader_code)) {
            std::cout << "Could not compile shader" << path << std::endl;
            return false;
        }

        return true;
    }
}

program::program(const char* vs_path, const char* fs_path) : pid(glCreateProgram()) {
    GLuint vs, fs;
    if (!createShader(vs, GL_VERTEX_SHADER, vs_path)) {
        std::cout << "Could not create VS: " << vs_path << std::endl;
    }
    if (!createShader(fs, GL_FRAGMENT_SHADER, fs_path)) {
        std::cout << "Could not create VS: " << vs_path << std::endl;
    }

    linkProgram(pid, vs, fs);
}


program::~program() {
    std::cout << "Deleting program " << pid << std::endl;
    glDeleteProgram(pid);
}