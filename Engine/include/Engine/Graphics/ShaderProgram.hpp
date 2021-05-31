#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <map>
#include <string>

#include <glm/glm.hpp>

namespace engine
{
    class ShaderProgram
    {
    public:
        ShaderProgram();
        ShaderProgram(const char* vs, const char* fs);
        ~ShaderProgram();

        void Initiaize();
        void Initiaize(const char* vs, const char* fs);
        void AttachShader(const char* file, unsigned int type);
        void Link();

        void Use();

        // Uniforms
        void AddUniform(const std::string& var);
        void SetUniformVec2(const std::string& var, const glm::vec2& val);
        void SetUniformVec3(const std::string& var, const glm::vec3& val);
        void SetUniformVec4(const std::string& var, const glm::vec4& val);
        void SetUniformMat4(const std::string& var, const glm::mat4& val);

        unsigned int Id();
    private:
        unsigned int mId;
        std::map<std::string, int> mUniforms;
    };
}

#endif
