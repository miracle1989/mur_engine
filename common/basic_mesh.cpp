#include "..\Include\basic_mesh.h"

BasicMesh::BasicMesh()
{
	m_VAO = 0;
}

BasicMesh::BasicMesh(std::vector<Vertex> vertex, std::vector<unsigned int> indices, std::vector<Texture *> textures)
{
	m_Vertexs = vertex;
	m_Indices = indices;
	m_Textures = textures;

	SetupMesh();
}

BasicMesh::~BasicMesh()
{
	for (int i = 0; i < m_Textures.size(); i++)
	{
		SAFE_DELETE(m_Textures[i]);
	}

	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}
}

bool BasicMesh::LoadMesh(const std::string& fileName)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	bool Ret = false;

	Assimp::Importer importer;
	const aiScene* pSence = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_FindDegenerates);
	
	if (pSence)
	{
		Ret = InitFromSence(pSence, fileName);
	}
	
	return false;
}

void BasicMesh::Render()
{
	for (int i = 0; i < m_Textures.size(); i++)
	{
		GLuint texUint = 0;
		switch (m_Textures[i]->GetType())
		{
		case aiTextureType_DIFFUSE:
			texUint = DIFFUSE_TEXTURE_UINT;
			break;
		case aiTextureType_SPECULAR:
			texUint = SPECULAR_TEXTURE_UNIT;
			break;
		case aiTextureType_AMBIENT:
			texUint = AMBIENT_TEXTURE_UNIT;
			break;
		case aiTextureType_NORMALS:
			texUint = NORMAL_TEXTURE_UNIT;
			break;
		case aiTextureType_HEIGHT:
			texUint = HEIGHT_TEXTURE_UNIT;
			break;
		default:
			assert(0);
			break;
		}

		m_Textures[i]->Bind(texUint);
	}

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);

}

bool BasicMesh::InitFromSence(const aiScene * pSence, const std::string & fileName)
{
	
	
	return false;
}

void BasicMesh::SetupMesh()
{
	GLuint VBO, IBO;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertexs.size() * sizeof(Vertex), &m_Vertexs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tanget));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}