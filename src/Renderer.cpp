#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(VertexArray* vertexArray, IndexBuffer* indexBuffer, const Shaders& shader) const
{
	shader.BindShader();
	vertexArray->Bind();
	if (indexBuffer != nullptr)
	{
		indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		std::cout << "Drawing" << std::endl;
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
