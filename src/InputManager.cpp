//
// Created by debyecao on 11/24/20.
//

#include "InputManager.hpp"
#include "Logger.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

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

int InputManager::GetKeyDown(int vkCode)
{
	auto value = m_Keys.find(vkCode);
	if (value == m_Keys.end())
	{
		Key key = {};
		m_Keys[vkCode] = key;
		return 0;
	}
	return m_Keys[vkCode].down;
}

bool InputManager::GetKeyPressed(int vkCode)
{
	return GetKeyDown(vkCode) == 1;
}

void InputManager::CursorPosCallback(double x, double y)
{
	m_MousePosition = glm::vec2(x, y);
}

void InputManager::MouseButtonCallback(int button, int action, int mods)
{
	if (button < MOUSE_BUTTON_COUNT)
	{
		if (action == GLFW_PRESS)
		{
			++m_MouseButtons[button].down;
		}
		else
		{
			m_MouseButtons[button].down = 0;
		}
	}
}

void InputManager::KeyCallback(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		++m_Keys[key].down;
	}
	else if (action == GLFW_REPEAT)
	{
		++m_Keys[key].down;
	}
	else if (action == GLFW_RELEASE)
	{
		m_Keys[key].down = 0;
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

int InputManager::GetMouseButtonDown(int button)
{
	assert(button >= 0 && button <= MOUSE_BUTTON_COUNT - 1);

	return m_MouseButtons[button].down;
}

bool InputManager::GetMouseButtonClicked(int button)
{
	assert(button >= 0 && button <= MOUSE_BUTTON_COUNT - 1);

	return m_MouseButtons[button].down == 1;
}