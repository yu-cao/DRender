//
// Created by debyecao on 11/24/20.
//

#include "stdafx.hpp"

#include "InputManager.hpp"

#include "GameContext.hpp"
#include "Window/Window.hpp"

#include <cassert>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	for (auto iter = m_Keys.begin(); iter != m_Keys.end(); ++iter)
	{
		if (iter->second.down > 0)
		{
			++iter->second.down;
		}
	}

	for (size_t i = 0; i < MOUSE_BUTTON_COUNT; i++)
	{
		if (m_MouseButtons[i].down > 0)
		{
			++m_MouseButtons[i].down;
		}
	}
}

void InputManager::PostUpdate()
{
	m_PrevMousePosition = m_MousePosition;
}

int InputManager::GetKeyDown(KeyCode keyCode)
{
	auto value = m_Keys.find(keyCode);
	if (value == m_Keys.end())
	{
		Key key = {};
		m_Keys[keyCode] = key;
		return 0;
	}
	return m_Keys[keyCode].down;
}

bool InputManager::GetKeyPressed(KeyCode keyCode)
{
	return GetKeyDown(keyCode) == 1;
}

void InputManager::CursorPosCallback(double x, double y)
{
	m_MousePosition = glm::vec2(x, y);
}

void InputManager::MouseButtonCallback(GameContext& gameContext, MouseButton button, Action action, int mods)
{
	assert((int) button < MOUSE_BUTTON_COUNT);
	if(action == Action::PRESS)
	{
		++m_MouseButtons[(int)button].down;

		if(button == MouseButton::LEFT)
		{
			gameContext.window->SetCursorMode(Window::CursorMode::DISABLED);
		}
	}
	else
	{
		m_MouseButtons[(int)button].down = 0;

		if(button == MouseButton::LEFT)
		{
			gameContext.window->SetCursorMode(Window::CursorMode::NORMAL);
		}
	}

}

void InputManager::KeyCallback(KeyCode keyCode, int scancode, Action action, int mods)
{
	if (action == Action::PRESS)
	{
		++m_Keys[keyCode].down;
	}
	else if (action == Action::REPEAT)
	{
		++m_Keys[keyCode].down;
	}
	else if (action == Action::RELEASE)
	{
		m_Keys[keyCode].down = 0;
	}
}

glm::vec2 InputManager::GetMousePosition() const
{
	return m_MousePosition;
}

glm::vec2 InputManager::GetMouseMovement() const
{
	return m_MousePosition - m_PrevMousePosition;
}

int InputManager::GetMouseButtonDown(MouseButton button)
{
	assert((int)button >= 0 && (int)button <= MOUSE_BUTTON_COUNT - 1);

	return m_MouseButtons[(int)button].down;
}

bool InputManager::GetMouseButtonClicked(MouseButton button)
{
	assert((int)button >= 0 && (int)button <= MOUSE_BUTTON_COUNT - 1);

	return m_MouseButtons[(int)button].down == 1;
}