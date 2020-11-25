//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_GAMECONTEXT_HPP
#define DRENDER_GAMECONTEXT_HPP

#include <glm/vec2.hpp>
#include "Window/Window.hpp"

class FreeCamera;
class InputManager;
class Renderer;
class TechDemo;
class Window;

struct GameContext
{
	Window* window;
	InputManager* inputManager;

	FreeCamera* camera;
	Renderer* renderer;
	TechDemo* mainApp;

	glm::uint program;
	float elapsedTime;
	float deltaTime;
};

#endif//DRENDER_GAMECONTEXT_HPP
