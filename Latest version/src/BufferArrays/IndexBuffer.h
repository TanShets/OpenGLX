#include <GL/glew.h>
#include <vector>
class IndexBuffer
{
	private:
		unsigned int BufferID;
		unsigned int count;
		unsigned int* indexes;
		std::vector<unsigned int> index;
	public:
		IndexBuffer(unsigned int* indexes, unsigned int count);
		IndexBuffer();
		~IndexBuffer();
		void Bind() const;
		void UnBind() const;
		unsigned int getCount() const;
		void Addto(unsigned int* new_indexes, unsigned int count);
};

