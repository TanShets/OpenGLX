#include <vector>
#include <GL/glew.h>

typedef struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	static unsigned int getSize(unsigned int typex)
	{
		switch (typex) {
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
		default:
			return 0;
		}
	}
}VertexBufferElement;

class VertexBufferLayout
{
	private:
		std::vector<VertexBufferElement> elements;
		unsigned int stride;
	public:
		VertexBufferLayout();
		~VertexBufferLayout();

		std::vector<VertexBufferElement> getElements() const;

		unsigned int getStride() const;

		template<class T>
		void Push(unsigned int count);

		template<>
		void Push<float>(unsigned int count);

		template<>
		void Push<unsigned int>(unsigned int count);

		template<>
		void Push<unsigned char>(unsigned int count);
};

template<class T>
inline void VertexBufferLayout::Push(unsigned int count) {
	return;
}

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
	this->elements.push_back({ GL_FLOAT, count, GL_FALSE });
	this->stride += count * sizeof(GLfloat);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	this->elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	this->stride += count * sizeof(GLuint);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	this->elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	this->stride += count * sizeof(GLubyte);
}