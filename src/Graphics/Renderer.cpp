//
// Created by debyecao on 11/25/20.
//
#include "stdafx.hpp"

#include "Graphics/Renderer.hpp"
#include "GameContext.hpp"

Renderer::Renderer(GameContext &gameContext)
{
	gameContext.renderer = this;
}

Renderer::~Renderer()
{

}