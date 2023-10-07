#include "Mesh.h"
#include <iostream>

Mesh::Mesh(const char* filePath) {
    LoadMesh(filePath);
	FinalizeMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->m_vertices = vertices;
	this->m_indices = indices;
	FinalizeMesh();
}

Mesh::~Mesh() {
    delete m_vao;
	delete m_vbo;
	delete m_ebo;
}

void Mesh::Render(Shader shader) {
	shader.Use();

	m_vao->Bind();
	m_ebo->Bind();
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	m_vao->Unbind();
	m_ebo->Unbind();
}

void Mesh::LoadMesh(const char* filePath) {
    Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
	}
	
	ProcessMesh(scene->mMeshes[0], scene);
}

void Mesh::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		
		glm::vec3 vector;
		
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		
		vertex.position = vector;
		
		if (mesh->mNormals) {
		    vector.x = mesh->mNormals[i].x;
		    vector.y = mesh->mNormals[i].y;
		    vector.z = mesh->mNormals[i].z;
		}
		
		vertex.normal = vector;
		
		if (mesh->mTextureCoords[0]) {
		    glm::vec2 vec;
		    
		    vec.x = mesh->mTextureCoords[0][i].x;
		    vec.y = mesh->mTextureCoords[0][i].y;
		    
		    vertex.texCoords = vec;
		} else {
		    vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		
		m_vertices.push_back(vertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
	    aiFace face = mesh->mFaces[i];
	    
	    for (unsigned int j = 0; j < face.mNumIndices; j++) {
			m_indices.push_back(face.mIndices[j]);
	    }
	}
}

void Mesh::FinalizeMesh() {
	m_vao = new VertexArray();
	m_vao->Bind();

	m_vbo = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
	m_ebo = new ElementBuffer(m_indices.data(), m_indices.size());

	m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	m_vao->LinkAttrib(*m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	m_vao->LinkAttrib(*m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	m_vao->Unbind();
}