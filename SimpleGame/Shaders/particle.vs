#version 330

in vec3 a_Position;
in float a_Radius;
in vec4 a_Color;
in float a_sTime;

out vec4 v_Color;
out vec2 v_Pos;

uniform float u_Time;

const float c_PI = 3.141592f;
const vec2 c_G = vec2(0,-9.8f * 2.f);

void main()
{
	float newTime = u_Time - a_sTime;
	vec4 newPosition = vec4(a_Position,1.f);
	if(newTime > 0) {
		float t = fract(newTime/1.0) * 1.f;
		float tt = t*t;
		float value = fract(u_Time * 0.025f) * 2.f - 1.f; // -1 ~ 1

	
		v_Pos = newPosition.xy;

		float xPos=	a_Radius * t;	// 0.f;			// cos(value * c_PI) * a_Radius;
		float yPos= 0.5*c_G.y*tt;	//1 sin(value * c_PI)* a_Radius;
	
	
		/*float xPos,yPos;
		if(a_Radius < 0.7f) {
			xPos = cos(value * c_PI) * a_Radius ;
			yPos = sin(value * c_PI)* a_Radius ;
		}
		else {
			xPos = -cos(value * c_PI) * a_Radius ;
			yPos = sin(value * c_PI)* a_Radius ;
		}*/
	
		newPosition.xy += vec2(xPos ,yPos + 0.5f);//newPosition.xy * a_Radius * 2.f + vec2(xPos ,yPos);
	}
	else {
		newPosition.xy = vec2(-10000,0);
	}

	gl_Position = newPosition;

	v_Color = a_Color;
}
