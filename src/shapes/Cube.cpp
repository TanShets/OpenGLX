#include "Cube.h"
#include <iostream>

Cube::Cube(float* ref_point, float side)
{
	this->reference_point = ref_point;
	this->side = side;
	float temp_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	this->color = temp_color;
	this->setData();
}

Cube::Cube(float* ref_point, float side, float* color)
{
	this->reference_point = ref_point;
	this->side = side;
	this->color = color;
	this->setData();
}

void Cube::setData()
{
	this->index = (unsigned int*)init_index;
	this->no_of_vertices = 8;
	this->temp_index = (unsigned int*)malloc(36 * sizeof(unsigned int));
	this->vertices = (Vertex*)malloc(8 * sizeof(Vertex));
	/*
	Vertex new_vertices[36] = {
		createVertex(-1, -1, -1), createVertex(1, -1, -1), createVertex(1, 1, -1),
		createVertex(-1, -1, -1), createVertex(1, 1, -1), createVertex(-1, 1, -1),
		createVertex(-1, -1, -1), createVertex(1, -1, 1), createVertex(-1, 1, 1),
		createVertex(-1, -1, -1), createVertex(-1, 1, 1), createVertex(-1, 1, -1),
		createVertex(-1, -1, -1), createVertex(-1, -1, 1), createVertex(1, -1, 1),
		createVertex(-1, -1, -1), createVertex(1, -1, 1), createVertex(1, -1, -1),
		createVertex(1, 1, 1), createVertex(-1, 1, -1), createVertex(-1, 1, 1),
		createVertex(1, 1, 1), createVertex(1, 1, -1), createVertex(-1, 1, -1),
		createVertex(1, 1, 1), createVertex(1, -1, 1), createVertex(1, -1, -1),
		createVertex(1, 1, 1), createVertex(1, -1, -1), createVertex(1, 1, -1),
		createVertex(1, 1, 1), createVertex(-1, 1, 1), createVertex(-1, -1, 1),
		createVertex(1, 1, 1), createVertex(-1, -1, 1), createVertex(1, -1, 1)
	};
	this->vertices = (Vertex*)new_vertices;
	*/
	float val1 = 1, val2 = 1, val3 = 1;
	int count = 0;
	for (int i = 0; i < 2 && count < 8; i++)
	{
		val1 *= -1;
		for (int j = 0; j < 2; j++) {
			val2 *= -1;
			for (int k = 0; k < 2; k++)
			{
				val3 *= -1;
				this->setVertex(count, val3, val2, val1);
				count++;
			}
		}
	}
}

void Cube::setVertex(int index, float move_x, float move_y, float move_z)
{
	*(this->vertices + index) = {
		{
			this->reference_point[0] + move_x * (this->side / 2), 
			this->reference_point[1] + move_y * (this->side / 2),
			this->reference_point[2] + move_z * (this->side / 2)
		},
		{
			//this->color[0], this->color[1], this->color[2], this->color[3]
			(float)(rand() % 10) / 10, (float)(rand() % 10) / 10, (float)(rand() % 10) / 10, \
			(float)(rand() % 10) / 10
		}
	};
}

const unsigned int* Cube::getIndex() const
{
	return this->index;
}

Vertex* Cube::getData()
{
	return Shape::getData();
}

float* Cube::getOrigin()
{
	return Shape::reference_point;
}

Vertex Cube::createVertex(float move_x, float move_y, float move_z)
{
	Vertex temp = {
		{
			this->reference_point[0] + move_x * (this->side / 2),
			this->reference_point[1] + move_y * (this->side / 2),
			this->reference_point[2] + move_z * (this->side / 2)
		},
		{
			(float)(rand() % 10) / 10, (float)(rand() % 10) / 10, (float)(rand() % 10) / 10, \
			(float)(rand() % 10) / 10
		}
	};
	return temp;
}

unsigned int* Cube::getIndex_for_Buffer(unsigned int* curr_Offset)
{
	unsigned int shift = *curr_Offset;
	for (int i = 0; i < 36; i++)
	{
		this->index[i] = this->init_index[i] + shift;
	}
	*curr_Offset += this->no_of_vertices;
	return this->index;
}

void Cube::AddtoBuffer(VertexBuffer* vb)
{
	unsigned int count = vb->getCount();
	//std::cout << "Vertex " << vertices[0].position[0] << " " << no_of_vertices << std::endl;
	vb->addData(vertices, no_of_vertices);
	vb->indexBuffer->Addto(this->getIndex_for_Buffer(&count), 36);
}
