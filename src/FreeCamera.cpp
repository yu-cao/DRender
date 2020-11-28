//
// Created by debyecao on 11/24/20.
//

#include "FreeCamera.hpp"
#include "GameContext.hpp"
#include "InputManager.hpp"
#include "Window/Window.hpp"

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

FreeCamera::FreeCamera(GameContext& gameContext, float FOV, float zNear, float zFar) :
	m_FOV(FOV), m_ZNear(zNear), m_ZFar(zFar),
	m_Position(vec3(0.0f)),
	m_MoveSpeed(10.0f),
	m_MoveSpeedFastMultiplier(3.5f),
	m_MoveSpeedSlowMultiplier(0.1f),
	m_RotationSpeed(0.0011f),
	m_Yaw(0.0f),
	m_Pitch(0.0f)
{
	gameContext.camera = this;
	RecalculateViewProjection(gameContext);
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Update(const GameContext& gameContext)
{
	vec2 look = vec2(0.0f);
	if (gameContext.inputManager->GetMouseButtonDown(InputManager::MouseButton::LEFT))
	{
		look = gameContext.inputManager->GetMouseMovement();
		look.y = -look.y;

		m_Yaw += look.x * m_RotationSpeed;
		m_Pitch += look.y * m_RotationSpeed;

		float pitchLimit = glm::half_pi<float>() - 0.017f;
		if (m_Pitch > pitchLimit)
			m_Pitch = pitchLimit;
		if (m_Pitch < -pitchLimit)
			m_Pitch = -pitchLimit;
	}

	m_Forward = {};
	m_Forward.x = cos(m_Pitch) * cos(m_Yaw);
	m_Forward.y = sin(m_Pitch);
	m_Forward.z = cos(m_Pitch) * sin(m_Yaw);
	m_Forward = normalize(m_Forward);

	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);

	m_Right = normalize(cross(worldUp, m_Forward));
	m_Up = cross(m_Forward, m_Right);

	vec3 translation = {};
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_W))
	{
		translation += m_Forward;
	}
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_S))
	{
		translation -= m_Forward;
	}
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_A))
	{
		translation += m_Right;
	}
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_D))
	{
		translation -= m_Right;
	}
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_E))
	{
		translation -= m_Up;
	}
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_Q))
	{
		translation += m_Up;
	}

	float speedMultiplier = 1.0f;
	if (gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_LEFT_SHIFT))
	{
		speedMultiplier = m_MoveSpeedFastMultiplier;
	}
	else if(gameContext.inputManager->GetKeyDown(InputManager::KeyCode::KEY_LEFT_CONTROL))
	{
		speedMultiplier = m_MoveSpeedSlowMultiplier;
	}

	Translate(translation * m_MoveSpeed * speedMultiplier * gameContext.deltaTime);

	RecalculateViewProjection(gameContext);
}

void FreeCamera::SetFOV(float FOV)
{
	m_FOV = FOV;
}

void FreeCamera::SetZNear(float zNear)
{
	m_ZNear = zNear;
}

void FreeCamera::SetZFar(float zFar)
{
	m_ZFar = zFar;
}

glm::mat4 FreeCamera::GetViewProjection() const
{
	return m_ViewProjection;
}

void FreeCamera::SetMoveSpeed(float moveSpeed)
{
	m_MoveSpeed = moveSpeed;
}

void FreeCamera::SetRotationSpeed(float rotationSpeed)
{
	m_RotationSpeed = rotationSpeed;
}

void FreeCamera::Translate(glm::vec3 translation)
{
	m_Position += translation;
}

void FreeCamera::SetPosition(glm::vec3 position)
{
	m_Position = position;
}

void FreeCamera::ResetPosition()
{
	m_Position = vec3(0.0f);
}

void FreeCamera::ResetOrientation()
{
	m_Forward = vec3(0.0f, 0.0f, 1.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_Right = vec3(1.0f, 0.0f, 0.0f);}

// TODO: Measure impact of calling this every frame (optimize? Only call when values change? Only update changed values)
void FreeCamera::RecalculateViewProjection(const GameContext& gameContext)
{
	auto windowSize = gameContext.window->GetSize();
	float aspectRatio = windowSize.x / (float)windowSize.y;
	mat4 projection = perspective(m_FOV, aspectRatio, m_ZNear, m_ZFar);

	mat4 translation = translate(mat4(1.0f), m_Position);

	mat4 view = lookAt(m_Position, m_Position + m_Forward, m_Up);
	m_ViewProjection = projection * view;
}