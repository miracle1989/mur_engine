#pragma once

#ifndef _SHADOW_MAP_TECHNIQUE_
#define _SHADOW_MAP_TECHNIQUE_

#include "technique.h"

class shadow_map_technique : Technique
{
public:

	shadow_map_technique();

	~shadow_map_technique();

	bool Init();

	void SetMVP(const glm::mat4& mat);
	
	void SetTextureUnit(GLenum unit);

private:
	
	GLuint m_MVPLocation;
	
	GLuint m_TextureLocation;
};

#endif // !_SHADOW_MAP_TECHNIQUE_