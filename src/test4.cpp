//#include "Renderer.h"
#include "../OpenGLX.h"
#include <iostream>
#include <unordered_map>
//#include "Texture.h"
//#include "shapes/shapes.h"
//#include <GLFW/glfw3.h>

std::unordered_map<float, std::unordered_map<float, Cube*>> grid;
float color[] = { ((float)(rand() % 10) / 10), ((float)(rand() % 10) / 10), ((float)(rand() % 10) / 10), ((float)(rand() % 10) / 10) };

void makeMatrix(Events* event, VertexBuffer* buffer)
{
	//std::vector<Cube*> answer;
	buffer->clear();
	float* position = event->getPosition();
	float x_low = position[0] - 25.0f, x_high = position[0] + 25.0f;
	float z_low = position[2] - 25.0f, z_high = position[2] + 25.0f;
	float i, j;
	float og[3] = { 0.0f, -0.5f, 0.0f };
	for (i = x_low; i < x_high; i += 0.5f)
	{
		if (grid.find(i) == grid.end())
		{
			//std::unordered_map<float, Cube*> new_map;
			grid[i] = std::unordered_map<float, Cube*>();
		}

		for (j = z_low; j < z_high; j += 0.5f)
		{
			if (grid[i].find(j) == grid[i].end())
			{
				og[0] = i;
				og[2] = j;
				grid[i][j] = new Cube(og, 0.5, color);
			}

			grid[i][j]->AddtoBuffer(buffer);
			//answer.push_back(grid[i][j]);
		}
	}
}

