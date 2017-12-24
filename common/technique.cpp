#include "technique.h"
#include <string.h>

Technique::Technique()
{
	m_Program = 0;
}

Technique::~Technique()
{
	for (ShaderObjList::iterator it = m_ShaderObjList.begin(); it != m_ShaderObjList.end(); it++)
	{
		glDeleteShader(*it);
	}

	if (m_Program != 0)
	{
		glDeleteProgram(m_Program);
	}
}

bool Technique::Init()
{
	m_Program = glCreateProgram();

	if (m_Program == 0)
	{
		fprintf(stderr, "Error create technique program");
		return false;
	}

	return true;
}

bool Technique::AttachShader(GLenum ShaderType, const char * pFileName)
{
	std::string s;

	ReadFile(s, pFileName);

	GLuint shaderObj = glCreateShader(ShaderType);

	if (shaderObj == 0)
	{
		fprintf(stderr, "error attach shader");
		return false;
	}

	const char* source = s.c_str();
	GLint size = s.size();
	glShaderSource(ShaderType, 1, &source, &size);
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar log[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, log);
		fprintf(stderr, "error compile shader %s, %s \n", pFileName, log);
		return false;
	}

	glAttachShader(m_Program, shaderObj);

	return true;
}

bool Technique::LinkProgram()
{
	glLinkProgram(m_Program);

	GLint success;
	char log[1024];

	glGetProgramiv(m_Program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(m_Program, 1024, NULL, log);
		fprintf(stderr, "program %d link fail, error message: %s ", m_Program, log);
		return false;
	}

	glValidateProgram(m_Program);
	glGetProgramiv(m_Program, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_Program, 1024, NULL, log);
		fprintf(stderr, "program %d validate fail, error message: %s ", m_Program, log);
		return false;
	}

	return true;
}

void Technique::Enable()
{
	glUseProgram(m_Program);
}

GLint Technique::GetUniformLocation(const char* pUniformName)
{
	GLint location = glGetUniformLocation(m_Program, pUniformName);

	if (location == INVALIDATE_LOCATION)
	{
		fprintf(stderr, "error get uniform location %s", pUniformName);
	}

	return location;
}

GLint Technique::GetProgramParam(GLenum param)
{
	GLint ret;
	glGetProgramiv(m_Program, param, &ret);
	return ret;
}

