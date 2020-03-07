#pragma once

#include <iostream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <SOIL2.h>

class Texture
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;
	GLint textureUnit;

public:
	Texture(const char* filename, GLenum type, GLint texture_unit);

	~Texture();

	//ASK SOMEONE!!!!!!
	inline GLuint getID()const
	{
		return this->id;
	}

	void bind();

	void unbind();

	//ASK SOMEONE!!!!!!!
	inline GLint getTextureUnit()const
	{
		return this->textureUnit;
	}
};

