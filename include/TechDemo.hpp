//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_TECHDEMO_HPP
#define DRENDER_TECHDEMO_HPP

#include "GameContext.hpp"

class FreeCamera;
class InputManager;
class SceneManager;
class Window;

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
	FreeCamera* m_DefaultCamera;

	bool m_Running;

	TechDemo(const TechDemo&) = delete;
	TechDemo& operator=(const TechDemo&) = delete;

	void Destroy();
};

#endif//DRENDER_TECHDEMO_HPP
