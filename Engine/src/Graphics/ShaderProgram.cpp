#include "Engine/Graphics/ShaderProgram.hpp"
#include "Engine/File.hpp"
#include "Engine/Exception.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
    ShaderProgram::ShaderProgram()
    {
        mId = 0;
    }

    ShaderProgram::ShaderProgram(const char* vs, const char* fs)
    {
        Initiaize(vs, fs);
    }
    
    void ShaderProgram::Initiaize()
    {
        mId = glCreateProgram();
    }

    void ShaderProgram::Initiaize(const char* vs, const char* fs)
    {
        Initiaize();
        AttachShader(vs, GL_VERTEX_SHADER);
        AttachShader(fs, GL_FRAGMENT_SHADER);
        Link();
    }

    void ShaderProgram::AttachShader(const char* file, unsigned int type)
    {
        const std::string strSrc = File::ReadText(file);
        const char* src = strSrc.c_str();
        unsigned int shader = glCreateShader(type);

        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        int isCompiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (!isCompiled)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            glDeleteShader(shader);
            THROW_SHADER_COMPILE_EXCEPTION(file, infoLog, type);
        }

        glAttachShader(mId, shader);
        glDeleteShader(shader);
    }

    void ShaderProgram::Link()
    {
        glLinkProgram(mId);
        int linkStatus;
        glGetProgramiv(mId, GL_LINK_STATUS, &linkStatus);
        if (!linkStatus)
        {
            char infoLog[512];
            glGetProgramInfoLog(mId, 512, NULL, infoLog);
            glDeleteProgram(mId);
            THROW_PROGRAM_LINKING_EXCEPTION(infoLog);
        }
    }

    void ShaderProgram::Use()
    {
        glUseProgram(mId);
    }

    // Uniforms
    void ShaderProgram::AddUniform(const std::string& var)
    {
        mUniforms[var] = glGetUniformLocation(mId, var.c_str());
    }
    void ShaderProgram::SetUniformVec2(const std::string& var, const glm::vec2& val)
    {
        glUniform2f(mUniforms[var], val.x, val.y);
    }
    void ShaderProgram::SetUniformVec3(const std::string& var, const glm::vec3& val)
    {
        glUniform3f(mUniforms[var], val.x, val.y, val.z);
    }
    void ShaderProgram::SetUniformVec4(const std::string& var, const glm::vec4& val)
    {
        glUniform4f(mUniforms[var], val.r, val.g, val.b, val.a);
    }
    void ShaderProgram::SetUniformMat4(const std::string& var, const glm::mat4& val)
    {
        glUniformMatrix4fv(mUniforms[var], 1, GL_FALSE, glm::value_ptr(val));
    }

    unsigned int ShaderProgram::Id()
    {
        return mId;
    }
}