double currentPos[2] = { 0, 0 };
double originalPos[2] = { 0, 0 };
float factor = 0.05f;
void rotationx(GLFWwindow* window, glm::mat4* rot)
{
	double x, y;
	glm::mat4 result;
	glfwGetCursorPos(window, &x, &y);
	if (currentPos[0] == x && currentPos[1] == y)
		return;
	else if(currentPos[0] == x)
		result = glm::rotate(glm::mat4(1.0), glm::radians(factor * (float)(y - currentPos[1])), glm::vec3(1.0f, 0.0f, 0.0f));
	else if(currentPos[1] == y)
		result = glm::rotate(glm::mat4(1.0), glm::radians(factor * (float)(x - currentPos[0])), glm::vec3(0.0f, 1.0f, 0.0f));
	else
	{
		glm::mat4 mat_x = glm::rotate(glm::mat4(1.0), glm::radians(factor * (float)(x - currentPos[0])), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mat_y = glm::rotate(glm::mat4(1.0), glm::radians(factor * (float)(y - currentPos[1])), glm::vec3(1.0f, 0.0f, 0.0f));
		result = mat_x * mat_y;
	}
	//currentPos[0] = x;
	//currentPos[1] = y;
	if((glm::radians(factor * (float)(x - currentPos[0])) >= glm::radians(30.0f)) || (glm::radians(factor * (float)(y - currentPos[1])) >= glm::radians(30.0f))){
		currentPos[0] = x;
		currentPos[1] = y;
	}
	*rot = result;
}

void print_perspective(const glm::mat4& val)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << val[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	//std::cout << (double)glm::radians(180.0f) << std::endl;
	//names shader = ParseShader("shaders/vertex.shader");
	//		std::string image_path = "Picture1.png";
	float origin[] = { 0.0f, -0.5f, 0.0f };
	float originx[] = { 0.0f, 5.0f, 0.0f };
	double pi = acos(-1.0);
	//std::cout << "pi " << (float)pi / 3 << std::endl;
	glm::mat4 proj = glm::perspective((float)(2 * pi / 3), (float)600 / (float)600, (float)0.2f, (float)50.0f);
		//glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -50.0f, 50.0f);
	//glm::mat4 model = glm::perspective((float)pi / 3, (float)600 / (float)600, (float)-1.0f, (float)1.0f);
	glm::mat4 rot = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 view(1.0f);
	glm::mat4 mvp = proj * view * rot;// *model;
	print_perspective(proj);
	print_perspective(view);
	//print_perspective(model);
	print_perspective(mvp);
	//glm::mat4 model;
	float z = -0.1f;
	//const char* ty = anon.c_str();
	GLFWwindow* window;
	if (glfwInit() == -1)
		return -1;
	window = glfwCreateWindow(800, 800, "The Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//double x, y;
	glfwGetCursorPos(window, &originalPos[0], &originalPos[1]);
	currentPos[0] = originalPos[0];
	currentPos[1] = originalPos[1];
	Vertex positions2[] = {
		{{-0.5f, 0.0f, 0.0f}, {0.8, 1.0, 0.3, 1.0}},//, {0.0f, 0.0f}},
		{{0.5f, 0.0f, -0.5f }, {0.7, 0.7, 1.0, 1.0}},//, {1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.2f }, {1.0, 0.1, 1.0, 1.0}},//, { 1.0f, 1.0f }},
		{{-0.5f, 0.5f, 0.6f}, {0.4, 1.0, 0.2, 1.0}},//, {0.0f, 1.0f}}
	};
	/*
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		//4, 5, 6,
		//6, 7, 4
	};
	*/
	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2,
		4, 5, 6,
		5, 7, 6
	};
	//unsigned int /*buffer, indexBuffer, */vertexArray;
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		return -1;
	//IndexBuffer id;
	float gap = 0.5f;
	//Cube** cubes = (Cube**)malloc(10000 * sizeof(Cube*));
	std::vector<Cube*> cubes;
	Cube* temp;
	//Cube** cubes2 = (Cube**)malloc(10000 * sizeof(Cube*));
	int fact, total;
	float side = 0.5;
	for (fact = 0; fact < 10; fact++)
	{
		origin[0] = -25.0f;
		//originx[0] = -25.0f;
		for (int fact2 = 0; fact2 < 10; fact2++)
		{
			//cubes[100 * fact + fact2] = new Cube(origin, 0.5, color);
			//total = (rand() % 10) + 1;
			//origin[1] = -0.5f;
			//std::cout << "Rando " << total << std::endl;
			origin[1] = (rand() % 100) * 0.1;
			side = (rand() % 100) * 0.01;
			temp = new Cube(origin, side, color);
			cubes.push_back(temp);
			//cubes2[100 * fact + fact2] = new Cube(originx, 0.5, color);
			origin[0] += gap;
			//originx[0] += gap;
		}
		origin[2] += gap;
		//originx[2] -= gap;
	}
	//			Cube cube(origin, 0.5, color);
	float origin2[3] = { 0.0f, 0.0f, 0.5f };
	//			Cube cube2(origin2, 0.5, color);
	//float* v = cube.getOrigin();
	//std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
	//			Vertex* data = (Vertex*)(cube.getData());
	Renderer renderer;
	Shaders shader;
	//			data = (Vertex*)(cube.getData());
	VertexArray vertexArray;
	VertexArray vertexArray2;
	//glGenVertexArrays(1, &vertexArray);
	//glGenBuffers(1, &buffer);
	//	VertexBuffer buffer((const void*)positions, 8 * sizeof(Vertex));
	//			VertexBuffer buffer(data, 8);
	VertexBuffer buffer;
	//			cube.AddtoBuffer(&buffer);
	//			cube2.AddtoBuffer(&buffer);
	//			buffer.sizeUpBuffer(10000);
	VertexBuffer buffer2;
	std::cout << "Size " << cubes.size() << std::endl;
	/*
	for (fact = 0; fact < (int)cubes.size(); fact++)
	{
		//std::cout << "Index " << fact << std::endl;
		cubes[fact]->AddtoBuffer(&buffer);
		//std::cout << "Finish " << fact << std::endl;
		//cubes2[fact]->AddtoBuffer(&buffer2);
	}
	*/
	origin[0] = 0.0f, origin[1] = 0.0f, origin[2] = 0.0f;
	Sphere* sphere = new Sphere(origin, 10, 90, 180);
	sphere->addToBuffer(&buffer);
	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(3);
	vbLayout.Push<float>(4);
	//VertexBuffer buffer2(positions2, 4);
	VertexBufferLayout vbLayout2;
	vbLayout2.Push<float>(3);
	vbLayout2.Push<float>(4);
	//	IndexBuffer indexBuffer(indices, 12);
	//			IndexBuffer indexBuffer((unsigned int*)cube.getIndex(), 36);
	vertexArray.Bind();
	buffer.Bind();
	buffer.indexBuffer->Bind();
	//			indexBuffer.Bind();
	std::cout << "Start Array" << std::endl;
	vertexArray.AddBuffer(buffer, vbLayout);
	std::cout << "End Array" << std::endl;
	//			indexBuffer.UnBind();
	buffer.UnBind();
	vertexArray.UnBind();
	buffer.indexBuffer->UnBind();

	//			vertexArray2.Bind();
	//			buffer2.Bind();
	//			buffer2.indexBuffer->Bind();
	//			indexBuffer.Bind();
	//			vertexArray2.AddBuffer(buffer2, vbLayout2);
	//			indexBuffer.UnBind();
	//			buffer2.UnBind();
	//			vertexArray2.UnBind();
	//			buffer2.indexBuffer->UnBind();
	shader.BindShader();
	GLfloat colors[4];
	GLfloat xx = 0;
	GLint anony = 0;
	glm::vec4 anon;
	float increment = 0.005;
	glm::vec4 useMe(0.0f, 0.0f, 0.0f, 1.0f);
	Events event(window, originalPos, (float)0.5);
	//std::vector<Cube*> Cubes;
	//glDepthMask(GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	//glEnableFunc(GL_LESS);
	std::cout << "Start Loop" << std::endl;
	while (!glfwWindowShouldClose(window)) {
		glfwSwapInterval(5);
		//Cubes = makeMatrix(&event);
		//glClear(GL_COLOR_BUFFER_BIT);
		renderer.Clear();
		//			buffer.update(data, 8 * sizeof(Vertex));
		//buffer2.update(positions2, 4 * sizeof(Vertex));
		z += increment;
		//rot = rotationx(window);
		//	rotationx(window, &rot);
		event.update(&view);
		mvp = proj * rot * view;// *model;
		//			useMe = glm::vec4(data[0].position[0], data[0].position[1], data[0].position[2], 1.0f);
		//			useMe = mvp * useMe;
		//			std::cout << "VertexX: " << data[0].position[0] << " " << useMe[1] << " " << useMe[2] << std::endl;
		//vertexArray.Bind();
		//indexBuffer.Bind();
		shader.uniformChange('M', 4, (void*)&proj, "proj");
		shader.uniformChange('M', 4, (void*)&view, "view");
		//		std::cout << "Position of origin: " << tempx[0] << " " << tempx[1] << " " << tempx[2] << std::endl;
		shader.uniformChange('M', 4, (void*)&mvp, "u_MVP");
		renderer.Draw(&vertexArray, buffer.indexBuffer, shader);
		//glDepthFunc(GL_NEVER);
		//renderer.Draw(&vertexArray2, buffer2.indexBuffer, shader);
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