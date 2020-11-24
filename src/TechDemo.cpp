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
#include <glm/gtx/euler_angles.hpp> // rotation

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

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}

void WindowFocusCallback(GLFWwindow* window, int focused)
{
	TechDemo* techDemo = static_cast<TechDemo*>(glfwGetWindowUserPointer(window));
	techDemo->UpdateWindowFocused(focused);
}

void CursorPosCallback(GLFWwindow* window, double x, double y)
{
	TechDemo* techDemo = static_cast<TechDemo*>(glfwGetWindowUserPointer(window));
	techDemo->SetMousePosition((float)x, (float)y);
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	TechDemo* techDemo = static_cast<TechDemo*>(glfwGetWindowUserPointer(window));
	techDemo->UpdateWindowSize(width, height);
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

	m_WindowSize = vec2(1920, 1080);
	m_ZNear = 0.1f;
	m_ZFar = 1000.0f;
	m_FOV = 45.0f;

	m_Window = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, "Window Title", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowUserPointer(m_Window, this);

	glfwSetKeyCallback(m_Window, KeyCallback);
	glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
	glfwSetCursorPosCallback(m_Window, CursorPosCallback);
	glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
	glfwSetWindowFocusCallback(m_Window, WindowFocusCallback);

	glfwFocusWindow(m_Window);
	m_WindowFocused = true;

	glfwMakeContextCurrent(m_Window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	Logger::LogInfo("OpenGL Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

	icons[0] = LoadGLFWImage("../resources/icons/icon_01_48.png");
	icons[1] = LoadGLFWImage("../resources/icons/icon_01_32.png");
	icons[2] = LoadGLFWImage("../resources/icons/icon_01_16.png");

	glfwSetWindowIcon(m_Window, NUM_ICONS, icons);

	glClearColor(0.05f, 0.1f, 0.25f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	m_ProgramID = ShaderUtils::LoadShaders("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");

	glUseProgram(m_ProgramID);

	m_Cube.Init(m_ProgramID, vec3(0.0f, 0.0f, 0.0f), glm::quat(vec3(0.0f, 1.0f, 0.0f)), vec3(3.0f, 1.0f, 1.0f));
	m_Cube2.Init(m_ProgramID, vec3(0.0f, 0.0f, 4.0f), glm::quat(vec3(0.0f, 0.0f, 2.0f)), vec3(1.0f, 5.0f, 1.0f));
	//m_Sphere1.Init(m_ProgramID, Sphere::Type::STANDARD, 2.0f, 20, 20, vec3(0.0f, 8.0f, 0.0f));

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

		CalculateViewProjection(dt);

		m_Cube.Draw(m_ProgramID, m_ViewProjection, currentTime);
		m_Cube2.Draw(m_ProgramID, m_ViewProjection, currentTime);
		//m_Sphere1.Draw(m_ProgramID, m_ViewProjection, currentTime);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

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

glm::mat4 TechDemo::GetViewProjection() const
{
	return m_ViewProjection;
}

void TechDemo::SetMousePosition(float x, float y)
{
	SetMousePosition(vec2(x, y));
}

void TechDemo::SetMousePosition(glm::vec2 mousePos)
{
	m_MousePos = mousePos;
}

void TechDemo::UpdateWindowSize(int width, int height)
{
	UpdateWindowSize(vec2(width, height));
}

void TechDemo::UpdateWindowSize(glm::tvec2<int> windowSize)
{
	m_WindowSize = windowSize;
	glViewport(0, 0, windowSize.x, windowSize.y);
}

void TechDemo::UpdateWindowFocused(int focused)
{
	m_WindowFocused = focused == GLFW_TRUE;
}

void TechDemo::CalculateViewProjection(float dt)
{
	static float currentTime = 0.0f;

	float aspectRatio = m_WindowSize.x / (float)m_WindowSize.y;
	glm::mat4 Projection = glm::perspective(m_FOV, aspectRatio, m_ZNear, m_ZFar);

	bool move = m_WindowFocused;
	if (move) currentTime += dt;

	vec3 eye = glm::vec3(8 + (cos(currentTime) * 4.0f), 3.5f, sin(currentTime) * 3.0f);

	vec3 center = glm::vec3(0, 0, 0);
	vec3 up = glm::vec3(0, 1, 0);

	glm::mat4 View = glm::lookAt(
		eye, center, up
	);
	m_ViewProjection = Projection * View;
}