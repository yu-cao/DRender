//
// Created by debyecao on 11/29/20.
//

#ifndef DRENDER_VULKANWINDOWWRAPPER_HPP
#define DRENDER_VULKANWINDOWWRAPPER_HPP

#define GLFW_INCLUDE_VULKAN
#include "GLFWWindowWrapper.hpp"

struct GameContext;

class VulkanWindowWrapper : public GLFWWindowWrapper
{
public:
	VulkanWindowWrapper(std::string title, glm::tvec2<int> size, GameContext& gameContext);
	virtual ~VulkanWindowWrapper();

	virtual void SetSize(int width, int height) override;

private:
	virtual void WindowSizeCallback(int width, int height) override;
	VulkanWindowWrapper(const VulkanWindowWrapper&) = delete;
	VulkanWindowWrapper& operator=(const VulkanWindowWrapper&) = delete;
};
#endif//DRENDER_VULKANWINDOWWRAPPER_HPP
