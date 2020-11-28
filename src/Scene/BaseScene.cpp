//
// Created by debyecao on 11/25/20.
//

#include "Scene/BaseScene.hpp"
#include "Logger.hpp"

using namespace glm;

BaseScene::BaseScene(std::string name) : m_Name(name)
{
}

BaseScene::~BaseScene()
{
	delete m_Camera;
}

std::string BaseScene::GetName() const
{
	return m_Name;
}