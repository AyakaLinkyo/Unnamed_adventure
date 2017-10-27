#include "..\\pch.h"
#include "GameMain.h"


GameMain::GameMain()
{
	m_base = nullptr;
}


GameMain::~GameMain()
{
}

void GameMain::Scene(GameBase* nextScene)
{
	// ���݂̃X�e�[�g��j������
	if (m_base != nullptr) delete m_base;

	m_base = nextScene;
}

void GameMain::Update()
{
	m_base->UpdateGame(this);
}

void GameMain::Render()
{
	m_base->RenderGame();
}

