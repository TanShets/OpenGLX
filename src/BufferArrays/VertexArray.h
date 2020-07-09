#include <GL/glew.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

class VertexArray
{
	private:
		unsigned int vertexBufferID;
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void UnBind() const;
		void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layouts) const;
};

