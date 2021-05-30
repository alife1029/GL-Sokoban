#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "API.hpp"
#include <exception>
#include <string>

namespace engine 
{

    class ENGINE_API Exception : public std::exception
    {
    public:
        Exception(int line, const char* file) noexcept;
        const char* what() const noexcept override;
        virtual const char* GetType() const noexcept;
        int GetLine() const noexcept;
        const std::string& GetFile() const noexcept;
        virtual std::string GetOriginString() const noexcept;
    private:
        int line;
        std::string file;
    protected:
        mutable std::string whatBuffer;
    };



    class ENGINE_API NotFoundException : public Exception
    {
    public:
        NotFoundException(int line, const char* file, std::string nf) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        std::string nf;
    };



    class ENGINE_API ShaderCompileException : public Exception
    {
    public:
        ShaderCompileException(int line, const char* file, std::string shaderFile, std::string gpuLog, std::string shaderType) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        std::string shaderType;
        std::string shaderFile;
        std::string gpuLog;
    };



    class ENGINE_API ProgramLinkingException : public Exception
    {
    public:
        ProgramLinkingException(int line, const char* file, std::string gpuLog) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        std::string gpuLog;
    };



    class ENGINE_API OpenGLException : public Exception
    {
    public:
        OpenGLException(int line, const char* file, unsigned int errorCode) noexcept;
        OpenGLException(int line, const char* file, std::string description) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        void TranslateMessage() noexcept;
    private:
        unsigned int errorCode;
        std::string description;
    };


    // TODO: Remove comment when OpenAL features added
    /*
    class ENGINE_API OpenALException : public Exception
    {
    public:
        OpenALException(int line, const char* file, unsigned int errorCode) noexcept;
        OpenALException(int line, const char* file, std::string description) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        void TranslateMessage() noexcept;
    private:
        unsigned int errorCode;
        std::string description;
    };
    */


    class ENGINE_API EngineException : public Exception
    {
    public:
        EngineException(int line, const char* file, std::string description) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        std::string description;
    };

}









// Useful Macros
#define THROW_EXCEPTION() throw engine::Exception(__LINE__, __FILE__)
#define THROW_NOT_FOUND_EXCEPTION(____nf____) throw engine::NotFoundException(__LINE__, __FILE__, ____nf____)
#define THROW_SHADER_COMPILE_EXCEPTION(____shaderFile____, ____gpuLog____, ____shaderType____) throw engine::ShaderCompileException(__LINE__, __FILE__, ____shaderFile____, ____gpuLog____, ____shaderType____)
#define THROW_PROGRAM_LINKING_EXCEPTION(____gpuLog____) throw engine::ProgramLinkingException(__LINE__, __FILE__, ____gpuLog____)
#define THROW_OPENGL_EXCEPTION(____errCode____) throw engine::OpenGLException(__LINE__, __FILE__, ____errCode____)
#define THROW_OPENAL_EXCEPTION(____errCode____) throw engine::OpenALException(__LINE__, __FILE__, ____errCode____)
#define THROW_ENGINE_EXCEPTION(____description____) throw engine::EngineException(__LINE__, __FILE__, ____description____)

#endif
