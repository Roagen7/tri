#pragma once
#include <tricore/program/Program.h>


namespace {
    static constexpr auto POSTPROCESS = "postprocess";
    static constexpr auto IDENTITY = "identity";
}

namespace tri::core::postprocess {
    
    class BasePostprocess : public Program {
    public:
        BasePostprocess(
            const std::string& fragmentShaderPath
        ) : Program(fmt::format("{}/{}/{}/vs.glsl", SHADER_PATH, POSTPROCESS, IDENTITY), fragmentShaderPath){}

        BasePostprocess(): BasePostprocess(fmt::format("{}/{}/{}/fs.glsl", SHADER_PATH, POSTPROCESS, IDENTITY)){}

        void setup(Frame& frame){
            texture = frame.getTexture();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);	
            uniformInt("screenTexture", 0);
        }

        virtual void use() const {
            Program::use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);	
        }

    private:
        GLuint texture;

    };
}

