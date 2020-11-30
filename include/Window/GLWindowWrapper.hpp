//
// Created by debyecao on 11/29/20.
//

#ifndef DRENDER_GLWINDOWWRAPPER_HPP
#define DRENDER_GLWINDOWWRAPPER_HPP

#include "GLFWWindowWrapper.hpp"

struct GameContext;

class GLWindowWrapper : public GLFWWindowWrapper
{
public:
	GLWindowWrapper(std::string title, glm::tvec2<int> size, GameContext& gameContext);
	virtual ~GLWindowWrapper();

	virtual void SetSize(int width, int height) override;

private:
	GLWindowWrapper(const GLWindowWrapper&) = delete;
	GLWindowWrapper& operator=(const GLWindowWrapper&) = delete;
};

#endif//DRENDER_GLWINDOWWRAPPER_HPP
