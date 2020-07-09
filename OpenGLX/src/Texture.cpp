#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& pathx) : path(pathx),\
textureID(0), local_Buffer(nullptr), width(0), height(0), Bpp(0)
{
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	std::cout << "Texture id " << this->textureID << std::endl;

	stbi_set_flip_vertically_on_load(1);
	this->local_Buffer = stbi_load(this->path.c_str(), &this->width, &this->height, &this->Bpp, 4);
	if (this->local_Buffer == nullptr)
		std::cout << "NONONONONO" << std::endl;
	else
	{
		int i = 0;
		std::cout << "Width " << this->width << std::endl;
		std::cout << "Height " << this->height << std::endl;
		while (*(this->local_Buffer + i) != NULL)
		{
			std::cout << *(this->local_Buffer + i) << std::endl;
			i++;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->local_Buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (this->local_Buffer)
		stbi_image_free(this->local_Buffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->textureID);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
