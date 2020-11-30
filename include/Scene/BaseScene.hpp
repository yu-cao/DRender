//
// Created by debyecao on 11/25/20.
//

#ifndef DRENDER_BASESCENE_HPP
#define DRENDER_BASESCENE_HPP

#include "FreeCamera.hpp"
#include "GameContext.hpp"

#include <string>

class BaseScene
{
public:
	BaseScene(std::string name);
	virtual ~BaseScene();

	virtual void Destroy(const GameContext& gameContext) = 0;

	virtual void UpdateAndRender(const GameContext& gameContext) = 0;

	std::string GetName() const;

private:
	std::string m_Name;
	FreeCamera* m_Camera;

	BaseScene(const BaseScene&) = delete;
	BaseScene& operator=(const BaseScene&) = delete;
};

#endif//DRENDER_BASESCENE_HPP
