#include "mur_util.h"
#include <fstream>
#include <sstream>

void ReadFile(std::string& outString, const char * pFileName)
{
	std::ifstream file;
	std::stringstream fileStringStream;
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		file.open(pFileName);

		fileStringStream << file.rdbuf();

		file.close();

		outString = fileStringStream.str();
	}
	catch(std::ifstream::failure e)
	{
		MUR_ERROR(pFileName);
	}
}

void Error(const char* file, int line, const char* pError)
{
	char msg[1024];
	_snprintf_s(msg, sizeof(msg), "%s : %d: can't open file %s", file, line, pError);
	printf(msg);
}

long long GetCurrentTimeMS()
{
	return GetTickCount();
}

