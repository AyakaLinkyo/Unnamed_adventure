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
	void UpdateGame(GameMain* main);	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��
	static void Dispose();

private:
	static GameBase* m_base;

};
