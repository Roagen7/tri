#include <tricore/program/Program.h>


namespace {
    static constexpr auto POSTPROCESS = "postprocess";
    static constexpr auto IDENTITY = "identity";
}

namespace tri::core::postprocess {
    
    class BasePostprocess : public Program {
    public:
        BasePostprocess(const std::string& vertexShaderPath
        , const std::string& fragmentShaderPath): Program(vertexShaderPath, fragmentShaderPath){}

        BasePostprocess(): Program(fmt::format("{}/{}/{}/vs.glsl", SHADER_PATH, POSTPROCESS, IDENTITY),fmt::format("{}/{}/{}/fs.glsl", SHADER_PATH, POSTPROCESS, IDENTITY)){}

        void setup(Frame& frame){
            texture = frame.getTexture();
        }

        virtual void use() const {
            glBindTexture(GL_TEXTURE_2D, texture);	
            Program::use();
        }

    private:
        GLuint texture;

    };
}

