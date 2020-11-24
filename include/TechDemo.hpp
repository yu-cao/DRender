//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_TECHDEMO_HPP
#define DRENDER_TECHDEMO_HPP

#include "Primitives.hpp"
#include "GameContext.hpp"

// Include glad *before* glfw
#include "../util/glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/vec2.hpp"

struct GLFWwindow;
class FreeCamera;
class InputManager;

class TechDemo final
{
public:
	TechDemo();
	~TechDemo();

	void Initialize();

	void UpdateAndRender();

	void SetVSyncEnabled(bool enabled);
	void ToggleVSyncEnabled();

	glm::vec2 GetWindowSize() const;

private:
	// Callback accessors
	void UpdateWindowSize(int width, int height);
	void UpdateWindowSize(glm::tvec2<int> windowSize);
	void UpdateWindowFocused(int focused);

	GLFWwindow* m_Window;

	glm::tvec2<int> m_WindowSize;
	bool m_WindowFocused;

	int m_FramesThisSecond;
	int m_FPS;

	bool m_VSyncEnabled;

	FreeCamera *m_Camera;
	InputManager *m_InputManager;
	GameContext m_GameContext;

	GLuint m_ProgramID;

	// Uniforms
	GLuint m_TextureID;

	CubePosCol m_Cube;
	CubePosCol m_Cube2;
	SpherePosCol m_Sphere1;

	static const int NUM_ICONS = 3;
	GLFWimage icons[NUM_ICONS];

	// Allow callbacks to access us
	friend void CursorPosCallback(GLFWwindow* window, double x, double y);
	friend void WindowSizeCallback(GLFWwindow* window, int width, int height);
	friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void ErrorCallback(int error, const char* description);
	friend void WindowFocusCallback(GLFWwindow* window, int focused);

	TechDemo(const TechDemo&) = delete;
	TechDemo& operator=(const TechDemo&) = delete;
};

#endif//DRENDER_TECHDEMO_HPP
