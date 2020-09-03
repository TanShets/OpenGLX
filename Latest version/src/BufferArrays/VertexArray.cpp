#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->vertexBufferID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->vertexBufferID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(this->vertexBufferID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layouts) const
{
	//this->Bind();
	//vertexBuffer.Bind();
	const auto& elements = layouts.getElements();
	unsigned int offset = 0;
	const Vertex* data = (const Vertex*)vertexBuffer.getData();
	//std::cout << "size " << elements.size() << std::endl;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layouts.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSize(element.type);
		//offset = offsetof(Vertex, position);
	}
}
