#pragma once
#include <..\shapes\shapes.h>
#include <..\shaders\Shaders.h>

class Renderer
{
	public:
		Renderer();
		void Clear() const;
		void Draw(VertexArray* vertexArray, IndexBuffer* indexBuffer, const Shaders& shader) const;
};

