cmake_minimum_required(VERSION 3.17)
project(DRender)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include)
set(GLM_H /usr/local/Cellar/glm/0.9.9.8/include)

include_directories(${GLFW_H} ${GLM_H})

# 添加目标链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.3.dylib)
set(SOIL /Users/debyecao/GitHub/DRender/util/SOIL/libSOIL.a)
link_libraries(${OPENGL} ${GLFW_LINK} ${SOIL})

set(SOURCE_FILES
        src/main.cpp
        include/TechDemo.hpp
        include/ShaderUtils.hpp
        src/Primitives.cpp include/Primitives.hpp
        src/ShaderUtils.cpp
        src/TechDemo.cpp
        util/glad/glad.c
        util/Random/Random.cpp util/Random/Random.h
        src/Logger.cpp include/Logger.hpp
        src/Colors.cpp include/Colors.hpp
        src/FreeCamera.cpp include/FreeCamera.hpp
        include/GameContext.hpp
        include/InputManager.hpp src/InputManager.cpp)
add_executable(DRender ${SOURCE_FILES})

if (APPLE)
    target_link_libraries(DRender "-framework OpenGL")
    target_link_libraries(DRender "-framework Cocoa")
endif()