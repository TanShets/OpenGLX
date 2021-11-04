#include "Rectangle.h"

Rectangle::Rectangle(float* ref_point, float width1, float height1)
{
	this->Init(ref_point, width, height);
	this->setData();
}

Rectangle::Rectangle(float* ref_point, float width, float height, float* color)
{
	this->Init(ref_point, width, height);
	this->color = color;
	this->setData();
}

Rectangle::Rectangle(float* ref_point, float side)
{
	this->Init(ref_point, side, side);
	this->setData();
}

Rectangle::Rectangle(float* ref_point, float side, float* color)
{
	this->Init(ref_point, side, side);
	this->color = color;
	this->setData();
}

void Rectangle::Init(float* ref_point, float width, float height)
{
	//this->side = 0;
	this->getDimension();
	this->reference_point = ref_point;
	float temp_color[] = { 0.0, 0.0, 0.0, 1.0 };
	this->color = temp_color;
	this->width = width;
	this->height = height;
}

void Rectangle::setData()
{
	this->index = (unsigned int*)this->temp_index;
	Vertex vertexX[] = {
		{
			{this->reference_point[0] - (this->width / 2), this->reference_point[1] - (this->height / 2), 1.0f},\
			{*(this->color), *(this->color + 1), *(this->color + 2), *(this->color + 3)}
		},
		{
			{this->reference_point[0] + (this->width / 2), this->reference_point[1] - (this->height / 2), 1.0f},\
			{*(this->color),* (this->color + 1),* (this->color + 2),* (this->color + 3)}
		},
		{
			{this->reference_point[0] + (this->width / 2), this->reference_point[1] + (this->height / 2), 1.0f},\
			{*(this->color),* (this->color + 1),* (this->color + 2),* (this->color + 3)}
		},
		{
			{this->reference_point[0] - (this->width / 2), this->reference_point[1] + (this->height / 2), 1.0f},\
			{*(this->color),* (this->color + 1),* (this->color + 2),* (this->color + 3)}
		}
	};

	this->vertices = vertexX;
}

const unsigned int* Rectangle::getIndex() const
{
	return this->index;
}
