//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_TECHDEMO_H
#define DRENDER_TECHDEMO_H

// Include glad *before* glfw
#include "../util/glad/glad.h"
#include "GLFW/glfw3.h"

struct GLFWwindow;

class TechDemo final
{
public:
	TechDemo();
	~TechDemo();

	void Initialize();

	void UpdateAndRender();

	void SetVSyncEnabled(bool enabled);
	void ToggleVSyncEnabled();

private:

	GLFWwindow* m_Window;

	int m_FramesThisSecond;
	int m_FPS;

	bool m_VSyncEnabled;

	GLuint m_ProgramID;
	GLuint m_MVPID;

	GLuint m_VertexArrayID;

	GLuint m_VertexBufferID;
	GLuint m_ColorBufferID;
	GLuint m_IndicesBufferID;
	GLuint m_TexCoordBufferID;

	GLuint m_TextureID;

	GLuint m_UniformTimeID;

	static const int NUM_ICONS = 3;
	GLFWimage icons[NUM_ICONS];

	TechDemo(const TechDemo&) = delete;
	TechDemo& operator=(const TechDemo&) = delete;
};

#endif//DRENDER_TECHDEMO_H
