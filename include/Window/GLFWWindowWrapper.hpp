//
// Created by debyecao on 11/25/20.
//

#ifndef DRENDER_GLFWWINDOWWRAPPER_HPP
#define DRENDER_GLFWWINDOWWRAPPER_HPP

#include "Window.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

struct GameContext;

class GLFWWindowWrapper : public Window
{
public:
	GLFWWindowWrapper(std::string title, glm::vec2 size, GameContext& gameContext);
	virtual ~GLFWWindowWrapper();

	virtual void Update(const GameContext& gameContext) override;
	virtual void PollEvents() override;

	GLFWwindow* GetWindow() const;

protected:
	virtual void SetWindowTitle(std::string title) override;

private:
	static const int NUM_ICONS = 3;
	GLFWimage icons[NUM_ICONS];

	GLFWwindow* m_Window;

	float m_PreviousFrameTime;

	GLFWWindowWrapper(const GLFWWindowWrapper&) = delete;
	GLFWWindowWrapper& operator=(const GLFWWindowWrapper&) = delete;
};

#endif//DRENDER_GLFWWINDOWWRAPPER_HPP
