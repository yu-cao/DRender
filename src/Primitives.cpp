//
// Created by debyecao on 11/24/20.
//

#include "../include/Primitives.hpp"
#include "../include/FreeCamera.hpp"
#include "../include/GameContext.hpp"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

using namespace glm;

// CubePosCol
CubePosCol::CubePosCol()
{
}

void CubePosCol::Init(GLuint program, glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale = scale;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_Vertices), s_Vertices, GL_STATIC_DRAW);

	const int stride = VertexPosCol::stride;

	GLint posAttrib = glGetAttribLocation(program, "in_Position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, stride, 0);

	GLint colorAttrib = glGetAttribLocation(program, "in_Color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(VertexPosCol, col));

	m_UniformTimeID = glGetUniformLocation(program, "in_Time");
	m_MVPID = glGetUniformLocation(program, "in_MVP");

	glBindVertexArray(0);
}

CubePosCol::~CubePosCol()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void CubePosCol::Draw(GLuint program, const GameContext& gameContext, float currentTime)
{
	glBindVertexArray(m_VAO);

	glUniform1f(m_UniformTimeID, currentTime);

	glUseProgram(program);

	glm::mat4 Translation = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 Rotation = glm::mat4(m_Rotation);
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), m_Scale);
	glm::mat4 Model = Translation * Rotation * Scale;
	glm::mat4 MVP = gameContext.camera->GetViewProjection() * Model;
	glUniformMatrix4fv(m_MVPID, 1, GL_FALSE, &MVP[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTS);

	glBindVertexArray(0);
}

const VertexPosCol CubePosCol::s_Vertices[] =
	{
		// Front
		{ -1.0f, -1.0f, -1.0f, Color::RED },
		{ -1.0f,  1.0f, -1.0f, Color::LIME_GREEN },
		{ 1.0f,  1.0f, -1.0f, Color::ORANGE },

		{ -1.0f, -1.0f, -1.0f,	Color::RED },
		{ 1.0f,  1.0f, -1.0f, Color::ORANGE },
		{ 1.0f, -1.0f, -1.0f, Color::PINK },

		// Top
		{ -1.0f, 1.0f, -1.0f, Color::GREEN },
		{ -1.0f, 1.0f,  1.0f, Color::LIGHT_BLUE },
		{ 1.0f,  1.0f,  1.0f, Color::YELLOW },

		{ -1.0f, 1.0f, -1.0f, Color::GREEN },
		{ 1.0f,  1.0f,  1.0f, Color::YELLOW },
		{ 1.0f,  1.0f, -1.0f, Color::BLACK },

		// Back
		{ 1.0f, -1.0f, 1.0f, Color::BLACK },
		{ 1.0f,  1.0f, 1.0f, Color::DARK_GRAY },
		{ -1.0f,  1.0f, 1.0f, Color::LIGHT_GRAY },

		{ 1.0f, -1.0f, 1.0f, Color::BLACK },
		{ -1.0f, 1.0f, 1.0f, Color::LIGHT_GRAY },
		{ -1.0f, -1.0f, 1.0f, Color::WHITE },

		// Bottom
		{ -1.0f, -1.0f, -1.0f,	Color::BLUE },
		{ -1.0f, -1.0f,  1.0f,	Color::LIGHT_BLUE },
		{ 1.0f,  -1.0f,  1.0f,	Color::LIME_GREEN },

		{ -1.0f, -1.0f, -1.0f,	Color::BLUE },
		{ 1.0f, -1.0f,  1.0f, Color::LIME_GREEN },
		{ 1.0f, -1.0f, -1.0f, Color::YELLOW },

		// Right
		{ 1.0f, -1.0f, -1.0f, Color::PINK },
		{ 1.0f,  1.0f, -1.0f, Color::CYAN },
		{ 1.0f,  1.0f,  1.0f, Color::PURPLE },

		{ 1.0f, -1.0f, -1.0f, Color::PINK },
		{ 1.0f,  1.0f,  1.0f, Color::PURPLE },
		{ 1.0f, -1.0f,  1.0f, Color::BLUE },

		// Left
		{ -1.0f, -1.0f, -1.0f, Color::LIME_GREEN },
		{ -1.0f,  1.0f, -1.0f, Color::LIGHT_GRAY },
		{ -1.0f,  1.0f,  1.0f, Color::LIGHT_BLUE },

		{ -1.0f, -1.0f, -1.0f, Color::LIME_GREEN },
		{ -1.0f,  1.0f,  1.0f, Color::LIGHT_BLUE },
		{ -1.0f, -1.0f,  1.0f, Color::ORANGE },
	};

