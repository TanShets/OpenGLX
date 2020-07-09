#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
//#define ASSERT(x) if(!(x)) __debugbreak();
//#define GLCall(x) ASSERT(logCall(#x, __FILE__, __LINE__))
typedef struct names {
	std::string vertexShader, fragmentShader;
}names;

class Shaders
{
	private:
		unsigned int Shader_id;
		const std::string path = "shaders/vertex.shader";
		names source_codes;
		std::unordered_map<std::string, int> locations;
	public:
		//int special_location;
		Shaders();
		~Shaders();
		void ParseShader();
		void createShader();
		static unsigned int compileShader(unsigned int type, const std::string& source_code);
		void deleteShader() const;
		void BindShader() const;
		int getLocation(const std::string& uniform_name);
		void uniformChange(char type, int size, void* values, const std::string& uniform_name);
};