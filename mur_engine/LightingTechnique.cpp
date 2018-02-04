#include "LightingTechnique.h"


LightingTechnique::LightingTechnique()
{
}


LightingTechnique::~LightingTechnique()
{
}

bool LightingTechnique::Init()
{
	if (!Technique::Init())
		return false;

	if (!AttachShader(GL_VERTEX_SHADER, "../shaders/lighting.vs"))
		return false;

	if (!AttachShader(GL_FRAGMENT_SHADER, "../shaders/lighting.ps"))
		return false;

	if (!LinkProgram())
		return false;

	m_MVPLocation = GetUniformLocation("gMVP");

	m_LightMVPLocation = GetUniformLocation("gLightMVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_TextureSamplerLocation = GetUniformLocation("gSampler");
	m_ShadowMapLocation = GetUniformLocation("gShadowMap");
	m_EyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
	m_SpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	m_SpecularPowerLocation = GetUniformLocation("gSpecularPower");

	{
		m_DirectionalLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
		m_DirectionalLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
		m_DirectionalLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
		m_DirectionalLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");

		if (m_DirectionalLightLocation.Color == INVALIDATE_LOCATION ||
			m_DirectionalLightLocation.AmbientIntensity == INVALIDATE_LOCATION ||
			m_DirectionalLightLocation.DiffuseIntensity == INVALIDATE_LOCATION ||
			m_DirectionalLightLocation.Direction == INVALIDATE_LOCATION)
		{
			MUR_ERROR("%s invalidata location", __function__);
			return false;
		}
	}

	for (unsigned int i = 0; i < ARRAYSIZE(m_PointLightLocation); i++)
	{
		char name[128];
		memset(name, 0, sizeof(name));

		snprintf(name, sizeof(name), "gPointLight[%d].Base.Color", i);
		m_PointLightLocation[i].Color = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gPointLight[%d].Base.AmbientIntensity", i);
		m_PointLightLocation[i].AmbientIntensity = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gPointLight[%d].Pos", i);
		m_PointLightLocation[i].Pos = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gPointLight[%d].Base.DiffuseIntensity", i);
		m_PointLightLocation[i].DiffuseIntensity = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gPointLight[%d].Atten.Constant", i);
		m_PointLightLocation[i].Atten.Constant = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gPointLight[%d].Atten.Linear", i);
		m_PointLightLocation[i].Atten.Linear = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gPointLight[%d].Atten.Exp", i);
		m_PointLightLocation[i].Atten.Exp = GetUniformLocation(name);

		if (m_PointLightLocation[i].Color == INVALIDATE_LOCATION ||
			m_PointLightLocation[i].AmbientIntensity == INVALIDATE_LOCATION ||
			m_PointLightLocation[i].Pos == INVALIDATE_LOCATION ||
			m_PointLightLocation[i].DiffuseIntensity == INVALIDATE_LOCATION ||
			m_PointLightLocation[i].Atten.Constant == INVALIDATE_LOCATION ||
			m_PointLightLocation[i].Atten.Linear == INVALIDATE_LOCATION ||
			m_PointLightLocation[i].Atten.Exp == INVALIDATE_LOCATION)
		{
			MUR_ERROR("%s invalidata location", __function__);
			return false;
		}
	}

	for (unsigned int i = 0; i < ARRAYSIZE(m_SpotLightLocaiton); i++)
	{
		char name[128];
		memset(name, 0, sizeof(name));

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Base.Color", i);
		m_SpotLightLocaiton[i].Color = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Base.AmbientIntensity", i);
		m_SpotLightLocaiton[i].AmbientIntensity = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Pos", i);
		m_SpotLightLocaiton[i].Pos = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Base.DiffuseIntensity", i);
		m_SpotLightLocaiton[i].DiffuseIntensity = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Direction", i);
		m_SpotLightLocaiton[i].Direction = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].CutOff", i);
		m_SpotLightLocaiton[i].CutOff = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Atten.Constant", i);
		m_SpotLightLocaiton[i].Atten.Constant = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Atten.Linear", i);
		m_SpotLightLocaiton[i].Atten.Linear = GetUniformLocation(name);

		snprintf(name, sizeof(name), "gSpotLight[%d].Base.Atten.Exp", i);
		m_SpotLightLocaiton[i].Atten.Exp = GetUniformLocation(name);

		if (m_SpotLightLocaiton[i].Color == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].AmbientIntensity == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].Pos == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].DiffuseIntensity == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].Direction == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].CutOff == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].Atten.Constant == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].Atten.Linear == INVALIDATE_LOCATION ||
			m_SpotLightLocaiton[i].Atten.Exp == INVALIDATE_LOCATION)
		{	
			MUR_ERROR("lighting tech invalidate location");
			return false;
		}
	}


	return true;
}

