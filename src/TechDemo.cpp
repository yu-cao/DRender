//
// Created by debyecao on 11/24/20.
//
#include "../include/TechDemo.h"
#include "../include/ShaderUtils.h"
#include "../include/Logger.h"

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp> // vec3, vec3, mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotation, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "../util/SOIL/SOIL.h"

#define ArrayCount(arr) (sizeof(arr[0]) / sizeof(arr))

using namespace glm;

void ErrorCallback(int error, const char* description)
{
	Logger::LogError("GL Error: " + std::string(description));
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

// TODO: Consolidate these two functions?
mat4 Transform(const vec2& Orientation, const vec3& Position, const vec3& Up)
{
	mat4 Proj = perspective(radians(45.f), 1.33f, 0.1f, 10.f);
	mat4 ViewTranslate = translate(mat4(1.f), Position);
	mat4 ViewRotateX = rotate(ViewTranslate, Orientation.y, Up);
	mat4 View = rotate(ViewRotateX, Orientation.x, Up);
	mat4 Model = mat4(1.0f);

	return Proj * View * Model;
}

void SetUniformMVP(GLuint Location, const vec3& Position, const vec3& Rotation)
{
	float FOV = 45.0f;
	float aspect = 16.0f / 9.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
	mat4 Projection = perspective(FOV, aspect, zNear, zFar);

	float Scale = 0.5f;

	mat4 ViewTranslate = translate(mat4(1.0f), Position);
	mat4 ViewRotateX = rotate(ViewTranslate, Rotation.y, vec3(-1.0f, 0.0f, 0.0f));
	mat4 View = rotate(ViewRotateX, Rotation.x, vec3(0.0f, 1.0f, 0.0f));
	mat4 Model = scale(mat4(1.0f), vec3(Scale));
	mat4 MVP = Projection * View * Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, value_ptr(MVP));
}

vec3 ComputeNormal(const vec3& a, const vec3& b, const vec3& c)
{
	return normalize(cross(c - a, b - a));
}

TechDemo::TechDemo()
{
}

TechDemo::~TechDemo()
{
	glDeleteProgram(m_ProgramID);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_VertexBufferID);
	glDeleteVertexArrays(1, &m_VertexArrayID);
	glDeleteBuffers(1, &m_ColorBufferID);
	glDeleteBuffers(1, &m_TexCoordBufferID);
	glBindVertexArray(0);

	glfwDestroyWindow(m_Window);

	SOIL_free_image_data(icons[0].pixels);
	SOIL_free_image_data(icons[1].pixels);
	SOIL_free_image_data(icons[2].pixels);

	glfwTerminate();
}

void LoadGLTexture(const std::string filename)
{
	int width, height;
	unsigned char* imageData = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	SOIL_free_image_data(imageData);
}

