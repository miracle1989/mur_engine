#pragma once
class Basic
{
public:
	
	Basic();
	
	~Basic();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

private:

	long long m_FrameTime;
	long long m_StartTime;
	int       m_FrameCount;
	int       m_FPS;
};

