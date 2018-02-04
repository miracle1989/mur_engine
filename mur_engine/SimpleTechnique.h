#pragma once
#include "technique.h"
class SimpleTechnique : public Technique
{
public:

	SimpleTechnique();
	
	~SimpleTechnique();

	bool Init();

	void SetMVP(glm::mat4& mvp);

private:

	GLuint m_MVPLocation;
};

