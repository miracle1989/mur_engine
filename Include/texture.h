#pragma once
#ifndef _MUR_TEXTURE_H_
#define _MUR_TEXUTRE_H_
#include <string>
#include "stb_image/stb_image.h"
#include "mur_util.h"
#include "assimp/material.h"

class Texture
{
public:
	Texture(GLenum target, std::string & path);
	Texture(GLenum target, aiTextureType type, std::string& path);
	
	void Load();

	void Bind(GLuint texUnit);

	int GetType();

	void SetType(aiTextureType type);

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