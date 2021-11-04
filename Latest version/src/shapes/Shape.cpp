#include "Shape.h"

Shape::Shape()
{
	this->reference_point = nullptr;
	this->vertices = nullptr;
	this->no_of_vertices = 0;
	this->color = nullptr;
	this->dimension = 0;
}

Shape::Shape(float* ref_point)
{
	this->reference_point = ref_point;
	this->vertices = nullptr;
	this->no_of_vertices = 0;
	this->color = nullptr;
	this->dimension = 0;
}

void Shape::setData()
{
	return;
}

Vertex* Shape::getData() const
{
	return this->vertices;
}

void Shape::getDimension()
{
	int i = 0;
	while (this->reference_point + i != nullptr)
		i++;
	this->dimension = i;
}
