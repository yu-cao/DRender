//
// Created by debyecao on 11/25/20.
//

#ifndef DRENDER_GLFWWINDOWWRAPPER_HPP
#define DRENDER_GLFWWINDOWWRAPPER_HPP

#include "Window.hpp"

#include <GLFW/glfw3.h>

struct GameContext;

class GLFWWindowWrapper : public Window
{
public:
	GLFWWindowWrapper(std::string title, glm::vec2 size, GameContext& gameContext);
	virtual ~GLFWWindowWrapper();

	virtual void Update(const GameContext& gameContext) override;
	virtual void PollEvents() override;
	virtual void SetCursorMode(CursorMode mode) override;

	GLFWwindow* GetWindow() const;

protected:
	virtual void SetWindowTitle(std::string title) override;
	GLFWwindow* m_Window;

private:
	static const int NUM_ICONS = 3;
	GLFWimage icons[NUM_ICONS];

	float m_PreviousFrameTime;

	GLFWWindowWrapper(const GLFWWindowWrapper&) = delete;
	GLFWWindowWrapper& operator=(const GLFWWindowWrapper&) = delete;
};

void GLFWErrorCallback(int error, const char* description);
void GLFWKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
void GLFWWindowFocusCallback(GLFWwindow* glfwWindow, int focused);
void GLFWCursorPosCallback(GLFWwindow* glfwWindow, double x, double y);
void GLFWWindowSizeCallback(GLFWwindow* glfwWindow, int width, int height);

#endif//DRENDER_GLFWWINDOWWRAPPER_HPP
