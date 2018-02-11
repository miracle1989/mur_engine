#include "ShadowMapFBO.h"


ShadowMapFBO::ShadowMapFBO():m_FBO(0),m_ShadowMap(0),m_Height(0),m_Width(0)
{
}

ShadowMapFBO::~ShadowMapFBO()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_ShadowMap);
}

bool ShadowMapFBO::Init(unsigned int width, unsigned int height)
{
	glGenTextures(1, &m_ShadowMap);
	glGenFramebuffers(1, &m_FBO);

	glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (void*)0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_ShadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		MUR_ERROR("shadow map fbo incomplete");
		return false;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void ShadowMapFBO::BindForWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void ShadowMapFBO::BindForReading(GLenum unit)
{
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
}

