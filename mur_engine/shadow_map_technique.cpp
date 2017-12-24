#include "stdafx.h"
#include "shadow_map_technique.h"


shadow_map_technique::shadow_map_technique()
{

}


shadow_map_technique::~shadow_map_technique()
{
}

bool shadow_map_technique::Init()
{
	if (Technique::Init())
		return false;

	if (!AttachShader(GL_VERTEX_SHADER, "shadow_map.vs"))
		return false;

	if (!AttachShader(GL_FRAGMENT_SHADER, "shadow_map.ps"))
		return false;

	if (!LinkProgram())
		return false;

	m_MVPLocation = GetUniformLocation("gMVP");
	m_TextureLocation = GetUniformLocation("gShadowMap");

	if(m_MVPLocation == INVALIDATE_LOCATION || m_TextureLocation == INVALIDATE_LOCATION)
		return false;

	return true;
}

void shadow_map_technique::SetMVP(const glm::mat4& mvp)
{
	glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &mvp[0][0]);
}

void shadow_map_technique::SetTextureUnit(GLenum unit)
{
	glUniform1i(m_TextureLocation, unit);
}
