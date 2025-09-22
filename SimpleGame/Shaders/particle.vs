#version 330

in vec3 a_Position;
in float a_Radius;
in vec4 a_Color;

out vec4 v_Color;
out vec2 v_Pos;

uniform float u_Time;

const float c_PI = 3.141592f;

void main()
{
	float value = fract(u_Time * 0.025f) * 2.f - 1.f; // -1 ~ 1

	vec4 newPosition = vec4(a_Position,1.f);
	
	v_Pos = newPosition.xy;

	float xPos= cos(value * c_PI) * a_Radius;
	float yPos= sin(value * c_PI)* a_Radius;
	
	/*
	if(a_Radius < 0.7f) {
		xPos = cos(value * c_PI) * a_Radius ;
		yPos = sin(value * c_PI)* a_Radius ;
	}
	else {
		xPos = cos(-value * c_PI) * a_Radius ;
		yPos = sin(-value * c_PI)* a_Radius ;
	}
	*/
	newPosition.xy = newPosition.xy * a_Radius + vec2(xPos ,yPos);
	
	gl_Position = newPosition;

	v_Color = a_Color;
}