void LightingTechnique::SetMVP(const glm::mat4 & mvp)
{
	glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, &mvp[0][0]);
}

void LightingTechnique::SetLightMVP(const glm::mat4 & mvp)
{
	glUniformMatrix4fv(m_LightMVPLocation, 1, GL_FALSE, &mvp[0][0]);
}

void LightingTechnique::SetWorldMatrix(const glm::mat4 & w)
{
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, &w[0][0]);
}

void LightingTechnique::SetTextureUnit(GLenum unit)
{
	glUniform1i(m_TextureSamplerLocation, unit);
}

void LightingTechnique::SetShadowMapTextureUnit(GLenum unit)
{
	glUniform1i(m_ShadowMapLocation, unit);
}

void LightingTechnique::SetDirectionalLight(unsigned int numLights, const DirectionalLight&  light)
{
	glUniform3f(m_DirectionalLightLocation.Color, light.Color.x, light.Color.y, light.Color.z);
	glUniform1f(m_DirectionalLightLocation.AmbientIntensity, light.AmbientIntensity);
	glUniform1f(m_DirectionalLightLocation.DiffuseIntensity, light.DiffuseIntensity);

	glm::vec3 Direction = light.Direction;
	Direction = glm::normalize(Direction);
	glUniform3f(m_DirectionalLightLocation.Direction, Direction.x, Direction.y, Direction.z);
}

void LightingTechnique::SetPointLight(unsigned int numLights, const PointLight * light)
{
	for (int i = 0; i < numLights; i++)
	{
		glUniform3f(m_PointLightLocation[i].Color, light->Color.x, light->Color.y, light->Color.z);
		glUniform1f(m_PointLightLocation[i].AmbientIntensity, light->AmbientIntensity);
		glUniform1f(m_PointLightLocation[i].DiffuseIntensity, light->DiffuseIntensity);
		glUniform3f(m_PointLightLocation[i].Pos, light->Position.x, light->Position.y, light->Position.z);
		glUniform1f(m_PointLightLocation[i].Atten.Constant, light->Attenuation.Constant);
		glUniform1f(m_PointLightLocation[i].Atten.Linear, light->Attenuation.Linear);
		glUniform1f(m_PointLightLocation[i].Atten.Exp, light->Attenuation.Exp);
	}
}

void LightingTechnique::SetSpotLight(unsigned int numLights, const SpotLight * light)
{
	for (int i = 0; i < numLights; i++)
	{
		glUniform3f(m_SpotLightLocaiton[i].Color, light->Color.x, light->Color.y, light->Color.z);
		glUniform1f(m_SpotLightLocaiton[i].AmbientIntensity, light->AmbientIntensity);
		glUniform1f(m_SpotLightLocaiton[i].DiffuseIntensity, light->DiffuseIntensity);
		glUniform3f(m_SpotLightLocaiton[i].Pos, light->Position.x, light->Position.y, light->Position.z);
		glUniform1f(m_SpotLightLocaiton[i].Atten.Constant, light->Attenuation.Constant);
		glUniform1f(m_SpotLightLocaiton[i].Atten.Linear, light->Attenuation.Linear);
		glUniform1f(m_SpotLightLocaiton[i].Atten.Exp, light->Attenuation.Exp);
		glUniform1f(m_SpotLightLocaiton[i].CutOff, light->CutOff);

		glm::vec3 direction = light->Direction;
		glm::normalize(direction);
		glUniform3f(m_SpotLightLocaiton[i].Direction, direction.x, direction.y, direction.z);
	}
}

void LightingTechnique::SetEyeWorldPos(const glm::vec3 pos)
{
	glUniform3f(m_EyeWorldPosLocation, pos.x, pos.y, pos.z);
}

void LightingTechnique::SetSpecularIntensity(float intensity)
{
	glUniform1f(m_SpecularIntensityLocation, intensity);
}

void LightingTechnique::SetSpecularPower(float power)
{
	glUniform1f(m_SpecularPowerLocation, power);
}
