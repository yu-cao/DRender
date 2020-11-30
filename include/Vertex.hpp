//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_VERTEX_HPP
#define DRENDER_VERTEX_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

struct GameContext;

struct VertexPosCol
{
	VertexPosCol() {};
	VertexPosCol(float x, float y, float z, float r, float g, float b) : pos{ x, y, z }, col{ r, g, b } {}
	VertexPosCol(float x, float y, float z, const float col[3]) : pos{ x, y, z }, col{ col[0], col[1], col[2] } {}
	VertexPosCol(float x, float y, float z, glm::vec4) : pos{ x, y, z }, col{ col[0], col[1], col[2] } {}
	VertexPosCol(const float pos[3], const float col[3]) : pos{ pos[0], pos[1], pos[2] }, col{ col[0], col[1], col[2] } {}
	VertexPosCol(glm::vec3 pos, glm::vec3 col) : pos{ pos[0], pos[1], pos[2] }, col{ col[0], col[1], col[2] } {}

	static const int stride = 3 * sizeof(float) + 3 * sizeof(float);
	float pos[3];
	float col[3];
};

#endif//DRENDER_VERTEX_HPP
