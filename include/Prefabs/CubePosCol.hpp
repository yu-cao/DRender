//
// Created by debyecao on 11/29/20.
//

#ifndef DRENDER_CUBEPOSCOL_HPP
#define DRENDER_CUBEPOSCOL_HPP

#include "Vertex.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct GameContext;

struct CubePosCol
{
	CubePosCol();

	void Init(const GameContext& gameContext, glm::vec3 position, glm::quat rotation = glm::quat(glm::vec3(0.0f)), glm::vec3 scale = glm::vec3(1.0f));
	void Destroy(const GameContext& gameContext);
	~CubePosCol();

	void Render(const GameContext& gameContext);

	std::vector<VertexPosCol> m_Vertices;

	glm::uint m_RenderID;

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::uint m_UniformTimeID;
};

#endif//DRENDER_CUBEPOSCOL_HPP
