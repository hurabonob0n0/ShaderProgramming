#version 330

layout(location=0) out vec4 FragColor;

in vec3 v_Pos;
in vec4 v_Color;

uniform vec4 u_Color;

void main()
{
	//FragColor = vec4(u_Color.r, u_Color.g, u_Color.b, u_Color.a);
	if(v_Pos.y >0.5f)
	discard;
	FragColor = v_Color;//vec4(u_Color.r, u_Color.g, u_Color.b, u_Color.a);
}
