#include "Engine/Exception.hpp"
#include <sstream>
#include <glad/glad.h>
//#include <AL/al.h>

namespace engine {

    Exception::Exception(int line, const char* file) noexcept
        :
        line(line),
        file(file)
    { }

    const char* Exception::what() const noexcept
    {
        std::ostringstream oss;
        oss << "[ERROR TYPE] " << GetType() << std::endl
            << GetOriginString();
        whatBuffer = oss.str();
        return whatBuffer.c_str();
    }

    const char* Exception::GetType() const noexcept
    {
        return "Alife Exception";
    }

    int Exception::GetLine() const noexcept
    {
        return line;
    }

    const std::string& Exception::GetFile() const noexcept
    {
        return file;
    }

    std::string Exception::GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << "[FILE] " << file << std::endl
            << "[LINE] " << line;
        return oss.str();
    }






    // Not Found Exception
    NotFoundException::NotFoundException(int line, const char* file, std::string nf) noexcept
        :
        Exception(line, file),
        nf(nf)
    { }

    const char* NotFoundException::GetType() const noexcept
    {
        return "Not Found Exception";
    }

    std::string NotFoundException::GetOriginString() const noexcept
    {
        std::stringstream ss;
        ss << Exception::GetOriginString() << std::endl << nf << " not found!";
        return ss.str();
    }




    // Shader compile exception
    ShaderCompileException::ShaderCompileException(int line, const char* file, std::string shaderFile, std::string gpuLog, unsigned int shaderType) noexcept
        :
        Exception(line, file),
        shaderType(shaderType),
        shaderFile(shaderFile),
        gpuLog(gpuLog)
    {
        TranslateMessage();
    }

    const char* ShaderCompileException::GetType() const noexcept
    {
        return "Shader Compile Exception";
    }

    std::string ShaderCompileException::GetOriginString() const noexcept
    {
        std::stringstream ss;
        ss  << Exception::GetOriginString() << std::endl
            << "[SHADER TYPE] " << strShaderType << std::endl
            << "[SHADER FILE] " << shaderFile << std::endl
            << "[GPU LOG] " << gpuLog << std::endl;
        return ss.str();
    }

    void ShaderCompileException::TranslateMessage() noexcept
    {
        switch (shaderType)
        {
        case GL_VERTEX_SHADER: strShaderType = "Vertex Shader"; break;
        case GL_FRAGMENT_SHADER: strShaderType = "Fragment Shader"; break;
        case GL_GEOMETRY_SHADER: strShaderType = "Geometry Shader"; break;
        default: strShaderType = "Unknown"; break;
        }
    }





    // Shader Program Linking exception
    ProgramLinkingException::ProgramLinkingException(int line, const char* file, std::string gpuLog) noexcept
        :
        Exception(line, file),
        gpuLog(gpuLog)
    { }

    const char* ProgramLinkingException::GetType() const noexcept
    {
        return "Shader Program Linking Exception";
    }

    std::string ProgramLinkingException::GetOriginString() const noexcept
    {
        std::stringstream ss;
        ss << Exception::GetOriginString() << std::endl << "[GPU LOG] " << gpuLog << std::endl;
        return ss.str();
    }






    // OpenGL Exception
    OpenGLException::OpenGLException(int line, const char* file, unsigned int errorCode) noexcept
        :
        Exception(line, file),
        errorCode(errorCode) 
    { 
        TranslateMessage();
    }

    OpenGLException::OpenGLException(int line, const char* file, std::string description) noexcept
        :
        Exception(line, file),
        errorCode(0),
        description(description) { }

    const char* OpenGLException::GetType() const noexcept
    {
        return "OpenGL Graphics Exception";
    }

    std::string OpenGLException::GetOriginString() const noexcept
    {
        std::stringstream ss;

        ss  << Exception::GetOriginString() << std::endl
            << "[ERROR CODE] " << errorCode << std::endl
            << "[DESCRIPTION] " << description << std::endl;

        return ss.str();
    }

    void OpenGLException::TranslateMessage() noexcept
    {
        switch(errorCode)
        {
        case 1280:  description = "GL_INVALID_ENUM"; break;
        case 1281:  description = "GL_INVALID_VALUE"; break;
        case 1282:  description = "GL_INVALID_OPERATION"; break;
        case 1283:  description = "GL_STACK_OVERFLOW"; break;
        case 1284:  description = "GL_STACK_UNDERFLOW"; break;
        case 1285:  description = "GL_OUT_OF_MEMORY"; break;
        case 1286:  description = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
        default:    description = "Undefined Error Code"; break;
        };
    }





    // OpenAL Exception
    /*
    OpenALException::OpenALException(int line, const char* file, std::string description) noexcept
        :
        Exception(line, file),
        errorCode(0),
        description(description) { }

    OpenALException::OpenALException(int line, const char* file, unsigned int errorCode) noexcept
        :
        Exception(line, file),
        errorCode(errorCode)
    { 
        TranslateMessage();
    }

    const char* OpenALException::GetType() const noexcept
    {
        return "OpenAL Audio Exception";
    }

    std::string OpenALException::GetOriginString() const noexcept
    {
        std::stringstream ss;

        ss  << Exception::GetOriginString() << std::endl
            << "[ERROR CODE] " << errorCode << std::endl
            << "[DESCRIPTION] " << description << std::endl;

        return ss.str();
    }

    void OpenALException::TranslateMessage() noexcept
    {
        switch(errorCode)
        {
        case AL_INVALID_NAME:       description = "AL_INVALID_NAME"; break;
        case AL_INVALID_ENUM:       description = "AL_INVALID_ENUM"; break;
        case AL_INVALID_VALUE:      description = "AL_INVALID_VALUE"; break;
        case AL_INVALID_OPERATION:  description = "AL_INVALID_OPERATION"; break;
        case AL_OUT_OF_MEMORY:      description = "AL_OUT_OF_MEMORY"; break;
        default:                    description = "Undefined Error Code"; break;
        };
    }
    */




    // Engine Exception
    EngineException::EngineException(int line, const char* file, std::string description) noexcept
        :
        Exception(line, file),
        description(description)
    { }

    const char* EngineException::GetType() const noexcept
    {
        return "Game Engine Exception";
    }

    std::string EngineException::GetOriginString() const noexcept
    {
        std::stringstream ss;
        ss  << Exception::GetOriginString() << std::endl 
            << "[DESCRIPTION] " << description << std::endl;
        return ss.str();
    }
    
}
