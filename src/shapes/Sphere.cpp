#include "Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <algorithm>

Sphere::Sphere(float* ref_point, float radius) 
{
	this->no_of_sectors = 18;
	this->no_of_stacks = 36;
	this->basic_init(ref_point, radius);
}

Sphere::Sphere(float* ref_point, float radius, unsigned int no_of_sectors, unsigned int no_of_stacks)
{
	this->no_of_sectors = no_of_sectors;
	this->no_of_stacks = no_of_stacks;
	this->basic_init(ref_point, radius);
}

void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

void Sphere::setOrigin(float* ref_point)
{
	this->reference_point = ref_point;
}

float Sphere::getRadius()
{
	return this->radius;
}

float* Sphere::getOrigin()
{
	return this->reference_point;
}

Vertex* Sphere::getData()
{
	return this->vertices;
}

void Sphere::addToBuffer(VertexBuffer* vb)
{
	unsigned int count = vb->getCount();
	this->makeIndexForVertexBuffer(count);
	vb->addData(vertices, (unsigned int)this->temp_vertices->size());
	vb->indexBuffer->Addto(this->index, (unsigned int)this->temp_index->size());
}

void Sphere::setData()
{
	float sector_angle = (float)360.0 / (float)this->no_of_sectors;
	float stack_angle = (float)180.0 / (float)this->no_of_stacks;
	float xz, x, y, z;
	this->makeVertex(0, this->radius, 0);
	float i, j;
	float phi, theta;
	int count = 0, count2 = 0;
	for (i = 90.0 - stack_angle; i > -90.0; i -= stack_angle)
	{
		phi = M_PI * i / 180;
		y = this->radius * (float)sin(phi);
		xz = this->radius * (float)cos(phi);
		count2++;
		for (j = 0; j < 360.0; j += sector_angle)
		{
			theta = M_PI * j / 180;
			if (i == 90.0 - stack_angle)
				count++;
			x = xz * cos(theta);
			z = xz * sin(theta);
			this->makeVertex(x, y, z);
		}
	}
	if (count != this->no_of_sectors)
		this->no_of_sectors = count;
	this->makeVertex(0, -this->radius, 0);
	this->vertices = &((*this->temp_vertices)[0]);
	unsigned int temp;
	int l, m = (int)this->temp_vertices->size();
	for (l = 1; l <= this->no_of_sectors; l++)
	{
		this->temp_index->push_back(0);
		this->temp_index->push_back(l);
		temp = l == this->no_of_sectors ? 1 : l + 1;
		this->temp_index->push_back(temp);
	}
	std::cout << this->no_of_sectors << std::endl;
	std::cout << (*this->temp_index)[0] << " " << (*this->temp_index)[1] << " " << (*this->temp_index)[2] << std::endl;
	//this->print((*(this->vertices + (*this->temp_index)[0])).position);
	//this->print((*(this->vertices + (*this->temp_index)[1])).position);
	//this->print((*(this->vertices + (*this->temp_index)[2])).position);
	
	for (l = 1; l < m - this->no_of_sectors; l++)
	{
		this->temp_index->push_back(l);
		temp = l % this->no_of_sectors == 1 ? l + 2 * this->no_of_sectors - 1 : l + this->no_of_sectors - 1;
		this->temp_index->push_back(temp);
		this->temp_index->push_back(l + this->no_of_sectors);
		this->temp_index->push_back(l);
		this->temp_index->push_back(l + this->no_of_sectors);
		temp = l % this->no_of_sectors == 0 ? l - this->no_of_sectors + 1 : l + 1;
		this->temp_index->push_back(temp);
	}
	
	for (l = m - this->no_of_sectors - 1; l < m - 1; l++)
	{
		this->temp_index->push_back(l);
		this->temp_index->push_back(m - 1);
		temp = l == m - 2 ? m - this->no_of_sectors - 1 : l + 1;
		this->temp_index->push_back((l + 1) % this->no_of_sectors);
	}
}

void Sphere::makeVertex(float x, float y, float z)
{
	this->temp_vertices->push_back({
		{
			this->reference_point[0] + x,
			this->reference_point[1] + y,
			this->reference_point[2] + z
		},
		{
			(float)(rand() % 10) / 10, (float)(rand() % 10) / 10, 
			(float)(rand() % 10) / 10, (float)(rand() % 10) / 10
		}
	});
}

void Sphere::makeIndexForVertexBuffer(unsigned int count)
{
	this->index = (unsigned int*)calloc(
						(int)this->temp_index->size(), 
						sizeof(unsigned int)
					);
	for (int i = 0; i < (int)this->temp_index->size(); i++)
		this->index[i] = count + (*this->temp_index)[i];
}

void Sphere::print(float* position)
{
	std::cout << "(" << position[0] << "," << position[1] << "," << position[2] << ")";
}

void Sphere::basic_init(float* ref_point, float radius)
{
	this->reference_point = ref_point;
	this->radius = radius;
	this->temp_vertices = new std::vector<Vertex>();
	this->temp_index = new std::vector<unsigned int>();
	this->vertices = nullptr;
	this->setData();
}
