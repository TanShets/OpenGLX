#include "Rectangle.h"
class Cube: Shape
{
	private:
		float side;
		float* color;
		unsigned int indexPos;
		unsigned int* temp_index;
		unsigned int* index;
		//const unsigned int offset = 8;
		const unsigned int init_index[36] = {
			0, 1, 3,
			3, 2, 0,
			0, 4, 1,
			1, 4, 5,
			0, 4, 2,
			4, 6, 2,
			1, 5, 3,
			5, 7, 3,
			4, 5, 7,
			7, 6, 4,
			6, 3, 2,
			3, 6, 7,
		};
	public:
		Cube(float* ref_point, float side);
		Cube(float* ref_point, float side, float* color);
		void setData();
		void setVertex(int index, float move_x, float move_y, float move_z);
		const unsigned int* getIndex() const;
		Vertex* getData();
		float* getOrigin();
		Vertex createVertex(float move_x, float move_y, float move_z);
		unsigned int* getIndex_for_Buffer(unsigned int* curr_Offset);
		void AddtoBuffer(VertexBuffer* vb);
};

