#include <VertexArray.h>
#include <IndexBuffer.h>
#include <..\shaders\Shaders.h>

class Renderer
{
	public:
		Renderer();
		void Clear() const;
		void Draw(VertexArray* vertexArray, IndexBuffer* indexBuffer, const Shaders& shader) const;
};

