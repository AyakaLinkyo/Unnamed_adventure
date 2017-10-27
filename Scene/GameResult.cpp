#include "pch.h"
#include "GameResult.h"
#include "GameTitle.h"

#include <d3d11.h>
#include "SimpleMath.h"
#include "Key.h"
#include "Score.h"
#include "Timer.h"

#include "Resources\Music\CueSheet_0.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

GameBase* GameResult::m_base = NULL;

GameBase * GameResult::GetInstance()
{
	m_base = new GameResult();

	return m_base;
}


GameResult::GameResult()
{
	this->Initialize();
}


GameResult::~GameResult()
{

}

void GameResult::Initialize()
{
	//描画関数設定
	Draw& draw = Draw::GetInstance();

	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resources/Music/Archer.acf");
	ADX2Le::LoadAcb("Resources/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	効果音
	ADX2Le::Play(CRI_CUESHEET_0_TORESULT);

	//	サウンド再生
	ADX2Le::Play(CRI_CUESHEET_0_RESULT);

}

void GameResult::UpdateGame(GameMain* main)
{
	ADX2Le::Update();
	Score& score = Score::GetInstance();
	Timer& time = Timer::GetInstance();

	Key& key = Key::GetInstance();
	auto kb = key.m_keyboard->GetState();

	key.Update();
	if (kb.Escape)
	{
		//	サウンドライブラリの終了処理
		ADX2Le::Finalize();

		exit(1);
	}

	if (kb.IsKeyDown(DirectX::Keyboard::Space))
	{
		time.ResetTime();
		score.ResetScore();
		main->Scene(GameTitle::GetInstance());
	}


}

void GameResult::RenderGame()
{
	Draw& draw = Draw::GetInstance();
	
	draw.Render(L"Resources/result.png", Vector2(800 / 2, 600 / 2));
	//draw.RenderFont(L"Result");
	//スコアの描画
	Score& score = Score::GetInstance();
	score.Render(Vector2(400, 300));
}

void GameResult::Dispose()
{
	if (m_base != NULL)
	{
		delete m_base;
	}
}
