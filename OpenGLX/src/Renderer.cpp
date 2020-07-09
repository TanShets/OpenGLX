#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray* vertexArray, IndexBuffer* indexBuffer, const Shaders& shader) const
{
	shader.BindShader();
	vertexArray->Bind();
	indexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
}
