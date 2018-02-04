#pragma once
#ifndef  _TECHNIQUE_H_
#define  _TECHNIQUE_H_

#include <list>
#include "mur_util.h"
#include "glm/glm.hpp"

class Technique
{
public:

	Technique();

	virtual ~Technique();

	virtual bool Init();

	void Enable();

protected:

	bool AttachShader(GLenum ShaderType, const char* pFileName);
	
	bool LinkProgram();

	GLint GetUniformLocation(const char* pUniformName);

	GLint GetProgramParam(GLenum param);

	GLuint m_Program;

private:

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_ShaderObjList;

};
#endif