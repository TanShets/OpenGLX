#include "Renderer.h"
#include <GLFW/glfw3.h>
class Events
{
	private:
		GLFWwindow* window;
		double originalPos[2], currentPos[2], temp_pos[2];
		float speed, deg_x, deg_y;
		float position[3], shift[2];
		const glm::vec3 vertical_vector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 direction;
		glm::vec3 Position, x_axis;
		bool hasChanged;
	public:
		Events(GLFWwindow* window, double* originalPos, float speed);
		Events(GLFWwindow* window, float speed);
		void update(glm::mat4* view);
		void update_keyboard();
		void update_mouse();
		float* getPosition() const;
		float* getAngleSines() const;
		bool changed();
};

