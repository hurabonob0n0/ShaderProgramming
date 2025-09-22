#version 330

layout(location=0) out vec4 FragColor;

in vec4 v_Color;
in vec2 v_Pos;

void main()
{
	//FragColor = v_Color;
	if(length(v_Pos) > 0.5f){
		discard;
	}
	FragColor = vec4(0.9f,0.1f,0.1f,1.f);
}
