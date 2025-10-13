#version 330

in vec3 a_Position;

out vec4 v_Color;

uniform float u_Time;

const float c_PI = 3.141592f;

void main()
{
	vec4 newPosition = vec4(a_Position, 1.f);

    float value = (newPosition.x + 1.f) * 0.5f; // 0~1
    newPosition.y *= (1.f-value);
    float xPos = 0.f;
    float yPos = sin(value *c_PI * 2.f + u_Time*30.f) * 1.f * value;
    //newPosition += vec4(yPos,yPos,yPos,yPos);
    newPosition += vec4(xPos,yPos,0,0);

    gl_Position = newPosition;
    float newColor = (sin(value *c_PI * 2.f + u_Time*30.f) +1.f)/2 + 0.3f;
    v_Color = vec4(newColor);
}
