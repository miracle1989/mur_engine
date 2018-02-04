#pragma once

#ifndef _LIGHTING_TECHNIQUE_H_
#define _LIGHTING_TECHNIQUE_H_

#include "technique.h"

class BasicLight
{
public :
	std::string Name;
	glm::vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	BasicLight()
	{
		Color = glm::vec3(0.0f, 0.0f, 0.0f);
		AmbientIntensity = 0;
		DiffuseIntensity = 0;
	}
};

class DirectionalLight :public BasicLight
{
public:
	glm::vec3 Direction;
	DirectionalLight()
	{
		Direction = glm::vec3(0.0f);
	}
};

struct LightAttenuation
{
	float Constant;
	float Linear;
	float Exp;
};

class PointLight : public BasicLight
{
public:
	glm::vec3 Position;
	LightAttenuation Attenuation;

	PointLight()
	{
		Position = glm::vec3(0.0f);
		memset(&Attenuation, 0, sizeof(Attenuation));
	}
};

class SpotLight : public PointLight
{
public:
	glm::vec3 Direction;
	float CutOff;

	SpotLight()
	{
		Direction = glm::vec3(0.0f);
		CutOff = 0;
	}
};


class LightingTechnique : public Technique
{
public:

	static const unsigned int MAX_POINT_LIGHT = 2;
	static const unsigned int MAX_SPOT_LIGHT = 2;

	LightingTechnique();

	~LightingTechnique();

	virtual bool Init();

	void SetMVP(const glm::mat4& mvp);

	void SetLightMVP(const glm::mat4& mvp);

	void SetWorldMatrix(const glm::mat4& w);

	void SetTextureUnit(GLenum unit);

	void SetShadowMapTextureUnit(GLenum unit);

	void SetDirectionalLight(unsigned int numLights, const DirectionalLight& light);

	void SetPointLight(unsigned int numLights, const PointLight* light);

	void SetSpotLight(unsigned int numLights, const SpotLight* light);

	void SetEyeWorldPos(const glm::vec3 pos);

	void SetSpecularIntensity(float intensity);

	void SetSpecularPower(float power);

private:

	GLint m_MVPLocation;

	GLint m_LightMVPLocation;

	GLint m_WorldMatrixLocation;

	GLint m_TextureSamplerLocation;

	GLint m_ShadowMapLocation;

	GLint m_EyeWorldPosLocation;

	GLint m_SpecularIntensityLocation;

	GLint m_SpecularPowerLocation;

	struct
	{
		GLint Color;
		GLint AmbientIntensity;
		GLint DiffuseIntensity;
		GLint Direction;
	}m_DirectionalLightLocation;


	struct
	{
		GLint Color;
		GLint AmbientIntensity;
		GLint DiffuseIntensity;
		GLint Pos;
		struct
		{
			GLint Constant;
			GLint Linear;
			GLint Exp;
		}Atten;
	}m_PointLightLocation[MAX_POINT_LIGHT];

	struct
	{
		GLint Color;
		GLint AmbientIntensity;
		GLint DiffuseIntensity;
		GLint Pos;
		GLint Direction;
		GLint CutOff;
		struct
		{
			GLint Constant;
			GLint Linear;
			GLint Exp;
		}Atten;
	}m_SpotLightLocaiton[MAX_SPOT_LIGHT];
};


#endif // !_LIGHTING_TECHNIQUE_H_
