#pragma once

#include <glad/glad.h>

class Texture {
   public:
    Texture(const std::string& path, GLenum textureUnit = GL_TEXTURE0);
    ~Texture();

    void Bind() const;
    void Unbind() const;

    inline float GetWidth() const { return static_cast<float>(m_Width); }
    inline float GetHeight() const { return static_cast<float>(m_Height); }
    inline int GetNbChannels() const { return m_NbChannels; }

   private:
    unsigned int m_RendererID;  // ID of the texture
    GLenum m_TextureUnit;       // Unit of the texture (GL_TEXTURE0, GL_TEXTURE1, etc.)
    int m_Width, m_Height, m_NbChannels;
};
