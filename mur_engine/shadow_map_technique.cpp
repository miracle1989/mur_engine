#include "stdafx.h"
#include "shadow_map_technique.h"


ShadowMapTechnique::ShadowMapTechnique()
{

}


ShadowMapTechnique::~ShadowMapTechnique()
{
}

bool ShadowMapTechnique::Init()
{
	if (!Technique::Init())
		return false;

	if (!AttachShader(GL_VERTEX_SHADER, "../shaders/shadow_map.vs"))
		return false;

	if (!AttachShader(GL_FRAGMENT_SHADER, "../shaders/shadow_map.ps"))
		return false;

	if (!LinkProgram())
		return false;

	m_MVPLocation = GetUniformLocation("gMVP");

	if(m_MVPLocation == INVALIDATE_LOCATION)
		return false;

	return true;
}

void ShadowMapTechnique::SetMVP(const glm::mat4& mvp)
{
	m_LightMVP = mvp;
	glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, &mvp[0][0]);
}

void ShadowMapTechnique::SetTextureUnit(GLenum unit)
{
	glUniform1i(m_TextureLocation, unit);
}

glm::mat4 ShadowMapTechnique::GetMVP()
{
	return m_LightMVP;
}
