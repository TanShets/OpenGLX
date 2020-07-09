#include "IndexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer(unsigned int* indexes, unsigned int count)
{
	this->indexes = indexes;
	this->count = count;
	glGenBuffers(1, &BufferID);
	//this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indexes, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), this->indexes, GL_STATIC_DRAW);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	std::cout << "Index" << std::endl;
}

unsigned int IndexBuffer::getCount() const
{
	return this->count;
}
