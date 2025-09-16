#version 330

in vec3 a_Position;
in vec4 a_Color;

out vec4 v_Color;
out float f_Pos;

uniform float u_Time;

const float c_PI = 3.141592f;

void main()
{
	// vec3 Pos = vec3(a_Position.x - 0.5f,a_Position.y - 0.5f,0.f); - 내가 한 것
	// gl_Position = vec4(Pos,1.f);
	// float fTime = sin(u_Time* 0.025f);
	// newPosition.xy = newPosition.xy + vec2(fTime ,0);


	// 교수님 코드
	// newPosition.xy = newPosition.xy - vec2(0.5f);
	float value = fract(u_Time * 0.025f) * 2.f - 1.f; // -1 ~ 1
	vec4 newPosition = vec4(a_Position,1.f);
	float xPos = cos(value * c_PI) * 0.8f;
	float yPos = sin(value * c_PI)* 0.8f;
	newPosition.xy = newPosition.xy + vec2(xPos ,yPos);
	gl_Position = newPosition;

	v_Color = a_Color;
}
