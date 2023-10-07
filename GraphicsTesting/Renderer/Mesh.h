#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"



class Mesh {
private:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    VertexArray* m_vao;
    VertexBuffer* m_vbo;
    ElementBuffer* m_ebo;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

public:
    Mesh(const char* filePath);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	void Render(Shader shader);

private:
    void LoadMesh(const char* filePath);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void FinalizeMesh();
};