//
// Created by debyecao on 11/25/20.
//
#include "stdafx.hpp"

#include "Window/Window.hpp"
#include "Window/GLWindowWrapper.hpp"
#include "Helpers/Helpers.hpp"
#include "Logger.hpp"

using namespace glm;

Window::Window(std::string title, glm::vec2 size, GameContext& gameContext) :
	m_TitleString(title),
	m_Size(size),
	m_ShowFPSInWindowTitle(true),
	m_ShowMSInWindowTitle(true),
	m_GameContextRef(gameContext),
	m_UpdateWindowTitleFrequency(0.0f),
	m_SecondsSinceTitleUpdate(0.0f)
{
	gameContext.window = this;
}

Window::~Window()
{
}

void Window::Update(const GameContext& gameContext)
{
	m_GameContextRef = gameContext;

	m_SecondsSinceTitleUpdate += gameContext.deltaTime;
	if (m_SecondsSinceTitleUpdate >= m_UpdateWindowTitleFrequency)
	{
		m_SecondsSinceTitleUpdate = 0.0f;
		SetWindowTitle(GenerateWindowTitle(gameContext.deltaTime));
	}
}

tvec2<int> Window::GetSize() const
{
	return m_Size;
}

bool Window::HasFocus() const
{
	return m_HasFocus;
}

GLFWwindow* Window::IsGLFWWindow()
{
	GLWindowWrapper* glWindow = dynamic_cast<GLWindowWrapper*>(this);
	if (glWindow)
	{
		return glWindow->GetWindow();
	}

	VulkanWindowWrapper* vulkanWindow = dynamic_cast<VulkanWindowWrapper*>(this);
	if (vulkanWindow)
	{
		return vulkanWindow->GetWindow();
	}
	return nullptr;
}

void Window::SetTitleString(std::string title)
{
	m_TitleString = title;
}

std::string Window::GenerateWindowTitle(float dt)
{
	std::string result = m_TitleString;
	if (m_ShowMSInWindowTitle) result += "   " + Helpers::FloatToString(dt, 3) + " ms";
	if (m_ShowFPSInWindowTitle) result += +" | " + Helpers::FloatToString(1.0f / dt, 0) + " FPS ";
	return result;
}

void Window::SetShowFPSInTitleBar(bool showFPS)
{
	m_ShowFPSInWindowTitle = showFPS;
}

void Window::SetShowMSInTitleBar(bool showMS)
{
	m_ShowMSInWindowTitle = showMS;
}

void Window::SetUpdateWindowTitleFrequency(float updateFrequencyinSeconds)
{
	m_UpdateWindowTitleFrequency = updateFrequencyinSeconds;
}


// Callbacks
void Window::KeyCallback(InputManager::KeyCode keyCode, int scancode, InputManager::Action action, int mods)
{
	m_GameContextRef.inputManager->KeyCallback(keyCode, scancode, action, mods);
}

void Window::MouseButtonCallback(InputManager::MouseButton mouseButton, InputManager::Action action, int mods)
{
	m_GameContextRef.inputManager->MouseButtonCallback(m_GameContextRef, mouseButton, action, mods);
}

void Window::WindowFocusCallback(int focused)
{
	m_HasFocus = focused != 0;
}

void Window::CursorPosCallback(double x, double y)
{
	m_GameContextRef.inputManager->CursorPosCallback(x, y);
}

void Window::WindowSizeCallback(int width, int height)
{
	SetSize(width, height);
}