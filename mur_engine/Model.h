#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include "basic_mesh.h"

class Model
{
public:
	std::vector<BasicMesh> m_Meshes;

	std::string m_FileName;

	bool m_GammaCorrection;

	Model(const std::string& file, bool bGammaCorrection = false);
	
	~Model();


private:
	void ProcessNode(aiNode* pNode, const aiScene* pScene);
	BasicMesh ProcessMesh(const aiMesh * pMesh, const aiScene * pScene);
	std::vector<Texture *> LoadMaterialTextures(const aiMaterial * material, const aiTextureType type, const std::string & name);
};

#endif

