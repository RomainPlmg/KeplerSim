#include "Texture.h"

#include "core/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& path, GLenum m_TextureUnit)
    : m_RendererID(0), m_TextureUnit(m_TextureUnit) {
    glGenTextures(1, &m_RendererID);
    glActiveTexture(m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image with stb_image
    stbi_set_flip_vertically_on_load(true);  // Flip verticaly images
    unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NbChannels, 0);

    if (data) {
        GLenum format{};
        switch (m_NbChannels) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGB;
                break;
        }

        // Load image datas into OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        CORE_ERROR("Failed to load texture: {0}", path);
    }

    // Libérer l'image après le chargement
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);  // Détache la texture
}

void Texture::Bind() const {
    glActiveTexture(m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

Texture::~Texture() { glDeleteTextures(1, &m_RendererID); }
