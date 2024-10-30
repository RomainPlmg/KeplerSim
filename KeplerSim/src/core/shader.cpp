#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include "log.h"
#include "utils/utils.h"

Shader::Shader(const std::string& name, const std::string& vertexPath,
               const std::string& fragmentPath) {
    /* Read shader codes */
    std::string vertexSrc = Utils::ParseFile(vertexPath);
    std::string fragmentSrc = Utils::ParseFile(fragmentPath);

    /* Compile shader codes */
    uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    m_RendererID = glCreateProgram();

    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(m_RendererID); }

void Shader::SetUniformInt(const std::string& name, int value) const {
    GLint uniformLoc = glGetUniformLocation(m_RendererID, name.c_str());
    if (uniformLoc == -1) {
        CORE_ERROR("Error: Unable to find the uniform \'{0}\'", name);
    }
    glUniform1i(uniformLoc, value);
}

void Shader::SetUniformIntArray(const std::string& name, int* values, uint32_t count) const {}

void Shader::SetUniformFloat(const std::string& name, float value) const {
    GLint uniformLoc = glGetUniformLocation(m_RendererID, name.c_str());
    if (uniformLoc == -1) {
        CORE_ERROR("Error: Unable to find the uniform \'{0}\'", name);
    }
    glUniform1f(uniformLoc, value);
}

void Shader::SetUniformFloat2(const std::string& name, const glm::vec2& value) const {}

void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& value) const {}

void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value) const {}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value) const {
    GLint uniformLoc = glGetUniformLocation(m_RendererID, name.c_str());
    if (uniformLoc == -1) {
        CORE_ERROR("Error: Unable to find the uniform \'{0}\'", name);
    }
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Print compile errors if any
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, NULL, message);
        CORE_ERROR("ERROR::Shader::{0}::COMPILATION_FAILED",
                   (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));
        CORE_ERROR("{0}", message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}