#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(Vertex* data, unsigned int no_of_vertices)
{
	this->data = data;
	//std::cout << "Capacity " << sizeof(data) << " " << sizeof(Vertex) << std::endl;
	int i = 0;
	for (i = 0; i < no_of_vertices; i++)
	{
		this->data_base.push_back(data[i]);
	}
	//float* temp = (float*)data;
	//std::cout << "Yes" << std::endl;
	this->size = no_of_vertices * sizeof(Vertex);
	glGenBuffers(1, &BufferID);
	this->indexBuffer = new IndexBuffer();
	//this->Bind();
	//this->UnBind();
}

VertexBuffer::VertexBuffer()
{
	this->size = 0;
	this->data = nullptr;
	glGenBuffers(1, &this->BufferID);
	this->indexBuffer = new IndexBuffer();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &BufferID);
	this->data_base.clear();
	//delete this->data;
	std::cout << "Vertex" << std::endl;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->BufferID);
	//Vertex* temp = (Vertex*)data;
	//std::cout << ((Vertex)(this->data[0])).position[0] << std::endl;
	glBufferData(GL_ARRAY_BUFFER, this->size, (Vertex*)&this->data_base[0], GL_DYNAMIC_DRAW);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::update(Vertex* updated_data, unsigned int new_size)
{
	this->data = updated_data;
	this->size = new_size;
	this->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, new_size, data);
	//glBufferSubData()
}

void VertexBuffer::update()
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->size, (Vertex*)&this->data_base);
}

void VertexBuffer::addData(Vertex* new_data, unsigned int no_of_vertices)
{
	for (int i = 0; i < no_of_vertices; i++)
		this->data_base.push_back(new_data[i]);
	//std::cout << "addData check" << std::endl;
	//glBufferSubData(GL_ARRAY_BUFFER, this->size, no_of_vertices * sizeof(Vertex), new_data);
	this->size += no_of_vertices * sizeof(Vertex);
	//this->Bind();
	//glBufferData(GL_ARRAY_BUFFER, no_of_vertices * sizeof(Vertex), new_data, GL_DYNAMIC_DRAW);
}

unsigned int VertexBuffer::getCount()
{
	return this->size / sizeof(Vertex);
}

Vertex* VertexBuffer::getData() const
{
	return (Vertex*)&this->data_base[0];
}

void VertexBuffer::clear()
{
	this->data_base.clear();
}

void VertexBuffer::sizeUpBuffer(unsigned int count)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
}
