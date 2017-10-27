#include "pch.h"
#include "GameTitle.h"
#include "GamePlay.h"

#include <d3d11.h>
#include "SimpleMath.h"
#include "Key.h"
#include "Resources\Music\CueSheet_0.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameBase* GameTitle::m_base = NULL;

GameBase * GameTitle::GetInstance()
{
	m_base = new GameTitle();

	return m_base;
}


GameTitle::GameTitle()
{
	this->Initialize();

}


GameTitle::~GameTitle()
{
	//	�T�E���h���C�u�����̏I������
	//ADX2Le::Finalize();

}

void GameTitle::Initialize()
{
	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le::Initialize("Resources/Music/Archer.acf");
	ADX2Le::LoadAcb("Resources/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");
	//	�T�E���h�Đ�
	ADX2Le::Play(CRI_CUESHEET_0_TITLE);

}

void GameTitle::UpdateGame(GameMain* main)
{
	//	�T�E���h�̍X�V
	ADX2Le::Update();

	Key& key = Key::GetInstance();
	auto kb = key.m_keyboard->GetState();

	key.Update();

	if (kb.IsKeyDown(DirectX::Keyboard::Enter))
	{
		//	���ʉ�
		ADX2Le::Play(CRI_CUESHEET_0_TOPLAY);

		main->Scene(GamePlay::GetInstance());
	}
	if (kb.Escape)
	{
		//	�T�E���h���C�u�����̏I������
		ADX2Le::Finalize();

		exit(1);
	}


}

void GameTitle::RenderGame()
{
	Draw& draw = Draw::GetInstance();

	draw.Render(L"Resources/title.png", Vector2(800 / 2, 600 / 2));
	//draw.RenderFont(L"Title");
}

void GameTitle::Dispose()
{
	if (m_base != NULL)
	{
		delete m_base;
	}
}
