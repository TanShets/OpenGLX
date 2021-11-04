#pragma once
#include <VertexArray.h>
class Shape
{
	private:
	public:
		int no_of_vertices, dimension;
		Vertex* vertices;
		unsigned int* index;
		float* reference_point; // Basically giving us some idea about coordinates.
		float* color;
		Shape();
		Shape(float* ref_point);
		void setData();
		Vertex* getData() const;
		void getDimension();
};