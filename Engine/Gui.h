#pragma once
#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "ResourceManager.h"

class Gui
{
public:
	int Width;
	int Height;
	GLuint cursorId;

	Gui()
	{
		Width = 1280;
		Height = 720;
		cursorId = ResourceManager::GetInstance()->GetTexture("cursor");
	}

	void Render()
	{
		glUseProgram(0);

		glEnable(GL_BLEND);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, 1280, 720, 0.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cursorId);

		RenderQuad(Width / 2 - 16, Height / 2 - 16, 32, 32);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	void RenderQuad(float x, float y, float w, float h)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + w, y + h, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + w, y, 0.0f);
		glEnd();
	}
};


