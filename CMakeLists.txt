cmake_minimum_required(VERSION 3.17)
project(DRender)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include)
set(GLM_H /usr/local/Cellar/glm/0.9.9.8/include)
set(VULKAN_H /usr/local/Cellar/vulkan-headers/1.2.162/include)
set(UTILITY ./util)
set(INCLUDE ./include)
set(RES ./resources)

include_directories(${GLFW_H} ${GLM_H}
        ${VULKAN_H}
        ${UTILITY} ${INCLUDE} ${RES})

# 添加目标链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.3.dylib)
set(MOLTEN_VK_LINK /Users/debyecao/vulkansdk-macos-1.2.154.0/macOS/lib/libMoltenVK.dylib)
set(SOIL /Users/debyecao/GitHub/DRender/util/SOIL/libSOIL.a)
link_libraries(${OPENGL} ${GLFW_LINK} ${MOLTEN_VK_LINK} ${SOIL})

set(SOURCE_FILES
        src/main.cpp
        include/TechDemo.hpp src/TechDemo.cpp
        include/ShaderUtils.hpp src/ShaderUtils.cpp
        include/Vertex.hpp
        util/glad/glad.c
        util/Random/Random.cpp util/Random/Random.hpp
        src/Logger.cpp include/Logger.hpp
        src/Colors.cpp include/Colors.hpp
        src/FreeCamera.cpp include/FreeCamera.hpp
        include/GameContext.hpp
        include/InputManager.hpp src/InputManager.cpp
        util/Helpers/Helpers.cpp util/Helpers/Helpers.hpp
        include/Graphics/Renderer.hpp src/Graphics/Renderer.cpp
        include/Graphics/GLRenderer.hpp src/Graphics/GLRenderer.cpp
        include/GLHelpers.hpp
        include/Scene/BaseScene.hpp src/Scene/BaseScene.cpp
        include/Scene/SceneManager.hpp src/Scene/SceneManager.cpp
        include/Scene/TestScene.hpp src/Scene/TestScene.cpp
        include/Window/Window.hpp src/Window/Window.cpp
        include/Window/GLFWWindowWrapper.hpp src/Window/GLFWWindowWrapper.cpp
        include/Prefabs/CubePosCol.hpp src/Prefabs/CubePosCol.cpp
        include/Prefabs/SpherePosCol.hpp src/Prefabs/SpherePosCol.cpp
        include/stdafx.hpp
        src/Window/GLWindowWrapper.cpp include/Window/GLWindowWrapper.hpp
        src/Window/VulkanWindowWrapper.cpp include/Window/VulkanWindowWrapper.hpp
        src/Graphics/VulkanRenderer.cpp include/Graphics/VulkanRenderer.hpp
        util/tiny_obj_loader/tiny_obj_loader.h)

add_executable(DRender ${SOURCE_FILES})

if (APPLE)
    target_link_libraries(DRender "-framework OpenGL")
    target_link_libraries(DRender "-framework Cocoa")
    target_link_libraries(DRender /Users/debyecao/vulkansdk-macos-1.2.154.0/macOS/Frameworks/vulkan.framework)
endif()