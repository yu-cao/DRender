//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_FREECAMERA_HPP
#define DRENDER_FREECAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

struct GameContext;

class FreeCamera
{
public:
	FreeCamera(const GameContext& gameContext, float FOV = 45.0f, float zNear = 0.1f, float zFar = 1000.0f);
	~FreeCamera();

	void Update(const GameContext& gameContext);

	void SetFOV(float FOV);
	void SetZNear(float zNear);
	void SetZFar(float zFar);
	void SetClearColor(glm::vec3 clearColor);
	glm::mat4 GetViewProjection() const;

	void SetMoveSpeed(float moveSpeed);
	void SetRotationSpeed(float rotationSpeed);

	void Translate(glm::vec3 translation);
	void RotateEuler(glm::vec3 rotationEuler);
	void Rotate(glm::quat rotation);

	void SetPosition(glm::vec3 position);
	void SetOrientation(glm::quat orientation);

	void ResetPosition();
	void ResetOrientation();

private:
	void RecalculateViewProjection(const GameContext& gameContext);

	glm::mat4 m_ViewProjection;
	float m_FOV;
	float m_ZNear;
	float m_ZFar;

	glm::vec3 m_Position;
	glm::quat m_Orientation;
	glm::vec3 m_ClearColor;

	float m_MoveSpeed;
	float m_RotationSpeed;
};

#endif//DRENDER_FREECAMERA_HPP
