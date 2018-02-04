#pragma once

#ifndef _MUR_UTIL_H_
#define _MUR_UTIL_H_
#include "GLAD/glad.h"
#include <string>
#include <Windows.h>
#include <assert.h>

#define INVALIDATE_LOCATION -1

#define COLOR_TEXTURE_UNIT        GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX  0
#define SHADOW_TEXTURE_UNIT       GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX 1

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
		assert(0);
	}
}

long long GetCurrentTimeMS();







#endif