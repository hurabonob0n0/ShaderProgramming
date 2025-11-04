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

void circle()
{	
	vec4 centerC = vec4(1.f,0.f,0.f,1.f);
	vec4 borderC = vec4(1.f,1.f,1.f,0.f);
	vec4 newColor = a_Color;
	
	vec4 newPosition = vec4(a_Position,1.f);

	float lifeTime = 1.f;
	float newTime = u_Time - a_sTime;
	float t = 0.0f; // <--- 1. 't' 변수를 if 문 밖에서 선언 및 초기화

	if(newTime > 0)
	{
		float period = a_velocityXY.x * 2.f;

		t = fract(newTime/lifeTime) * lifeTime; // <--- 2. 여기서는 값만 할당 (float 제거)

		float xPos = t * 2.f -1.f;
		float yPos = sin(t * c_PI * period);// * (a_Radius *2.f -1.f) * sin(t*c_PI);// + a_Position.y;

		// yPos *= sin(fract(newTime/lifeTime*c_PI));

		newPosition.x += xPos;
		newPosition.y += yPos;

		newColor = mix(centerC,borderC,abs(yPos*3.f));
	}
	else
	{
		newPosition.xy = vec2(-9999,0);
	}
	gl_Position = vec4(newPosition.xyz,1.f);
	v_Color = vec4(newColor.rgb,lifeTime-t); // <--- 3. 이제 't'에 접근 가능
}


void wave()
{	
	vec4 centerC = vec4(1.f,0.f,0.f,1.f);
	vec4 borderC = vec4(1.f,1.f,1.f,0.f);
	vec4 newColor = a_Color;
	
	vec4 newPosition = vec4(a_Position,1.f);

	float lifeTime = 1.f;
	float newTime = u_Time - a_sTime;

	float period = a_velocityXY.x * 1.f;

	float t = fract(newTime/lifeTime) * lifeTime;

	float xPos = t * 2.f -1.f;
	float yPos = sin(t * c_PI * period) * (a_Radius *2.f -1.f) * sin((xPos+1.f)*0.5f*c_PI);// + a_Position.y;

	// yPos *= sin(fract(newTime/lifeTime*c_PI));

	newPosition.x += xPos;
	newPosition.y += yPos;

	newColor = mix(centerC,borderC,abs(yPos*3.f));

	gl_Position = vec4(newPosition.xyz,1.f);
	v_Color = vec4(newColor.rgb,lifeTime-t);
}

void foundation()
{
	float lifeTime = 2.f - a_Color.r * 2.f;
	float newAlpha = 1.f;
	float newTime = u_Time - a_sTime;
	vec4 newPosition = vec4(a_Position,1.f);
	if(newTime > 0) {
		float t = fract(newTime/lifeTime) * lifeTime;
		float tt = t*t;
		float value = fract(u_Time * 0.025f) * 2.f - 1.f; // -1 ~ 1

		//v_Pos = newPosition.xy;

		float xPos= a_velocityXY.x * t;			// cos(value * c_PI) * a_Radius;
		float yPos= a_velocityXY.y * t + 0.5*c_G.y*tt;	//1 sin(value * c_PI)* a_Radius;
	
		newPosition.xy += vec2(xPos ,yPos);//newPosition.xy * a_Radius * 2.f + vec2(xPos ,yPos);

		//vec2 curPos = newPosition.xy;
		//
		//vec2 toMouse = u_MousePos - curPos;
		//
		//float distance = length(toMouse);
		//
		//float attractionStrength = 1.f;
		//
		//vec2 acceleration = normalize(toMouse) *
		//attractionStrength * max(distance, 0.1f);
		//
		//vec2 mouseAttractionOffset = acceleration * tt;
		//
		//newPosition.xy += mouseAttractionOffset;

		newAlpha = 1.f - t/lifeTime;
	}
	else {
		newPosition.xy = vec2(-10000,0);
	}

	gl_Position = newPosition;

	v_Color = vec4( a_Color.rgb,newAlpha);
}


void main()
{
	//foundation();
	//wave();
	circle(); // 참고: 현재 main 에서는 wave()가 호출되고 있습니다.
}