#include "texture.h"
#include <assert.h>


Texture::Texture(GLenum target, std::string & path)
{
	m_Target = target;
	m_Path = path;
	m_Type = -1;
}

Texture::Texture(GLenum target, aiTextureType type, std::string & path)
{
}

void Texture::Load()
{	
	int width, height, noComponents;
	unsigned char* data = stbi_load(m_Path.c_str(), &width, &height, &noComponents, 0);

	if (data)
	{
		m_Width = width;
		m_Height = height;

		switch(noComponents)
		{
			case 1:
				m_Format = GL_RED;
				break;
			case 3:
				m_Format = GL_RGB;
				break;
			case 4:
				m_Format = GL_RGBA;
				break;
			default:
				assert(0);
				break;
		}

		glGenTextures(1, &m_ID);

		glTexImage2D(m_Target, 0, m_Format, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		MUR_ERROR("can't load texture");
	}
	
}

void Texture::Bind(GLuint texUnit)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

int Texture::GetType()
{
	return m_Type;
}

int Texture::SetType(aiTextureType type)
{
	m
}
