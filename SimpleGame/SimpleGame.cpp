/*
Copyright 2022 Lee Taek Hee (Tech University of Korea)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer* g_Renderer = NULL;
bool g_bNeedReloadShaderPrograms = false;

// 1. 마우스 좌표를 저장할 전역 변수 추가
int g_MouseX = 0;
int g_MouseY = 0;

int g_WincX = 500;
int g_WincY = 500;


void RenderScene(void)
{
	if (g_bNeedReloadShaderPrograms) {
		g_Renderer->ReloadAllShaderPrograms();
		g_bNeedReloadShaderPrograms = false;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	g_Renderer->DrawParticle();

	// 여기서 g_MouseX, g_MouseY를 사용해 원하는 작업을 할 수 있습니다.
	// 예: 마우스 위치에 사각형 그리기
	// g_Renderer->DrawSolidRect(g_MouseX, g_MouseY, ...);


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		g_bNeedReloadShaderPrograms = true;
		break;
	default:
		break;
	}
}

void SpecialKeyInput(int key, int x, int y)
{

}

// 2. 마우스 움직임을 처리할 함수 정의
void PassiveMotion(int x, int y)
{
	// 전역 변수에 현재 마우스 좌표 저장
	g_MouseX = x;
	g_MouseY = y;

	// 콘솔에 좌표 출력 (테스트용)
	// std::cout << "Mouse Position: (" << g_MouseX << ", " << g_MouseY << ")\n";
}


int main(int argc, char** argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(g_WincX, g_WincY);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	// 3. main 함수에 콜백 함수 등록
	glutPassiveMotionFunc(PassiveMotion);


	glutMainLoop();

	delete g_Renderer;

	return 0;
}