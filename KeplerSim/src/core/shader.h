#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
   public:
    Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    inline void Bind() const { glUseProgram(m_RendererID); }
    inline void Unbind() const { glUseProgram(0); }

    /* Utility uniform functions */
    void SetUniformInt(const std::string& name, int value) const;
    void SetUniformIntArray(const std::string& name, int* values, uint32_t count) const;
    void SetUniformFloat(const std::string& name, float value) const;
    void SetUniformFloat2(const std::string& name, const glm::vec2& value) const;
    void SetUniformFloat3(const std::string& name, const glm::vec3& value) const;
    void SetUniformFloat4(const std::string& name, const glm::vec4& value) const;
    void SetUniformMat4(const std::string& name, const glm::mat4& value) const;

   private:
    static uint32_t CompileShader(uint32_t type, const std::string& source);
    uint32_t m_RendererID;
};