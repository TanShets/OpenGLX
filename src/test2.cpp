#include "Renderer.h"
#include "Texture.h"
#include <GLFW/glfw3.h>
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>

int main() {
	//names shader = ParseShader("shaders/vertex.shader");
	std::string image_path = "Picture1.png";
	glm::mat4 proj = glm::ortho(-0.9f, 0.9f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.5, 0));
	glm::mat4 mvp = proj * view;
	//const char* ty = anon.c_str();
	GLFWwindow* window;
	if (glfwInit() == -1)
		return -1;
	window = glfwCreateWindow(600, 600, "The Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	float positions[] = {
		-0.9f, -0.9f, 0.0f, 0.0f,
		0.9f, -0.9f, 1.0f, 0.0f,
		0.9f, 0.9f, 1.0f, 1.0f,
		-0.9f, 0.9f, 0.0f, 1.0f
	};

	float positions2[] = {
		-0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
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
	VertexBuffer buffer((const void*)positions, 16 * sizeof(float));
	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(2);
	vbLayout.Push<float>(2);
	VertexBuffer buffer2((const void*)positions2, 16 * sizeof(float));
	VertexBufferLayout vbLayout2;
	vbLayout2.Push<float>(2);
	vbLayout2.Push<float>(2);
	//vbLayout.Push<float>(2);
	//vbLayout.Push<float>(2);
	//VertexBufferElement element = vbLayout.getElements()[0];
	IndexBuffer indexBuffer(indices, 6);
	//glGenBuffers(1, &indexBuffer);
	//glBindVertexArray(vertexArray);
	//vertexArray.AddBuffer(buffer, vbLayout);
	//vertexArray.UnBind();
	vertexArray.Bind();
	buffer.Bind();
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
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
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	/*
	glEnableVertexAttribArray(0);
	//unsigned int offset = 0;
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	*/
	//glVertexAttribPointer(0, element.count, element.type, element.normalized, vbLayout.getStride(), (const void*)offset);
	//texture.Bind(1);
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
		positions2[0] += increment;
		positions2[4] += increment;
		positions2[8] += increment;
		positions2[12] += increment;
		buffer2.update(positions2, 16 * sizeof(float));
		//vertexArray.Bind();
		//indexBuffer.Bind();
		colors[0] = (GLfloat)((float)(rand() % 10) / 10);
		colors[1] = (GLfloat)((float)(rand() % 10) / 10);
		colors[2] = (GLfloat)((float)(rand() % 10) / 10);
		colors[3] = 1.0f;
		shader.uniformChange('M', 4, (void*)&mvp, "u_MVP");
		shader.uniformChange('i', 1, (void*)&anony, "u_Texture");
		//shader.uniformChange('f', 1, &xx, "diss");
		shader.uniformChange('f', 4, colors, "u_Color");
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