#version 330

in vec3 a_Position;
in float a_Radius;
in vec4 a_Color;
in float a_sTime;
in vec2 a_velocityXY;

out vec4 v_Color;
out vec2 v_Pos;

uniform float u_Time;
uniform vec2 u_MousePos;

const float c_PI = 3.141592f;
const vec2 c_G = vec2(0,-9.8f * 0.25f);

void main()
{
	float lifeTime = 2.f - a_Color.r * 2.f;
	float newAlpha = 1.f;
	float newTime = u_Time - a_sTime;
	vec4 newPosition = vec4(a_Position,1.f);
	if(newTime > 0) {
		float t = fract(newTime/lifeTime) * lifeTime;
		float tt = t*t;
		float value = fract(u_Time * 0.025f) * 2.f - 1.f; // -1 ~ 1

		v_Pos = newPosition.xy;

		float xPos= a_velocityXY.x * t;			// cos(value * c_PI) * a_Radius;
		float yPos= a_velocityXY.y * t + 0.5*c_G.y*tt;	//1 sin(value * c_PI)* a_Radius;
	
		newPosition.xy += vec2(xPos ,yPos);//newPosition.xy * a_Radius * 2.f + vec2(xPos ,yPos);

		vec2 curPos = newPosition.xy;

		vec2 toMouse = u_MousePos - curPos;

		float distance = length(toMouse);

		float attractionStrength = 1.f;

		vec2 acceleration = normalize(toMouse) *
		attractionStrength * max(distance, 0.1f);

		vec2 mouseAttractionOffset = acceleration * tt;

		newPosition.xy += mouseAttractionOffset;

		newAlpha = 1.f - t/lifeTime;
	}
	else {
		newPosition.xy = vec2(-10000,0);
	}

	gl_Position = newPosition;

	v_Color = vec4( a_Color.rgb,newAlpha);
}
