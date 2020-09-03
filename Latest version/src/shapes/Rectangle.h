#include "Shape.h"

class Rectangle: Shape
{
	private:
		float width, height;
		const unsigned int temp_index[6] = {
			0, 1, 2,
			2, 3, 0
		};
		//float* color;
	public:
		Rectangle(float* ref_point, float width, float height);
		Rectangle(float* ref_point, float width, float height, float* color);
		Rectangle(float* ref_point, float side);
		Rectangle(float* ref_point, float side, float* color);
		void Init(float* ref_point, float width, float height);
		void setData();
		const unsigned int* getIndex() const;
		//void setVertex(int index, float x, float y);
};

/*
Reference point is the exact centre in this case.
*/
