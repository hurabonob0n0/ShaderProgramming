#version 330

in vec3 a_Position;
in vec4 a_Color;

out vec4 v_Color;

void main()
{
	// vec3 Pos = vec3(a_Position.x - 0.5f,a_Position.y - 0.5f,0.f); - 내가 한 것
	// gl_Position = vec4(Pos,1.f);

	// 교수님 코드
	vec4 newPosition = vec4(a_Position,1.f);
	// newPosition.xy = newPosition.xy - vec2(0.5f);
	newPosition.xy = newPosition.xy;
	gl_Position = newPosition;

	v_Color = a_Color;
}
