#pragma once
#include "GameMain.h"
#include "Draw.h"
#include "ADX2Le.h"


class GameTitle :
	public GameBase
{
public:
	static GameBase* GetInstance();
	GameTitle();

	~GameTitle();
	void Initialize();
	void UpdateGame(GameMain* main);	//	データの更新
	void RenderGame();	//	描画する
	static void Dispose();

private:
	static GameBase* m_base;

};
