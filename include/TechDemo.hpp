//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_TECHDEMO_HPP
#define DRENDER_TECHDEMO_HPP

#include "Primitives.hpp"
#include "GameContext.hpp"

#include "glm/vec2.hpp"

class FreeCamera;
class InputManager;
class SceneManager;

class TechDemo final
{
public:
	TechDemo();
	~TechDemo();

	void Initialize();

	void UpdateAndRender();
	void Stop();

private:
	Window* m_Window;
	SceneManager* m_SceneManager;
	GameContext m_GameContext;

	bool m_Running;

	TechDemo(const TechDemo&) = delete;
	TechDemo& operator=(const TechDemo&) = delete;
};

#endif//DRENDER_TECHDEMO_HPP
