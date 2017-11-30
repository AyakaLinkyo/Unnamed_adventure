#pragma once
#include "GameMain.h"
#include "..\\Singleton\Draw.h"

#include "..\\Camera\Camera.h"
#include "..\\Camera\FollowCamera.h"
#include "..\\Model\Obj3d.h"
#include "..\\Charactor\Player.h"
#include "..\\Model\ModelEffect.h"

#include "..\Item\Item.h"
#include "..\Item\ItemFactory.h"

#include "..\Switch\Switch.h"

#include "..\Door\Door.h"

#include <SimpleMath.h>
#include <d3d11_1.h>




class GamePlay :
	public GameBase
{
public:
	const static int WALL_NUM = 23;

	//フロア用
	const static int FLOOR_SCALE_X = 47;
	const static int FLOOR_SCALE_Z = 47;
	//通路
	const static int PASSEGE_SCALE_X = 24;
	const static int PASSEGE_SCALE_Z = 24;


	static GameBase* GetInstance();
	GamePlay();

	~GamePlay();
	void Initialize();
	void UpdateGame(GameMain* main);	//	データの更新
	void RenderGame();	//	描画する
	static void Dispose();

	//壁の位置
	void WallInitialize();

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

	//壁
	Obj3d m_wall[WALL_NUM];
	BoxNode m_wallNode[WALL_NUM];

	Door m_door[Door::NUM::MAX];
	//BoxNode m_openNode;


	//アイテム
	std::unique_ptr<Item> m_StageItem[2];
	ItemFactory* m_item_factory;

	//スイッチ（２つ）
	Switch m_switch[Switch::NUM::MAX];

};

