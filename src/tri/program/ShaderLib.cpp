#include "ShaderLib.h"

#include <fmt/format.h>

#include <shader_path.h>
#include <util/files.h>

#include <tri/program/shaderError.h>
#include <iostream>


ShaderLib::ShaderLib(){
    declarations = readShader(fmt::format("{}/{}", SHADER_PATH, LIB_PATH_DECLARATIONS));

    for(auto filename : FILES_VS){
        auto path = fmt::format("{}/{}/{}", SHADER_PATH, LIB_PATH_VS, filename);
        auto source = include_(readShader(path));
        auto sourceCStr = source.c_str();
        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &sourceCStr, NULL);
        glCompileShader(vertexShader);
        getShaderError(path, vertexShader);
        vertexShaders.push_back(vertexShader);
    }

    for(auto filename : FILES_FS){
        auto path = fmt::format("{}/{}/{}", SHADER_PATH, LIB_PATH_FS, filename);
        auto source = include_(readShader(path));
        auto sourceCStr = source.c_str();
        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &sourceCStr, NULL);
        glCompileShader(fragmentShader);
        getShaderError(path, fragmentShader);
        fragmentShaders.push_back(fragmentShader);
    }
}

ShaderLib::~ShaderLib(){

    // segmentation fault for some reason
//     for(auto shader : vertexShaders){
//         glDeleteShader(shader);
//     }

//    for(auto shader : fragmentShaders){
//         glDeleteShader(shader);
//     }   
}


ShaderLib& ShaderLib::instance(){
    static ShaderLib instance;
    return instance;
}

void ShaderLib::attach(GLint program){
    for(auto shader : instance().vertexShaders){
        glAttachShader(program, shader);
    }

    for(auto shader : instance().fragmentShaders){
        glAttachShader(program, shader);
    }   
}

std::string ShaderLib::include_(const std::string& source){
    return fmt::format("{}\n{}", declarations, source);
}


std::string ShaderLib::include(const std::string& source){
    return instance().include_(source);
}
