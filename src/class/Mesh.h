#pragma once
#include<glm/glm.hpp>
#include<GL/glew.h>
#include<iostream>
#include<string>
#include<vector>
#include"Shader.h"
using namespace std;
struct Vertex {
	// position
	glm::vec3 position;
	// normal
	glm::vec3 normal;
	// texCoords
	glm::vec2 uv;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};
class Mesh
{


private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;
	Mesh(std::vector<Vertex> vertexs,std::vector<Texture> textures,std::vector<unsigned int > indicies);
	void Draw(Shader &shader);


};

