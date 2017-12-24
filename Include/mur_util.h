#pragma once

#ifndef _MUR_UTIL_H_
#define _MUR_UTIL_H_

#include <string>
#include <Windows.h>
#include "GL/glew.h"

#define INVALIDATE_LOCATION -1

#define MUR_ERROR(pError) Error(__FILE__, __LINE__, pError) 
void Error(const char* file, int line, const char* pError);

#define SAFE_DELETE(p) if(p){delete p; p = NULL;}

void ReadFile(std::string& outString, const char* pFileName);

long long GetCurrentTimeMS();

inline void GLCheckError()
{
	GLenum ret = glGetError();

	if (ret != GL_NO_ERROR)
	{
		MUR_ERROR("glGetError fail");
	}
}

long long GetCurrentTimeMS();







#endif