// Attempts to load image at "filename" into an OpenGL texture
// If repeats, texture wrapping will be set to repeat, otherwise to clamp
// returns the OpenGL texture handle, or 0 on fail
void LoadAndBindGLTexture(const std::string filename, GLuint& textureHandle,
                          int sWrap = GL_REPEAT, int tWrap = GL_REPEAT, int minFilter = GL_LINEAR, int magFilter = GL_LINEAR)
{
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	LoadGLTexture(filename);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

// NOTE: This uses SOIL's automatic texture creation - which is outdated apparently
//GLuint LoadGLTexture(const std::string filename, bool repeats, bool generateMipmaps)
//{
//	GLuint loadFlags = 0;
//	if (generateMipmaps)
//	{
//		loadFlags |= SOIL_FLAG_MIPMAPS;
//	}
//	if (repeats)
//	{
//		loadFlags |= SOIL_FLAG_TEXTURE_REPEATS;
//	}
//	GLuint result = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, loadFlags);
//
//	if (result == 0)
//	{
//		std::cout << "SOIL loading error: " << SOIL_last_result() << std::endl;
//		std::cout << "image filepath: " << filename << std::endl;
//		return result;
//	}
//
//	return result;
//}

GLFWimage LoadGLFWImage(const std::string filename)
{
	GLFWimage result = {};

	int channels;
	unsigned char* data = SOIL_load_image(filename.c_str(), &result.width, &result.height, &channels, SOIL_LOAD_AUTO);

	if (data == 0)
	{
		Logger::LogError("SOIL loading error: " + std::string(SOIL_last_result()) + "\nimage filepath: " + filename);
		return result;
	}
	else
	{
		result.pixels = static_cast<unsigned char*>(data);
	}

	return result;
}

void TechDemo::Initialize()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// Call before window creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	m_Window = glfwCreateWindow(1920, 1080, "Window title", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(m_Window, KeyCallback);

	glfwMakeContextCurrent(m_Window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	Logger::LogInfo("OpenGL Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

	icons[0] = LoadGLFWImage("../resources/icons/icon_01_48.png");
	icons[1] = LoadGLFWImage("../resources/icons/icon_01_32.png");
	icons[2] = LoadGLFWImage("../resources/icons/icon_01_16.png");

	glfwSetWindowIcon(m_Window, NUM_ICONS, icons);

	glClearColor(0.05f, 0.1f, 0.45f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	static const GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  -1.0f, -1.0f,
	};

//	static GLfloat colors[12 * 3 * 3];
//	for (size_t i = 0; i < 12 * 3; i++)
//	{
//		colors[i * 3 + 0] = 1.0f;
//		colors[i * 3 + 1] = 1.0f;
//		colors[i * 3 + 2] = 1.0f;
//	}

	static const GLfloat texCoords[] =
		{
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 1.0f
		};

	m_ProgramID = ShaderUtils::LoadShaders("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");

	glUseProgram(m_ProgramID);

	// Vertex buffer object
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLint posAttrib = glGetAttribLocation(m_ProgramID, "in_Position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

//	glGenBuffers(1, &m_ColorBufferID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferID);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//	GLint colorAttrib = glGetAttribLocation(m_ProgramID, "in_Color");
//	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(colorAttrib);

	glGenBuffers(1, &m_TexCoordBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	GLint texCoordAttrib = glGetAttribLocation(m_ProgramID, "in_TexCoord");
	glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordAttrib);

	LoadAndBindGLTexture("../resources/images/test2.jpg", m_TextureID);
	glUniform1i(glGetUniformLocation(m_ProgramID, "texTest"), 0);

	m_UniformTimeID = glGetUniformLocation(m_ProgramID, "time");

	m_MVPID = glGetUniformLocation(m_ProgramID, "MVP");

	SetVSyncEnabled(true);
}

void TechDemo::UpdateAndRender()
{
	float secondsElapsedThisFrame = 0.0f;
	float prevTime = (float)glfwGetTime();
	while (!glfwWindowShouldClose(m_Window))
	{
		float currentTime = (float)glfwGetTime();
		float dt = currentTime - prevTime;
		prevTime = currentTime;
		if (dt < 0.0f) dt = 0.0f;

		++m_FramesThisSecond;
		secondsElapsedThisFrame += dt;
		if (secondsElapsedThisFrame >= 1.0f)
		{
			secondsElapsedThisFrame -= 1.0f;
			m_FPS = m_FramesThisSecond;
			m_FramesThisSecond = 0;
			glfwSetWindowTitle(m_Window, (std::string("Window Title    FPS:") + std::to_string(m_FPS)).c_str());
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(m_ProgramID);

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		float FOV = 45.0f;
		float aspectRatio = viewport[0] / float(viewport[1]);
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		glm::mat4 View = glm::lookAt(
			glm::vec3(-5, -5, 10),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);

		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;
		glUniformMatrix4fv(m_MVPID, 1, GL_FALSE, &MVP[0][0]);

		glUniform1f(m_UniformTimeID, currentTime);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void TechDemo::SetVSyncEnabled(bool enabled)
{
	m_VSyncEnabled = enabled;
	glfwSwapInterval(m_VSyncEnabled ? 1 : 0);
}

void TechDemo::ToggleVSyncEnabled()
{
	SetVSyncEnabled(!m_VSyncEnabled);
}