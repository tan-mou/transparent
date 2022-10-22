#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<GL/glew.h>
#include<iostream>
#include<string>
#include<vector>
#include"stb_image.h"
#include"Mesh.h"



unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
class Model
{
public:

    Model(std::string path)
    {
        loadModel(path);
    }

    void Draw(Shader &shader);


private:

    std::vector<Mesh> meshes;
    std::string directory;
    vector<Texture> textures_loaded;
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,std::string typeName);
};

