#pragma once
#include "GameMain.h"
#include "..\\Singleton\Draw.h"

#include "..\\Camera\Camera.h"
#include "..\\Camera\FollowCamera.h"
#include "..\\Model\Obj3d.h"
#include "..\\Charactor\Player.h"
#include "..\\Model\ModelEffect.h"
#include <SimpleMath.h>
#include <d3d11_1.h>




class GamePlay :
	public GameBase
{
public:
	static GameBase* GetInstance();
	GamePlay();

	~GamePlay();
	void Initialize();
	void UpdateGame(GameMain* main);	//	データの更新
	void RenderGame();	//	描画する
	static void Dispose();

private:
	static GameBase* m_base;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//地面モデル
	Obj3d m_obj_ground;
	//天球モデル
	Obj3d m_obj_skydome;
	//球モデル
	std::unique_ptr<DirectX::Model> m_ball_model;

	int	enemyNum = 5;
	int timeCnt;
	int endCnt;
	int m_remain_enemy;		//残りの敵の数
	int targetNum;
	std::unique_ptr<Player>m_player;

	//カメラ
	std::unique_ptr<FollowCamera> m_Camera;
	//エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_factory;



};

