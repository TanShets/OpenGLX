#include "IndexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer(unsigned int* indexes, unsigned int count)
{
	this->indexes = indexes;
	this->count = count;
	for (int i = 0; i < this->count; i++)
	{
		this->index.push_back(indexes[i]);
	}
	glGenBuffers(1, &BufferID);
	//this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indexes, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &this->BufferID);
	this->count = 0;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), (unsigned int*)&this->index[0], GL_STATIC_DRAW);
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

void IndexBuffer::Addto(unsigned int* new_indexes, unsigned int new_count)
{
	for (int i = 0; i < new_count; i++)
		this->index.push_back(new_indexes[i]);
	this->count += new_count;
	this->Bind();
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), new_count * sizeof(unsigned int), new_indexes);
}
