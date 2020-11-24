//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_TECHDEMO_H
#define DRENDER_TECHDEMO_H

// Include glad *before* glfw
#include "../util/glad/glad.h"

struct GLFWwindow;

class TechDemo final
{
public:
	TechDemo();
	~TechDemo();

	void Initialize();

	void UpdateAndRun();

	void SetVSyncEnabled(bool enabled);
	void ToggleVSyncEnabled();

private:

	GLFWwindow* m_Window;

	bool m_VSyncEnabled;

	GLuint m_ProgramID;
	GLuint m_MVPID;

	GLuint m_VertexArrayID;

	GLuint m_VertexBufferID;
	GLuint m_ColorBufferID;
	GLuint m_IndicesBufferID;

	TechDemo(const TechDemo&) = delete;
	TechDemo& operator=(const TechDemo&) = delete;

};

#endif//DRENDER_TECHDEMO_H
