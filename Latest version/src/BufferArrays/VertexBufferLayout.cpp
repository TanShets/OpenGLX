#include "VertexBufferLayout.h"
#include <iostream>

VertexBufferLayout::VertexBufferLayout()
{
	this->stride = 0;
	std::cout << "Yep broken" << std::endl;
}

VertexBufferLayout::~VertexBufferLayout()
{
	this->elements.clear();
	this->stride = 0;
}

std::vector<VertexBufferElement> VertexBufferLayout::getElements() const
{
	return this->elements;
}

unsigned int VertexBufferLayout::getStride() const
{
	return this->stride;
}