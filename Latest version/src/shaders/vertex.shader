#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
//layout(location = 2) in vec2 texCoord;
layout(location = 1) in vec4 v_Color;

//out vec2 v_TexCoord;
out vec4 u_Color;

uniform mat4 proj;
uniform mat4 view;
//uniform mat4 rot;
//uniform vec4 origin;
//uniform vec4 shift;
uniform mat4 u_MVP;

void main()
{
	//vec4 temp = view * position;
	mat4 result = proj * view;
	gl_Position = u_MVP * position;// proj* temp;
	//vec4 tempx = vec4(shift, 1.0, 1.0);
	//float dist = position[2] - origin[2];
	//if (dist < 0)
	//	dist = -dist;
	//vec2 tempw = dist * shift;
	//vec4 tempx = vec4(tempw, 0.0, 0.0);
	//	position = position - shift;
	//gl_Position = result * position;
	//vec4 temp = origin;
	//mat4 result = proj * view;
	//gl_Position = result * position - temp;
	u_Color = v_Color;
	//v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//in vec2 v_TexCoord;
in vec4 u_Color;
//uniform vec4 u_Color;
//uniform sampler2D u_Texture;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	color = u_Color;//texColor;
};