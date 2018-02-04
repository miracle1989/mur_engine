#include "stdafx.h"
#include "Model.h"

void Model::LoadModel(const std::string & fileName, bool bGammaCorrection)
{
	Assimp::Importer importer;
	const aiScene* pSence = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_FindDegenerates);

	if (pSence == NULL)
	{
		MUR_ERROR(fileName.c_str());
	}

	m_FileName = fileName;

	ProcessNode(pSence->mRootNode, pSence);
}

Model::Model():m_GammaCorrection(false)
{
}

Model::~Model()
{
}

void Model::Draw()
{
	for (auto mesh : m_Meshes)
	{
		mesh.Render();
	}
}

void Model::ProcessNode(aiNode* pNode, const aiScene* pScene)
{
	for (int i = 0; i < pNode->mNumMeshes; i++)
	{
		aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];

		m_Meshes.push_back(ProcessMesh(pMesh, pScene));
	}

	for (int i = 0; i < pNode->mNumChildren; i++)
	{
		ProcessNode(pNode->mChildren[i], pScene);
	}
}

BasicMesh Model::ProcessMesh(const aiMesh* pMesh, const aiScene* pScene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture *> textures;

	for (int i = 0; i < pMesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.Position.x = pMesh->mVertices[i].x;
		vertex.Position.y = pMesh->mVertices[i].y;
		vertex.Position.z = pMesh->mVertices[i].z;

		vertex.Normal.x = pMesh->mNormals[i].x;
		vertex.Normal.y = pMesh->mNormals[i].y;
		vertex.Normal.z = pMesh->mNormals[i].z;

		if (pMesh->mTextureCoords[0] != NULL)
		{
			vertex.TexCoords.x = pMesh->mTextureCoords[0][i].x;
			vertex.TexCoords.y = pMesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}


		//vertex.Tanget.x = pMesh->mTangents[i].x;
		//vertex.Tanget.y = pMesh->mTangents[i].y;
		//vertex.Tanget.z = pMesh->mTangents[i].z;

		//vertex.Bitangent.x = pMesh->mBitangents[i].x;
		//vertex.Bitangent.x = pMesh->mBitangents[i].y;
		//vertex.Bitangent.x = pMesh->mBitangents[i].z;
		
		vertices.push_back(vertex);
	}

	for (int i = 0; i < pMesh->mNumFaces; i++)
	{
		aiFace  face = pMesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	{
		aiMaterial* material = pScene->mMaterials[pMesh->mMaterialIndex];

		std::vector<Texture *> diffuseMaps =  LoadMaterialTextures(material, aiTextureType_DIFFUSE, "tex_diffuse");
		std::vector<Texture *> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "tex_specular");
		std::vector<Texture *> ambientMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "tex_ambient");
		std::vector<Texture *>  normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "tex_normal");
		std::vector<Texture *> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "tex_height");

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return BasicMesh(vertices, indices, textures);

}

std::vector<Texture *> Model::LoadMaterialTextures(const aiMaterial* material, const aiTextureType type, const std::string& name)
{	
	std::vector<Texture *> textures;
	
	for (int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);

		//TODO: may cause issue.
//		Texture tex = Texture();


//		tex.SetType(type);

//		textures.push_back(&tex);
	}

	return textures;
}

void TextureFromFile(const char* texName, const char* Directory)
{
	std::string fileName = std::string(Directory) + '/' + std::string(texName);

	unsigned int texID;
	glGenTextures(1, &texID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		switch (nrComponents)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			assert(0);
		}

		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}
