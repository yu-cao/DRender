//
// Created by debyecao on 11/29/20.
//

#ifndef DRENDER_SPHEREPOSCOL_HPP
#define DRENDER_SPHEREPOSCOL_HPP

#include "Vertex.hpp"
#include <vector>

struct SpherePosCol
{
	SpherePosCol();
	void Init(const GameContext& gameContext, glm::vec3 position, glm::quat rotation = glm::quat(glm::vec3(0.0f)), glm::vec3 scale = glm::vec3(1.0f));
	void Destroy(const GameContext& gameContext);
	~SpherePosCol();

	void Render(const GameContext& gameContext);

	std::vector<VertexPosCol> m_Vertices;
	std::vector<glm::uint> m_Indices;

	glm::uint m_RenderID;

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::uint m_UniformTimeID;
};


#endif//DRENDER_SPHEREPOSCOL_HPP
