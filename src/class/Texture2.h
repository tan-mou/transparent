#pragma once
#include<iostream>
#include<string>
#include<GL/glew.h>
#include"stb_image.h"
#define PNG 0
#define JPG 1
class Texture2{
private :
	unsigned int texture_id;
public:
	Texture2(unsigned int texture_position,std::string image_source,unsigned int type);
	void Bind();
	void UnBind();
	unsigned int  GetId() {
		return texture_id;
	}
};

