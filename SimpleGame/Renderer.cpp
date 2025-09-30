#include "stdafx.h"
#include "Renderer.h"

extern int g_MouseX;
extern int g_MouseY;

extern int g_WincX;
extern int g_WincY;

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	/*m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_TestShader = CompileShaders("./Shaders/test.vs", "./Shaders/test.fs");
	m_ParticleShader = CompileShaders("./Shaders/particle.vs", "./Shaders/particle.fs");*/
	CompileAllShaderPrograms();
	
	//Create VBOs
	CreateVertexBufferObjects();

	GenerateParticles(10000);

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::ReloadAllShaderPrograms()
{
	DeleteAllShaderPrograms();
	CompileAllShaderPrograms();
}

void Renderer::CompileAllShaderPrograms()
{
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_TestShader = CompileShaders("./Shaders/test.vs", "./Shaders/test.fs");
	m_ParticleShader = CompileShaders("./Shaders/particle.vs", "./Shaders/particle.fs");
}

void Renderer::DeleteAllShaderPrograms()
{
	glDeleteShader(m_SolidRectShader);
	glDeleteShader(m_TestShader);
	glDeleteShader(m_ParticleShader);
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	float temp = 0.5f;
	float size = 1.f;

	// lecture2
	float testPos[]
		=
	{
		(0.f - temp) * size, (0.f - temp) * size, 0.f, 0.5,
		(1.f - temp) * size, (0.f - temp) * size, 0.f, 0.5,
		(1.f - temp) * size, (1.f - temp) * size, 0.f, 0.5,

		(0.f - temp) * size, (0.f - temp) * size, 0.f,0.5,
		(1.f - temp) * size, (1.f - temp) * size, 0.f,0.5,
		(0.f - temp) * size, (1.f - temp) * size, 0.f, 0.5,//Quad1

		(0.f - temp) * size, (0.f - temp) * size, 0.f, 1.f,
		(1.f - temp) * size, (0.f - temp) * size, 0.f,1.f,
		(1.f - temp) * size, (1.f - temp) * size, 0.f, 1.f,

		(0.f - temp) * size, (0.f - temp) * size, 0.f,1.f,
		(1.f - temp) * size, (1.f - temp) * size, 0.f,1.f,
		(0.f - temp) * size, (1.f - temp) * size, 0.f, 1.f,//Quad2
	};
	
	glGenBuffers(1, &m_VBOTestPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testPos), testPos, GL_STATIC_DRAW);

	float testColor[]
		=
	{
		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f, //Triangle 1
						  
		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f, // Triangle 2

		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f, //Triangle 1

		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f,
		0.84, 0.60, 0.64, 1.f, // Triangle 2
	};

	glGenBuffers(1, &m_VBOTestColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testColor), testColor, GL_STATIC_DRAW);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];

	size_t slen = strlen(pShaderText);
	if (slen > INT_MAX) {
		// Handle error
	}
	GLint len = (GLint)slen;

	Lengths[0] = len;
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	float newX, newY;

	GetGLPosition(x, y, &newX, &newY);

	//Program select
	glUseProgram(m_SolidRectShader);

	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), newX, newY, 0, size);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::DrawTest()
{
	m_Time += 0.016;
	//Program select
	glUseProgram(m_TestShader);

	int uTimeloc = glGetUniformLocation(m_TestShader, "u_Time");
	glUniform1f(uTimeloc, m_Time);

	glUniform4f(glGetUniformLocation(m_TestShader, "u_Trans"),0, 0, 0, 1);
	glUniform4f(glGetUniformLocation(m_TestShader, "u_Color"), 1, 1,1, 1);

	int aPosLoc = glGetAttribLocation(m_TestShader, "a_Position");
	int aRadiusLoc = glGetAttribLocation(m_TestShader, "a_Radius");
	int aColLoc = glGetAttribLocation(m_TestShader, "a_Color");

	glEnableVertexAttribArray(aPosLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT,
		GL_FALSE, sizeof(float) * 4, 0);

	glEnableVertexAttribArray(aRadiusLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glVertexAttribPointer(aRadiusLoc, 1, GL_FLOAT,
		GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(float)*3));

	glEnableVertexAttribArray(aColLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glVertexAttribPointer(aColLoc, 4, GL_FLOAT,
		GL_FALSE, sizeof(float) * 4, 0);


	glDrawArrays(GL_TRIANGLES, 0, 12);

	glDisableVertexAttribArray(aPosLoc);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawParticle()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Time += 0.00064f;

	GLuint shader = m_ParticleShader;
	//Program select
	glUseProgram(shader);

	int uTimeloc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(uTimeloc, m_Time);

	GLuint uMousPosloc = glGetUniformLocation(shader, "u_MousePos");
	glUniform2f(uMousPosloc,
		((float)g_MouseX / (float)g_WincX)*2.f - 1.f,
		-((g_MouseY / (float)g_WincY)*2.f - 1.f));

	glUniform4f(glGetUniformLocation(shader, "u_Trans"), 0, 0, 0, 1);
	glUniform4f(glGetUniformLocation(shader, "u_Color"), 1, 1, 1, 1);

	int aPosLoc = glGetAttribLocation(shader, "a_Position");
	int aRadiusLoc = glGetAttribLocation(shader, "a_Radius");
	int aColLoc = glGetAttribLocation(shader, "a_Color");
	int asTimeLoc = glGetAttribLocation(shader, "a_sTime");
	int asVelocityLoc = glGetAttribLocation(shader, "a_velocityXY");

	glEnableVertexAttribArray(aPosLoc);
	glEnableVertexAttribArray(aRadiusLoc);
	glEnableVertexAttribArray(aColLoc);
	glEnableVertexAttribArray(asTimeLoc);
	glEnableVertexAttribArray(asVelocityLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT,
		GL_FALSE, sizeof(float) * 11, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glVertexAttribPointer(aRadiusLoc, 1, GL_FLOAT,
		GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 3));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glVertexAttribPointer(aColLoc, 4, GL_FLOAT,
		GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 4));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glVertexAttribPointer(asTimeLoc, 1, GL_FLOAT,
		GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 8));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glVertexAttribPointer(asVelocityLoc, 2, GL_FLOAT,
		GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 9));


	glDrawArrays(GL_TRIANGLES, 0, m_VBOParticleVertexCount);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPosLoc);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_BLEND);
}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::GenerateParticles(int numParticles)
{
	int floatCountPerVertex = 3 + 1 + 4 + 1 + 2; // x,y,z, radius, r,g,b,a, startTime, vx,vy;
	int verticesCountPerParticle = 6; // Quad
	int floatCountPerParticle = floatCountPerVertex * verticesCountPerParticle;
	int totalVerticeisCount = numParticles * verticesCountPerParticle;
	int totalFloatCount = floatCountPerVertex * totalVerticeisCount;

	float* pVertices = new float[totalFloatCount];

	for (int i = 0; i < numParticles; ++i) {
		float x, y, z, value, r, g, b, a;

		x = 0.f;//float(rand()) / (float)RAND_MAX * 2 - 1.f;
		y = 0.f;//float(rand()) / (float)RAND_MAX * 2 - 1.f;
		z = 0.f;

		value = float(rand()) / (float)RAND_MAX;

		r = float(rand()) / (float)RAND_MAX;
		g = float(rand()) / (float)RAND_MAX;
		b = float(rand()) / (float)RAND_MAX;
		a = float(rand()) / (float)RAND_MAX;

		float size;
		size = (float(rand()) / (float)RAND_MAX) * 0.01f;

		float sTime = (float(rand()) / (float)RAND_MAX) * 2.f;

		float vx = ((float(rand()) / (float)RAND_MAX) * 1.f - 0.5f);
		float vy = (((float(rand()) / (float)RAND_MAX) * 0.5f + 0.5f) + 0.5f) * 1.f;

		int index = i * floatCountPerVertex * verticesCountPerParticle;
		pVertices[index++] = x - size;
		pVertices[index++] = y - size;
		pVertices[index++] = z ;
		pVertices[index++] = value;
		pVertices[index++] = r;
		pVertices[index++] = g;
		pVertices[index++] = b;
		pVertices[index++] = a;
		pVertices[index++] = sTime;
		pVertices[index++] = vx;
		pVertices[index++] = vy;

		pVertices[index++] = x + size;
		pVertices[index++] = y - size;
		pVertices[index++] = z ;
		pVertices[index++] = value;
		pVertices[index++] = r;
		pVertices[index++] = g;
		pVertices[index++] = b;
		pVertices[index++] = a;
		pVertices[index++] = sTime;
		pVertices[index++] = vx;
		pVertices[index++] = vy;

		pVertices[index++] = x + size;
		pVertices[index++] = y + size;
		pVertices[index++] = z - size;
		pVertices[index++] = value;
		pVertices[index++] = r;
		pVertices[index++] = g;
		pVertices[index++] = b;
		pVertices[index++] = a; // Rect1
		pVertices[index++] = sTime;
		pVertices[index++] = vx;
		pVertices[index++] = vy;

		pVertices[index++] = x - size;
		pVertices[index++] = y - size;
		pVertices[index++] = z;
		pVertices[index++] = value;
		pVertices[index++] = r;
		pVertices[index++] = g;
		pVertices[index++] = b;
		pVertices[index++] = a;
		pVertices[index++] = sTime;
		pVertices[index++] = vx;
		pVertices[index++] = vy;

		pVertices[index++] = x + size;
		pVertices[index++] = y + size;
		pVertices[index++] = z - size;
		pVertices[index++] = value;
		pVertices[index++] = r;
		pVertices[index++] = g;
		pVertices[index++] = b;
		pVertices[index++] = a;
		pVertices[index++] = sTime;
		pVertices[index++] = vx;
		pVertices[index++] = vy;

		pVertices[index++] = x - size;
		pVertices[index++] = y + size;
		pVertices[index++] = z - size;
		pVertices[index++] = value;
		pVertices[index++] = r;
		pVertices[index++] = g;
		pVertices[index++] = b;
		pVertices[index++] = a; // Rect 2
		pVertices[index++] = sTime;
		pVertices[index++] = vx;
		pVertices[index++] = vy;

	}

	glGenBuffers(1, &m_VBOParticle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * totalFloatCount, pVertices, GL_STATIC_DRAW);

	m_VBOParticleVertexCount = totalVerticeisCount;

	delete [] pVertices;
}


