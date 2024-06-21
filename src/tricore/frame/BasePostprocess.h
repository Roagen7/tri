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

        void setup(ColorFrame& frame){
            colorAttachments = frame.getColorAttachments();
            colorAttachmentsCount = frame.getColorAttachmentsCount();
            for(auto i = 0u; i < colorAttachmentsCount; i++){
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);	
                uniformInt(fmt::format("colorAttachment{}", i), i);
            }
        }

        virtual void use() const {
            Program::use();
            for(auto i = 0u; i < colorAttachmentsCount; i++){
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);	
            }
        }

    private:
        GLuint* colorAttachments;
        GLuint colorAttachmentsCount{};

    };
}

