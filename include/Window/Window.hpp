//
// Created by debyecao on 11/25/20.
//

#ifndef DRENDER_WINDOW_HPP
#define DRENDER_WINDOW_HPP

#include "GameContext.hpp"
#include "InputManager.hpp"

#include <string>

struct GLFWwindow;

class Window
{
public:
	enum class CursorMode
	{
		NORMAL,
		HIDDEN,
		DISABLED
	};

	Window(std::string title, glm::vec2 size, GameContext& gameContext);
	virtual ~Window();

	virtual void Update(const GameContext& gameContext);
	virtual void PollEvents() = 0;

	glm::tvec2<int> GetSize() const;
	virtual void SetSize(int width, int height) = 0;
	bool HasFocus() const;

	void SetTitleString(std::string title);
	void SetShowFPSInTitleBar(bool showFPS);
	void SetShowMSInTitleBar(bool showMS);
	// Set to 0 to update window title every frame
	void SetUpdateWindowTitleFrequency(float updateFrequencyinSeconds);

	virtual void SetCursorMode(CursorMode mode) = 0;

	GLFWwindow* IsGLFWWindow();

protected:
	// Callbacks
	virtual void KeyCallback(InputManager::KeyCode keycode, int scancode, InputManager::Action action, int mods);
	virtual void MouseButtonCallback(InputManager::MouseButton mouseButton, InputManager::Action action, int mods);
	virtual void WindowFocusCallback(int focused);
	virtual void CursorPosCallback(double x, double y);
	virtual void WindowSizeCallback(int width, int height);

	friend void GLFWKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	friend void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
	friend void GLFWWindowFocusCallback(GLFWwindow* glfwWindow, int focused);
	friend void GLFWCursorPosCallback(GLFWwindow* glfwWindow, double x, double y);
	friend void GLFWWindowSizeCallback(GLFWwindow* glfwWindow, int width, int height);

	//void UpdateWindowSize(int width, int height);
	//void UpdateWindowSize(glm::vec2i windowSize);
	//void UpdateWindowFocused(int focused);

	virtual void SetWindowTitle(std::string title) = 0;

	// Store this privately so we can access it in callbacks
	// Should be updated with every call to Update()
	GameContext& m_GameContextRef;

	std::string m_TitleString;
	glm::tvec2<int> m_Size;
	bool m_HasFocus;

	bool m_ShowFPSInWindowTitle;
	bool m_ShowMSInWindowTitle;

	float m_UpdateWindowTitleFrequency;
	float m_SecondsSinceTitleUpdate;

private:
	std::string GenerateWindowTitle(float dt);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

#endif//DRENDER_WINDOW_HPP
