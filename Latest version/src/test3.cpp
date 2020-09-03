#include "Renderer.h"
#include "Texture.h"
#include <GLFW/glfw3.h>

int main() {
	//names shader = ParseShader("shaders/vertex.shader");
	std::string image_path = "Picture1.png";
	glm::mat4 proj = glm::ortho(-0.9f, 0.9f, -1.0f, 1.0f, -1.0f, 1.0f);
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0));
	glm::mat4 mvp = proj;// *view;
	float z = -0.1f;
	//const char* ty = anon.c_str();
	GLFWwindow* window;
	if (glfwInit() == -1)
		return -1;
	window = glfwCreateWindow(600, 600, "The Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	Vertex positions[] = {
		{{-0.9f, -0.9f, 0.0f}, {0.5, 0.1, 0.7, 1.0}, {0.0f, 0.0f}},
		{ {0.9f, -0.9f, 1.0f}, {0.1, 0.5, 1.0, 1.0}, {1.0f, 0.0f} },
		{{0.9f, 0.9f, 0.3f}, {1.0, 0.7, 1.0, 1.0}, {1.0f, 1.0f}},
		{{-0.9f, 0.9f, 0.6f}, {1.0, 1.0, 0.5, 1.0}, {0.0f, 1.0f}},
		{{-0.5f, 0.0f, 0.7f}, {0.1, 1.0, 0.7, 1.0}, {0.0f, 0.0f}},
		{{0.5f, 0.0f, -0.2f }, {1.0, 1.0, 1.0, 1.0}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.1f }, {0.1, 0.5, 0.7, 1.0}, { 1.0f, 1.0f }},
		{{-0.5f, 0.5f, -0.5f }, {0.7, 1.0, 0.1, 1.0}, {0.0f, 1.0f}}
	};

	Vertex positions2[] = {
		{{-0.5f, 0.0f, 0.0f}, {0.8, 1.0, 0.3, 1.0}, {0.0f, 0.0f}},
		{{0.5f, 0.0f, -0.5f }, {0.7, 0.7, 1.0, 1.0}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.2f }, {1.0, 0.1, 1.0, 1.0}, { 1.0f, 1.0f }},
		{{-0.5f, 0.5f, 0.6f}, {0.4, 1.0, 0.2, 1.0}, {0.0f, 1.0f}}
	};
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4
	};
	//unsigned int /*buffer, indexBuffer, */vertexArray;
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		return -1;
	Renderer renderer;
	Shaders shader;
	VertexArray vertexArray;
	VertexArray vertexArray2;
	//glGenVertexArrays(1, &vertexArray);
	//glGenBuffers(1, &buffer);
	VertexBuffer buffer((const void*)positions, 8 * sizeof(Vertex));
	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(3);
	vbLayout.Push<float>(4);
	vbLayout.Push<float>(2);
	VertexBuffer buffer2((const void*)positions2, 4 * sizeof(Vertex));
	VertexBufferLayout vbLayout2;
	vbLayout2.Push<float>(3);
	vbLayout2.Push<float>(4);
	vbLayout2.Push<float>(2);
	IndexBuffer indexBuffer(indices, 12);
	vertexArray.Bind();
	buffer.Bind();
	indexBuffer.Bind();
	vertexArray.AddBuffer(buffer, vbLayout);
	indexBuffer.UnBind();
	vertexArray.UnBind();

	vertexArray2.Bind();
	buffer2.Bind();
	indexBuffer.Bind();
	vertexArray2.AddBuffer(buffer2, vbLayout2);
	indexBuffer.UnBind();
	vertexArray2.UnBind();
	shader.BindShader();
	Texture texture("Picture1.png");
	texture.Bind();
	//GLint u_texture = 0;
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	GLfloat colors[4];
	GLfloat xx = 0;
	GLint anony = 0;
	float increment = 0.005;
	while (!glfwWindowShouldClose(window)) {
		glfwSwapInterval(5);
		//glClear(GL_COLOR_BUFFER_BIT);
		renderer.Clear();
		positions2[0].position[0] += increment;
		positions2[1].position[0] += increment;
		positions2[2].position[0] -= increment;
		positions2[3].position[0] -= increment;
		positions2[0].position[2] += increment;
		positions2[1].position[2] += increment;
		positions2[2].position[2] -= increment;
		positions2[3].position[2] -= increment;
		buffer2.update(positions2, 4 * sizeof(Vertex));
		z += increment;
		//view = glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 1.0, z));
		mvp = proj;// *view;
		//vertexArray.Bind();
		//indexBuffer.Bind();
		colors[0] = (GLfloat)((float)(rand() % 10) / 10);
		colors[1] = (GLfloat)((float)(rand() % 10) / 10);
		colors[2] = (GLfloat)((float)(rand() % 10) / 10);
		colors[3] = 1.0f;
		shader.uniformChange('M', 4, (void*)&mvp, "u_MVP");
		//	shader.uniformChange('i', 1, (void*)&anony, "u_Texture");
		//shader.uniformChange('ffff', 1, &xx, "diss");
		//shader.uniformChange('f', 4, colors, "u_Color");
		renderer.Draw(&vertexArray, &indexBuffer, shader);
		renderer.Draw(&vertexArray2, &indexBuffer, shader);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glDeleteProgram(program);
	//glDisable(GL_BLEND);
	shader.deleteShader();
	glfwTerminate();
	return 0;
}

/*
	Now able to render textures, still w/o blending.
*/