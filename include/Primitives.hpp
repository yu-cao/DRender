//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_PRIMITIVES_HPP
#define DRENDER_PRIMITIVES_HPP

#include "Colors.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../util/glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

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

struct CubePosCol
{
	CubePosCol();

	void Init(GLuint program, glm::vec3 position, glm::quat rotation = glm::quat(glm::vec3(0.0f)), glm::vec3 scale = glm::vec3(1.0f));
	~CubePosCol();

	void Draw(GLuint program, const GameContext& gameContext, float currentTime);

	static const int NUM_VERTS = 4 * 12;
	static const VertexPosCol s_Vertices[NUM_VERTS];

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	GLuint m_MVPID;
	GLuint m_UniformTimeID;
	GLuint m_VAO;
	GLuint m_VBO;
};

struct SpherePosCol
{
	SpherePosCol();
	void Init(GLuint program, glm::vec3 position, glm::quat rotation = glm::quat(glm::vec3(0.0f)), glm::vec3 scale = glm::vec3(1.0f));
	~SpherePosCol();

	void Draw(GLuint program, const GameContext& gameContext, float currentTime);

	std::vector<VertexPosCol> m_Vertices;
	std::vector<GLuint> m_Indices;

	GLuint m_NumVerts;
	GLuint m_NumIndices;

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	GLuint m_MVPID;
	GLuint m_UniformTimeID;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
};

#endif//DRENDER_PRIMITIVES_HPP
