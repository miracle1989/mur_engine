#include "stdafx.h"
#include "SimpleTechnique.h"


SimpleTechnique::SimpleTechnique()
{
}


SimpleTechnique::~SimpleTechnique()
{
}

bool SimpleTechnique::Init()
{
	if (!Technique::Init())
		return false;

	if (!AttachShader(GL_VERTEX_SHADER, "../shaders/simple.vs"))
		return false;

	if (!AttachShader(GL_FRAGMENT_SHADER, "../shaders/simple.ps"))
		return false;

	if (!LinkProgram())
		return false;

	m_MVPLocation = GetUniformLocation("gMVP");

	if (m_MVPLocation == INVALIDATE_LOCATION)
	{
		assert(0);
	}

	return true;
}

void SimpleTechnique::SetMVP(glm::mat4& mvp)
{
	glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, &mvp[0][0]);
}
