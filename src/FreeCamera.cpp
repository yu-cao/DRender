//
// Created by debyecao on 11/24/20.
//

#include "../include/FreeCamera.hpp"
#include "../include/GameContext.hpp"
#include "../include/InputManager.hpp"
#include "../include/Logger.hpp"

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <GLFW/glfw3.h>

using namespace glm;

FreeCamera::FreeCamera(const GameContext& gameContext, float FOV, float zNear, float zFar) :
	m_FOV(FOV), m_ZNear(zNear), m_ZFar(zFar),
	m_Position(vec3(0.0f)), m_Orientation(quat(vec3(0.0f))),
	m_MoveSpeed(0.1f),
	m_RotationSpeed(0.2f)
{
	RecalculateViewProjection(gameContext);
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Update(const GameContext& gameContext)
{
	vec2 look = vec2(0.0f);
	if (gameContext.inputManager->GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		vec2 mouseMovement = gameContext.inputManager->GetMouseMovement();
		look = mouseMovement;
	}
	float yaw = look.x * m_RotationSpeed * gameContext.deltaTime;
	float pitch = look.y * m_RotationSpeed * gameContext.deltaTime;

	Rotate(vec3(pitch, yaw, 0));

	mat4 matRotation = mat4(m_Orientation);
	vec3 forward = matRotation * vec4(0.0f, 0.0f, 1.0f, 0.0f);
	vec3 up = matRotation * vec4(0.0f, 1.0f, 0.0f, 0.0f);
	vec3 right = matRotation * vec4(1.0f, 0.0f, 0.0f, 0.0f);

	vec3 translation = {};
	if (gameContext.inputManager->GetKeyDown(GLFW_KEY_W))
	{
		translation += forward;
	}
	if (gameContext.inputManager->GetKeyDown(GLFW_KEY_S))
	{
		translation -= forward;
	}
	if (gameContext.inputManager->GetKeyDown(GLFW_KEY_A))
	{
		translation += right;
	}
	if (gameContext.inputManager->GetKeyDown(GLFW_KEY_D))
	{
		translation -= right;
	}
	if (gameContext.inputManager->GetKeyDown(GLFW_KEY_E))
	{
		translation -= up;
	}
	if (gameContext.inputManager->GetKeyDown(GLFW_KEY_Q))
	{
		translation += up;
	}

	Translate(translation * m_MoveSpeed);

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

void FreeCamera::SetClearColor(glm::vec3 clearColor)
{
	m_ClearColor = clearColor;
	glClearColor(m_ClearColor.x, m_ClearColor.g, m_ClearColor.b, 1.0f);
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

void FreeCamera::RotateEuler(glm::vec3 rotationEuler)
{
	Rotate(quat(rotationEuler));
}

void FreeCamera::Rotate(glm::quat rotation)
{
	m_Orientation *= rotation;
}

void FreeCamera::SetPosition(glm::vec3 position)
{
	m_Position = position;
}

void FreeCamera::SetOrientation(glm::quat orientation)
{
	m_Orientation = orientation;
}

void FreeCamera::ResetPosition()
{
	m_Position = vec3(0.0f);
}

void FreeCamera::ResetOrientation()
{
	m_Orientation = quat(vec3(0.0f));
}

// TODO: Measure impact of calling this every frame (optimize? Only call when values change? Only update changed values)
void FreeCamera::RecalculateViewProjection(const GameContext& gameContext)
{
	const vec2 windowSize = gameContext.windowSize;
	float aspectRatio = windowSize.x / (float)windowSize.y;
	mat4 Projection = perspective(m_FOV, aspectRatio, m_ZNear, m_ZFar);

	mat4 translation = translate(mat4(1.0f), m_Position);
	mat4 orientation = mat4(m_Orientation);

	mat4 View = translation * orientation;
	m_ViewProjection = Projection * View;
}