//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_GAMECONTEXT_HPP
#define DRENDER_GAMECONTEXT_HPP

#include "FreeCamera.hpp"
#include "InputManager.hpp"

#include <glm/vec2.hpp>

struct GameContext
{
	FreeCamera* camera;
	InputManager* inputManager;
	glm::vec2 windowSize;
	bool windowFocused;
	float elapsedTime;
	float deltaTime;
};

#endif//DRENDER_GAMECONTEXT_HPP
