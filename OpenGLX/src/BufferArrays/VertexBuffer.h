#include <GL/glew.h>

class VertexBuffer
{
	private:
		unsigned int BufferID;
		const void* data;
		unsigned int size;
	public:
		VertexBuffer(const void* data, unsigned int size);
		VertexBuffer(unsigned int size);
		~VertexBuffer();
		void Bind();
		void UnBind();
		void update(const void* updated_data, unsigned int new_size);
};

