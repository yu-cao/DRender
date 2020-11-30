//
// Created by debyecao on 11/29/20.
//

#ifndef DRENDER_STDAFX_HPP
#define DRENDER_STDAFX_HPP


#define COMPILE_OPEN_GL 0
#define COMPILE_VULKAN 1

#if COMPILE_VULKAN
	#include "glad/glad.h"
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>

	#include "Graphics/VulkanRenderer.hpp"
	#include "Window/VulkanWindowWrapper.hpp"
#endif

#if COMPILE_OPEN_GL
	#include <glad/glad.h>
	#define GLFW_INCLUDE_NONE
	#include <GLFW/glfw3.h>

	#include "Graphics/GLRenderer.hpp"
	#include "Window/GLWindowWrapper.hpp"
#endif

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>


#endif//DRENDER_STDAFX_HPP
