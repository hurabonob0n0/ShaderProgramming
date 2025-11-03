#version 330
#define MAX_POINTS 100


in vec3 a_Position;

out vec4 v_Color;

uniform float u_Time;

uniform vec4 u_Points[MAX_POINTS];

const float c_PI = 3.141592f;

const vec4 c_Points[3] = vec4[](vec4(0,0,0.5,1.f),vec4(0.75f,0,1.f,1.5f),vec4(-0.75,0,2.f,2.f));

void Flag()
{
	vec4 newPosition = vec4(a_Position, 1.f);

    float value = (newPosition.x + 1.f) * 0.5f; // 0~1
    newPosition.y *= (1.f-value);
    float xPos = 0.f;
    float yPos = sin(value *c_PI + u_Time*60.f) * 1.f * value;
    //newPosition += vec4(yPos,yPos,yPos,yPos);
    newPosition += vec4(xPos,yPos,0,0);

    gl_Position = newPosition;
    float newColor = (sin(value *c_PI * 2.f + u_Time*30.f) +1.f)/2 + 0.3f;
    v_Color = vec4(newColor);
}

void Wave()
{
    vec4 newPosition = vec4(a_Position, 1.f);
    float dx = 0;
    float dy = 0;

    vec2 pos = vec2(a_Position.xy);
    vec2 cen = vec2(0,0);
    float d = distance(pos,cen);
    float v = 1.25f - d;
    

    newPosition += vec4(dx,dy,0,0);
    
    gl_Position = newPosition;

    float value = 1.f - d;
    ////value = clamp(value,0,1);
    ////value = ceil(value);

    float newColor = v * sin(d*10.f*c_PI-u_Time*10.f);

    /*if(d < 0.5f)
    {
        newColor = 1;
    }
    else
    {
        newColor = 0;
    }*/
    //v_Color = vec4(value *500);
    v_Color = vec4(newColor);
}

void RainDorp()
{
    vec4 newPosition = vec4(a_Position, 1.f);
    float dx = 0;
    float dy = 0;

    vec2 pos = vec2(a_Position.xy);
    float newColor = 0.f;

    for(int i =0; i<MAX_POINTS; ++i){

        float sTime = u_Points[i].z;
        float lTime = u_Points[i].w;
        float newTime = u_Time - sTime;
        if(newTime > 0)
        {
            float baseTime = fract(newTime/lTime);
            float oneMinus = 1 - baseTime;
            float t = baseTime * lTime;
            float range = lTime * baseTime * 0.6 ; 
            vec2 cen = u_Points[i].xy;
            float d = distance(pos,cen);
            float v = 5.f*clamp(range-d,0,1);
            newColor +=  oneMinus * v * sin(d*c_PI * 30.f - t * 100.f);
        }
        
    }
    

    newPosition += vec4(dx,dy,0,0);
    
    gl_Position = newPosition;

    v_Color = vec4(0.f,0.f,newColor,newColor);
}

void main()
{
    //Wave();
    //Flag();
    RainDorp();
}