#include <string>
#include <GL/glew.h>
#include <stb_image.h>

class Texture
{
	private:
		unsigned int textureID;
		std::string path;
		unsigned char* local_Buffer;
		int width, height, Bpp;
	public:
		Texture(const std::string& path);
		~Texture();
		void Bind() const;
		void Bind(unsigned int slot /*= 0*/) const;
		void UnBind() const;

		inline int getWidth() const { return this->width; }
		inline int getHeight() const { return this->height; }
};