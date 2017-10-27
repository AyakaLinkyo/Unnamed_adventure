#pragma once
#include <Keyboard.h>
#include <d3d11.h>


class GameBase;

class GameMain
{
public:
	GameMain();
	~GameMain();
	//ƒV[ƒ“‚ğ•ÏX‚·‚é
	void Scene(GameBase* nextScene);
	void Update();

	void Render();
	
private:
	GameBase* m_base;

};

class GameBase
{
protected:
	int m_TimeCnt = 0;
	int m_NextScene = 0;

public:
	virtual ~GameBase() {}
	virtual void Initialize() = 0;
	virtual void UpdateGame(GameMain* main) = 0;
	virtual void RenderGame() = 0;
	int m_scene = 0;

};


