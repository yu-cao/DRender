//
// Created by debyecao on 11/25/20.
//

#ifndef DRENDER_SCENEMANAGER_HPP
#define DRENDER_SCENEMANAGER_HPP

#include <vector>

class BaseScene;
struct GameContext;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void UpdateAndRender(const GameContext& gameContext);

	void AddScene(BaseScene* newScene);
	void RemoveScene(BaseScene* scene);

	void SetCurrentScene(int sceneIndex);
	void SetCurrentScene(std::string sceneName);

	BaseScene* CurrentScene() const;

	void Destroy(const GameContext& gameContext);

private:
	int m_CurrentSceneIndex;
	std::vector<BaseScene*> m_Scenes;

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
};

#endif//DRENDER_SCENEMANAGER_HPP
