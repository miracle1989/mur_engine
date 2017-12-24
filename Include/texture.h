#pragma once
#ifndef _MUR_TEXTURE_H_
#define _MUR_TEXUTRE_H_
#include "GL/glew.h"
#include <string>
#include "stb_image/stb_image.h"
#include "mur_util.h"

class Texture
{
public:
	Texture(GLenum target, aiTextureType type, std::string& path);
	
	void Load();

	void Bind(GLuint texUnit);

	int GetType();

	int SetType(aiTextureType type);

private:
	GLuint			m_ID;
	GLuint			m_Format;
	GLuint			m_Target;
	GLint			m_Width;
	GLint			m_Height;
	std::string     m_Path;
	aiTextureType   m_Type;
};







#endif