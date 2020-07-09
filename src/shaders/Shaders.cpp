#include "Shaders.h"

void Shaders::ParseShader()
{
	std::string vertexShader, fragmentShader;
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	//std::cout << path << std::endl;
	std::ifstream stream(Shaders::path);
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;
	//std::cout << (int)type << std::endl;
	int count;
	while (std::getline(stream, line))
	{
		count = 0;
		if (line.find("#shader") != std::string::npos)
		{
			//std::cout << 1 << std::endl;
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}
	//std::cout << ss[0].str() << std::endl;
	//std::cout << ss[1].str() << std::endl;
	this->source_codes.vertexShader = ss[0].str();
	this->source_codes.fragmentShader = ss[1].str();
}

unsigned int Shaders::compileShader(unsigned int type, const std::string& source_code)
{
	unsigned int new_id = glCreateShader(type);
	const char* src = source_code.c_str();
	glShaderSource(new_id, 1, &src, nullptr);
	glCompileShader(new_id);
	return new_id;
}

void Shaders::createShader()
{
	unsigned int program = glCreateProgram();
	unsigned int vertex = compileShader(GL_VERTEX_SHADER, source_codes.vertexShader);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, source_codes.fragmentShader);
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	this->Shader_id = program;
}

Shaders::Shaders()
{
	//Shaders::path = "vertex.shader";
	this->ParseShader();
	this->createShader();
	std::cout << "New ID " << this->Shader_id << std::endl;
}

void Shaders::deleteShader() const {
	glDeleteProgram(this->Shader_id);
}

Shaders::~Shaders() {
	this->deleteShader();
}

void Shaders::BindShader() const {
	glUseProgram(this->Shader_id);
}

int Shaders::getLocation(const std::string& uniform_name)
{
	//std::cout << uniform_name << std::endl;
	const char* temp = uniform_name.c_str();
	int location = glGetUniformLocation(this->Shader_id, temp);
	std::cout << " ID: " << this->Shader_id << std::endl;
	std::cout << uniform_name << " Location: " << location << std::endl;
	//char* temp = (char*)uniform_name;
	this->locations[uniform_name] = location;
	//this->special_location = location;
	return location;
}

void Shaders::uniformChange(char type, int size, void* values, const std::string& uniform_name)
{
	float* vals = NULL;
	int* valsx = NULL;
	int loc;
	if (this->locations.find(uniform_name) == locations.end())
		loc = getLocation(uniform_name);
	else
		loc = this->locations[uniform_name];
	//std::cout << uniform_name << std::endl;
	//std::cout << loc << std::endl;
	
	switch (type)
	{
		case 'f':
		{
			vals = (GLfloat*)values;
			switch (size) {
				case 1:
				{
					glUniform1f(loc, *(vals));
					break;
				}
				case 2:
				{
					glUniform2f(loc, *(vals), *(vals + 1));
					break;
				}
				case 3:
				{
					glUniform3f(loc, *(vals), *(vals + 1), *(vals + 2));
					break;
				}
				case 4:
				{
					glUniform4f(loc, *(vals), *(vals + 1), *(vals + 2), *(vals + 3));
					break;
				}
				default:
					return;
			}
			break;
		}
		case 'i':
		{
			valsx = (GLint*)values;
			switch (size) {
				case 1:
				{
					glUniform1i(loc, *(valsx));
					break;
				}
				case 2:
				{
					glUniform2i(loc, *(valsx), *(valsx + 1));
					break;
				}
				case 3:
				{
					glUniform3i(loc, *(valsx), *(valsx + 1), *(valsx + 2));
					break;
				}
				case 4:
				{
					glUniform4i(loc, *(valsx), *(valsx + 1), *(valsx + 2), *(valsx + 3));
					break;
				}
				default:
					return;
			}
			break;
		}
		default:
			return;
	}
}