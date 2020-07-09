#include <GL/glew.h>
class IndexBuffer
{
	private:
		unsigned int BufferID;
		unsigned int count;
		unsigned int* indexes;
	public:
		IndexBuffer(unsigned int* indexes, unsigned int count);
		~IndexBuffer();
		void Bind() const;
		void UnBind() const;
		unsigned int getCount() const;
};

