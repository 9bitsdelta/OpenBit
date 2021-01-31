#pragma once

#include "Core/Base.h"

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

#include <GL/glew.h>

namespace Bit {

    class Shader
    {
    public:
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        static Ref<Shader> Create(const std::string& filePath);

        Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        const std::string& GetName() const;

        void UploadUniformInt(const std::string& name, int value);

        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        
        void UploadUniformInt1v(const std::string& name, const int* values, const uint32_t& count);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    
    private:

        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };

}