#include "Events.h"

Events::Events(GLFWwindow* window, double* originalPos, float speed)
{
	int i;
	this->window = window;
	this->hasChanged = false;
	for (i = 0; i < 2; i++)
	{
		this->originalPos[i] = *(originalPos + i);
		this->currentPos[i] = this->originalPos[i];
		this->temp_pos[i] = -1;
		this->shift[i] = 0;
	}
	this->speed = speed;
	this->deg_x = 0, this->deg_y = 0;
	for (i = 0; i < 3; i++)
		this->position[i] = 0.0f;
	this->Position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->direction = glm::vec3(0.0f, 0.0f, -1.0f);
	this->x_axis = glm::vec3(1.0f, 0.0f, 0.0f);
}

Events::Events(GLFWwindow* window, float speed)
{
	this->window = window;
	this->hasChanged = false;
	glfwGetCursorPos(this->window, &this->originalPos[0], &this->originalPos[1]);
	//this->currentPos[0] = this->originalPos[0];
	//this->currentPos[1] = this->originalPos[1];
	int i;
	for (i = 0; i < 2; i++)
	{
		this->currentPos[i] = this->originalPos[i];
		this->temp_pos[i] = -1;
		this->shift[i] = 0;
	}
	this->speed = speed;
	this->deg_x = 0, this->deg_y = 0;
	for (i = 0; i < 3; i++)
		this->position[i] = 0.0f;
	this->Position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->direction = glm::vec3(0.0f, 0.0f, -1.0f);
	this->x_axis = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Events::update(glm::mat4* view)
{
	this->update_keyboard();
	this->update_mouse();
	*view = glm::lookAt(this->Position, this->Position + this->direction, this->vertical_vector);
}

void Events::update_keyboard()
{
	int val1 = glfwGetKey(this->window, GLFW_KEY_W);
	int val2 = glfwGetKey(this->window, GLFW_KEY_UP);
	if (val1 == GLFW_PRESS || val2 == GLFW_PRESS)
	{
		this->Position += speed * this->direction;//this->position[2] += speed * this->direction.z;
		//std::cout << "Pos: " << Position.x << " " << Position.y << " " << Position.z << std::endl;
		this->hasChanged = true;
	}
	val1 = glfwGetKey(this->window, GLFW_KEY_S);
	val2 = glfwGetKey(this->window, GLFW_KEY_DOWN);
	if (val1 == GLFW_PRESS || val2 == GLFW_PRESS)
	{
		this->Position -= speed * this->direction;//this->position[2] -= speed * this->direction.z;
		this->hasChanged = true;
	}
	val1 = glfwGetKey(this->window, GLFW_KEY_A);
	val2 = glfwGetKey(this->window, GLFW_KEY_LEFT);
	glm::vec3 tempo = glm::cross(this->direction, this->vertical_vector);
	if (val1 == GLFW_PRESS || val2 == GLFW_PRESS)
	{
		//std::cout << "Tempo " << speed * tempo.x << " " << speed * tempo.y << " " << speed * tempo.z << std::endl;
		this->Position -= speed * tempo;//this->position[0] += speed;
		this->hasChanged = true;
	}
	val1 = glfwGetKey(this->window, GLFW_KEY_D);
	val2 = glfwGetKey(this->window, GLFW_KEY_RIGHT);
	if (val1 == GLFW_PRESS || val2 == GLFW_PRESS)
	{
		this->Position += speed * tempo; //this->position[0] -= 0.5 * speed;
		this->hasChanged = true;
	}

	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->Position += (float)(0.5 * speed) * this->vertical_vector;//this->position[1] += 0.5 * speed;

	if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->Position -= (float)(0.5 * speed) * this->vertical_vector;//this->position[1] -= 0.5 * speed;
	//this->Position.x = this->position[0];
	//this->Position.y = this->position[1];
	//this->Position.z = this->position[2];
	//*view = glm::translate(glm::mat4(1.0), glm::vec3(this->position[0], this->position[1], this->position[2]));
}

void Events::update_mouse()
{
	this->temp_pos[0] = -1;
	this->temp_pos[1] = -1;
	float changex = 0, changey = 0;
	glfwGetCursorPos(this->window, &temp_pos[0], &temp_pos[1]);
	if (this->temp_pos[0] == this->currentPos[0] && this->temp_pos[1] == this->currentPos[1])
		return;

	if (this->temp_pos[0] > this->currentPos[0])
		changex = (this->currentPos[0] - this->temp_pos[0]) * speed;//changex = -10 * speed;
	else if (this->temp_pos[0] < this->currentPos[0])
		changex = (this->currentPos[0] - this->temp_pos[0]) * speed;//10 * speed;

	if (this->temp_pos[1] > this->currentPos[1])
		changey = (this->currentPos[1] - this->temp_pos[1]) * speed;//-10 * speed;
	else if (this->temp_pos[1] < this->currentPos[1])
		changey = (this->currentPos[1] - this->temp_pos[1]) * speed;//10 * speed;

	this->x_axis = glm::cross(this->direction, this->vertical_vector);
	//glm::mat4 rot_x = glm::rotate(glm::mat4(1.0), glm::radians(this->deg_x), glm::vec3(1.0f, 0.0f, 0.0f));
	//glm::mat4 rot_y = glm::rotate(glm::mat4(1.0), glm::radians(this->deg_y), glm::vec3(0.0f, 1.0f, 0.0f));
	//*rot = rot_x * rot_y;
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(changex), this->vertical_vector) \
		* glm::rotate(glm::mat4(1.0f), glm::radians(changey), this->x_axis);
	this->direction = glm::mat3(rot) * this->direction;
	//this->direction *= 0.1;
	this->currentPos[0] = this->temp_pos[0];
	this->currentPos[1] = this->temp_pos[1];
	//this->Position = *((glm::vec3*)this->position);
	/*
	this->direction.x -= speed;//cos(glm::radians(this->deg_x)) * cos(glm::radians(this->deg_y)); 
	this->direction.y -= speed;// sin(glm::radians(this->deg_y)); 
	this->direction.z -= speed;// sin(glm::radians(this->deg_x))* cos(glm::radians(this->deg_y));
	//this->direction = glm::normalize(this->direction);
	*/
	//this->direction *= 0.001;
	//this->direction *= 0.1;
	//this->x_axis = glm::cross(this->vertical_vector, this->direction);
	
	//*rot = glm::lookAt(this->Position, this->Position + this->direction, this->vertical_vector);
}

float* Events::getPosition() const
{
	return (float*)this->position;
}

float* Events::getAngleSines() const
{
	float sine[4] = {0, 0, 0, 0};
	sine[0] = sin((float)glm::radians(this->deg_x));
	sine[1] = sin((float)glm::radians(this->deg_y));
	return sine;
}

bool Events::changed()
{
	if (this->hasChanged)
	{
		this->hasChanged = false;
		return true;
	}
	else
		return false;
}
