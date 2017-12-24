#pragma once

#ifndef _BASIC_MESH_H_
#define _BASIC_MESH_H_

#include "glm/glm.hpp"
#include <vector>
#include "texture.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#define DIFFUSE_TEXTURE_UINT   GL_TEXTURE0
#define SPECULAR_TEXTURE_UNIT  GL_TEXTURE1
#define AMBIENT_TEXTURE_UNIT   GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT    GL_TEXTURE3
#define HEIGHT_TEXTURE_UNIT    GL_TEXTURE4

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tanget;
	glm::vec3 Bitangent;
};


class BasicMesh
{
public:
	BasicMesh();
	BasicMesh(std::vector<Vertex> vertex, std::vector<unsigned int> indices, std::vector<Texture *> textures);
	
	~BasicMesh();

	bool LoadMesh(const std::string & fileName);

	bool LoadMesh();

	void Render();

private:
	std::vector<Vertex>  m_Vertexs;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture *> m_Textures;
	GLuint m_VAO;

	bool InitFromSence(const aiScene* pSence, const std::string& fileName);
	void SetupMesh();
};










#endif
