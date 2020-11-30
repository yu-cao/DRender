//
// Created by debyecao on 11/24/20.
//
#include "stdafx.hpp"

#include "TechDemo.hpp"
#include "FreeCamera.hpp"
#include "InputManager.hpp"
#include "Scene/SceneManager.hpp"
#include "Scene/TestScene.hpp"

// Ensure more than one API isn't defined
#if COMPILE_VULKAN
#if COMPILE_OPEN_GL
assert(false);
#endif
#endif

#if COMPILE_OPEN_GL
#if COMPILE_VULKAN
assert(false);
#endif
#endif

using namespace glm;

TechDemo::TechDemo()
{
}

TechDemo::~TechDemo()
{
	delete m_GameContext.inputManager;
	delete m_DefaultCamera;
	delete m_SceneManager;
	delete m_Window;
	delete m_GameContext.renderer;
}

void TechDemo::Initialize()
{
	m_GameContext = {};
	m_GameContext.mainApp = this;

#if COMPILE_VULKAN
	m_Window = new VulkanWindowWrapper("Vulkan Demo", vec2(1920, 1080), m_GameContext);
	VulkanRenderer* renderer = new VulkanRenderer(m_GameContext);
#elif COMPILE_OPEN_GL
	m_Window = new GLWindowWrapper("Tech Demo", vec2(1920, 1080), m_GameContext);
	GLRenderer* renderer = new GLRenderer(m_GameContext);
#endif

	m_Window->SetUpdateWindowTitleFrequency(0.4f);

	m_GameContext.renderer->SetVSyncEnabled(true);

	m_SceneManager = new SceneManager();
	TestScene* testScene = new TestScene(m_GameContext);
	m_SceneManager->AddScene(testScene);

	m_DefaultCamera = new FreeCamera(m_GameContext);
	m_DefaultCamera->SetPosition(vec3(-10.0f, 3.0f, -5.0f));
	m_GameContext.camera = m_DefaultCamera;

	m_GameContext.inputManager = new InputManager();

	renderer->PostInitialize();
}

void TechDemo::Stop()
{
	m_Running = false;
}

void TechDemo::Destroy()
{
	m_SceneManager->Destroy(m_GameContext);
}


void TechDemo::UpdateAndRender()
{
	m_Running = true;
	float previousTime = (float)glfwGetTime();
	while(m_Running)
	{
		float currentTime = (float)glfwGetTime();
		float dt = currentTime - previousTime;
		previousTime = currentTime;

		if (dt < 0.0f) dt = 0.0f;

		m_GameContext.deltaTime = dt;
		m_GameContext.elapsedTime = currentTime;

		m_GameContext.window->PollEvents();

		m_GameContext.inputManager->Update();
		m_GameContext.camera->Update(m_GameContext);
		m_GameContext.renderer->Clear((int)Renderer::ClearFlag::COLOR | (int)Renderer::ClearFlag::DEPTH);

		m_GameContext.window->Update(m_GameContext);

		m_SceneManager->UpdateAndRender(m_GameContext);

		m_GameContext.inputManager->PostUpdate();

		m_GameContext.renderer->SwapBuffers(m_GameContext);
	}

	Destroy();
}