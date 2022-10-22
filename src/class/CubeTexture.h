#pragma once
#include<string>
#include<vector>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#define PNG 0
#define JPG 1
using namespace std;
class CubeTexture
{
private:unsigned int textureID;
public:
	CubeTexture(unsigned int texture_position, vector<string> faces, unsigned int type);
	void Bind();
	void UnBind();
};

