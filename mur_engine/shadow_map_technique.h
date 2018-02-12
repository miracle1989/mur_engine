#pragma once

#ifndef _SHADOW_MAP_TECHNIQUE_
#define _SHADOW_MAP_TECHNIQUE_

#include "technique.h"

class ShadowMapTechnique : public Technique
{
public:

	ShadowMapTechnique();

	~ShadowMapTechnique();

	bool Init();

	void SetMVP(const glm::mat4& mat);
	
	void SetTextureUnit(GLenum unit);
	
	glm::mat4 GetMVP();

private:
	
	glm::mat4  m_LightMVP;

	GLuint     m_MVPLocation;
	
	GLuint     m_TextureLocation;
};

#endif // !_SHADOW_MAP_TECHNIQUE_