// SpherePosCol
SpherePosCol::SpherePosCol()
{
}

void SpherePosCol::Init(GLuint program, glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale = scale;

	GLuint parallelCount = 30;
	GLuint meridianCount = 30;

	assert(parallelCount > 0 && meridianCount > 0);

	const float PI = glm::pi<float>();
	const float TWO_PI = glm::two_pi<float>();

	// Vertices
	VertexPosCol v1 (0.0f, 1.0f, 0.0f, Color::BLACK);
	m_Vertices.push_back(v1);

	for (GLuint j = 0; j < parallelCount - 1; j++)
	{
		float polar = PI * float(j + 1) / (float)parallelCount;
		float sinP = sin(polar);
		float cosP = cos(polar);
		for (GLuint i = 0; i < meridianCount; i++)
		{
			float azimuth = TWO_PI * (float)i / (float)meridianCount;
			float sinA = sin(azimuth);
			float cosA = cos(azimuth);
			vec3 point(sinP * cosA, cosP, sinP * sinA);
			const float* color = (i % 2 == 0 ? j % 2 == 0 ? Color::ORANGE : Color::PURPLE : j % 2 == 0 ? Color::WHITE : Color::YELLOW);
			VertexPosCol vertex(point.x, point.y, point.z, color);
			m_Vertices.push_back(vertex);
		}
	}

	VertexPosCol vF(0.0f, -1.0f, 0.0f, Color::GRAY);
	m_Vertices.push_back(vF);

	m_NumVerts = m_Vertices.size();

	// Indices
	m_Indices.clear();

	// Top triangles
	for (size_t i = 0; i < meridianCount; i++)
	{
		GLuint a = i + 1;
		GLuint b = (i + 1) % meridianCount + 1;
		m_Indices.push_back(0);
		m_Indices.push_back(a);
		m_Indices.push_back(b);
	}

	// Center quads
	for (size_t j = 0; j < parallelCount - 2; j++)
	{
		GLuint aStart = j * meridianCount + 1;
		GLuint bStart = (j + 1) * meridianCount + 1;
		for (size_t i = 0; i < meridianCount; i++)
		{
			GLuint a = aStart + i;
			GLuint a1 = aStart + (i + 1) % meridianCount;
			GLuint b = bStart + i;
			GLuint b1 = bStart + (i + 1) % meridianCount;
			m_Indices.push_back(a);
			m_Indices.push_back(a1);
			m_Indices.push_back(b1);

			m_Indices.push_back(a);
			m_Indices.push_back(b1);
			m_Indices.push_back(b);
		}
	}

	// Bottom triangles
	for (size_t i = 0; i < meridianCount; i++)
	{
		GLuint a = i + meridianCount * (parallelCount - 2) + 1;
		GLuint b = (i + 1) % meridianCount + meridianCount * (parallelCount - 2) + 1;
		m_Indices.push_back(m_NumVerts - 1);
		m_Indices.push_back(a);
		m_Indices.push_back(b);
	}

	m_NumIndices = m_Indices.size();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices[0]) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices[0]) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);

	const int stride = VertexPosCol::stride;

	GLint posAttrib = glGetAttribLocation(program, "in_Position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, stride, 0);

	GLint colorAttrib = glGetAttribLocation(program, "in_Color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(VertexPosCol, col));

	m_UniformTimeID = glGetUniformLocation(program, "in_Time");
	m_MVPID = glGetUniformLocation(program, "in_MVP");

	glBindVertexArray(0);
}

SpherePosCol::~SpherePosCol()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void SpherePosCol::Draw(GLuint program, const GameContext& gameContext, float currentTime)
{
	glBindVertexArray(m_VAO);

	glUniform1f(m_UniformTimeID, currentTime);

	glUseProgram(program);

	glm::mat4 Translation = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 Rotation = glm::mat4(m_Rotation);
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), m_Scale);
	glm::mat4 Model = Translation * Rotation * Scale;
	glm::mat4 MVP = gameContext.camera->GetViewProjection() * Model;
	glUniformMatrix4fv(m_MVPID, 1, GL_FALSE, &MVP[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, (GLuint*)0);

	glBindVertexArray(0);
}