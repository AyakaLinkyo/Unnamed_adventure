#pragma once
#include "GameMain.h"
#include "Draw.h"

#include "ADX2Le.h"


class GameResult :
	public GameBase
{
public:
	static GameBase* GetInstance();
	GameResult();

	~GameResult();
	void Initialize();
	void UpdateGame(GameMain* main);	//	データの更新
	void RenderGame();	//	描画する
	static void Dispose();

private:
	static GameBase* m_base;

};
