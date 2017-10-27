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
	void UpdateGame(GameMain* main);	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��
	static void Dispose();

private:
	static GameBase* m_base;

};
