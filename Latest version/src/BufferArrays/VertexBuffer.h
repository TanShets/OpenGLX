#include <GL/glew.h>
#include <IndexBuffer.h>
#include <vector>

typedef struct vertex
{
	float position[3], color[4];// , texCoords[2];
}Vertex;

class VertexBuffer
{
	private:
		unsigned int BufferID;
		std::vector<Vertex> data_base;
		Vertex* data;
		unsigned int size;
		//unsigned int count;
	public:
		IndexBuffer* indexBuffer;
		VertexBuffer(Vertex* data, unsigned int size);
		VertexBuffer();
		~VertexBuffer();
		void Bind();
		void UnBind();
		void update(Vertex* updated_data, unsigned int new_size);
		void update();
		void addData(Vertex* new_data, unsigned int no_of_vertices);
		//void addData(Vertex* new_data, unsigned int no_of_vertices);
		unsigned int getCount();
		Vertex* getData() const;
		void clear();
		void sizeUpBuffer(unsigned int count);
};

