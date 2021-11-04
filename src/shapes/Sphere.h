#include "Shape.h"
#include <vector>

class Sphere : public Shape
{
	private:
		unsigned int* index;
		float radius;
		unsigned int no_of_sectors, no_of_stacks;
		std::vector<Vertex>* temp_vertices;
		std::vector<unsigned int>* temp_index;

		void setData();
		void basic_init(float* ref_point, float radius);
		void makeVertex(float x, float y, float z);
		void makeIndexForVertexBuffer(unsigned int count);
		void print(float* position);
	public:
		Sphere(float* ref_point, float radius);
		Sphere(float* ref_point, float radius, unsigned int no_of_sectors, unsigned int no_of_stacks);
		void setRadius(float radius);
		void setOrigin(float* ref_point);
		float getRadius();
		float* getOrigin();
		Vertex* getData();
		void addToBuffer(VertexBuffer* vb);
};

