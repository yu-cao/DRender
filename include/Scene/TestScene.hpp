//
// Created by debyecao on 11/25/20.
//

#ifndef DRENDER_TESTSCENE_HPP
#define DRENDER_TESTSCENE_HPP

#include "BaseScene.hpp"
#include "Primitives.hpp"

class TestScene : public BaseScene
{
public:
	TestScene(const GameContext& gameContext);
	virtual ~TestScene();

	void UpdateAndRender(const GameContext& gameContext) override;

private:
	CubePosCol m_Cube;
	CubePosCol m_Cube2;
	SpherePosCol m_Sphere1;

	TestScene(const TestScene&) = delete;
	TestScene& operator=(const TestScene&) = delete;
};

#endif//DRENDER_TESTSCENE_HPP
