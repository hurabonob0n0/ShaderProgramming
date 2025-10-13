#version 330

in vec3 a_Position;
in float a_Radius;
in vec4 a_Color;
in float a_sTime;
in vec2 a_velocityXY;

out vec4 v_Color;

uniform float u_Time;
uniform vec2 u_MousePos;

const float c_PI = 3.141592f;
const vec2 c_G = vec2(0,-9.8f * 0.25f);

void practice()
{
	vec3 newPosition = a_Position;
	vec4 newColor = a_Color;

	float xDelta,yDelta;

	xDelta = 0;
	yDelta = sin(newPosition.x*c_PI);

	newPosition.y += yDelta;

	gl_Position = vec4(newPosition,1.f);
	v_Color = a_Color;
}


void main()
{
	practice();
}