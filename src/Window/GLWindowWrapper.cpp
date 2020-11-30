//
// Created by debyecao on 11/29/20.
//
#include "stdafx.hpp"

#include "Window/GLWindowWrapper.hpp"
#include "Logger.hpp"
#include "ShaderUtils.hpp"

GLWindowWrapper::GLWindowWrapper(std::string title, glm::tvec2<int> size, GameContext& gameContext) :
	GLFWWindowWrapper(title, size, gameContext)
{
	glfwSetErrorCallback(GLFWErrorCallback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// Call before window creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL:
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// Vulkan:
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_Window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowUserPointer(m_Window, this);

	glfwSetKeyCallback(m_Window, GLFWKeyCallback);
	glfwSetMouseButtonCallback(m_Window, GLFWMouseButtonCallback);
	glfwSetCursorPosCallback(m_Window, GLFWCursorPosCallback);
	glfwSetWindowSizeCallback(m_Window, GLFWWindowSizeCallback);
	glfwSetWindowFocusCallback(m_Window, GLFWWindowFocusCallback);

	glfwFocusWindow(m_Window);
	m_HasFocus = true;

	glfwMakeContextCurrent(m_Window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	const std::string glVersion(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	Logger::LogInfo("OpenGL Version: " + glVersion);

	gameContext.program = ShaderUtils::LoadShaders("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");

	//icons[0] = LoadGLFWImage("resources/icons/icon_01_48.png");
	//icons[1] = LoadGLFWImage("resources/icons/icon_01_32.png");
	//icons[2] = LoadGLFWImage("resources/icons/icon_01_16.png");
	//
	//glfwSetWindowIcon(m_Window, NUM_ICONS, icons);
	//
	//SOIL_free_image_data(icons[0].pixels);
	//SOIL_free_image_data(icons[1].pixels);
	//SOIL_free_image_data(icons[2].pixels);
}

GLWindowWrapper::~GLWindowWrapper()
{
}

void GLWindowWrapper::SetSize(int width, int height)
{
	m_Size = glm::tvec2<int>(width, height);
	glViewport(0, 0, width, height);
}