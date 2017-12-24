#pragma once

#ifndef _SHADOW_MAP_FBO_
#define _SHADOW_MAP_FBO_

#include "mur_util.h"

class ShadowMapFBO
{
public:
	ShadowMapFBO();

	~ShadowMapFBO();

	bool Init(unsigned int width, unsigned int height);

	void BindForWriting();

	void BindForReading(GLenum unit);

private:

	unsigned int m_Width;

	unsigned int m_Height;

	GLuint m_ShadowMap;

	GLuint m_FBO;

};

#endif