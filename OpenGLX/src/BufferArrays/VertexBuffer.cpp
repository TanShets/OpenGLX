#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	this->data = data;
	float* temp = (float*)data;
	std::cout << "Yes" << std::endl;
	this->size = size;
	glGenBuffers(1, &BufferID);
	//this->Bind();
	//this->UnBind();
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	this->size = size;
	this->data = nullptr;
	glGenBuffers(1, &this->BufferID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &BufferID);
	std::cout << "Vertex" << std::endl;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->BufferID);
	glBufferData(GL_ARRAY_BUFFER, this->size, this->data, GL_STATIC_DRAW);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::update(const void* updated_data, unsigned int new_size)
{
	this->data = updated_data;
	this->size = new_size;
	this->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, new_size, data);
}
