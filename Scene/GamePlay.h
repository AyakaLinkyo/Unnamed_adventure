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

	//�t���A�p
	const static int FLOOR_SCALE_X = 47;
	const static int FLOOR_SCALE_Z = 47;
	//�ʘH
	const static int PASSEGE_SCALE_X = 24;
	const static int PASSEGE_SCALE_Z = 24;


	static GameBase* GetInstance();
	GamePlay();

	~GamePlay();
	void Initialize();
	void UpdateGame(GameMain* main);	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��
	static void Dispose();

	//�ǂ̈ʒu
	void WallInitialize();

private:
	static GameBase* m_base;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//�n�ʃ��f��
	Obj3d m_obj_ground;
	//�V�����f��
	Obj3d m_obj_skydome;
	//�����f��
	std::unique_ptr<DirectX::Model> m_ball_model;

	int	enemyNum = 5;
	int timeCnt;
	int endCnt;
	int m_remain_enemy;		//�c��̓G�̐�
	int targetNum;
	std::unique_ptr<Player>m_player;

	//�J����
	std::unique_ptr<FollowCamera> m_Camera;
	//�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_factory;

	//��
	Obj3d m_wall[WALL_NUM];
	BoxNode m_wallNode[WALL_NUM];

	Door m_door[Door::NUM::MAX];
	//BoxNode m_openNode;


	//�A�C�e��
	std::unique_ptr<Item> m_StageItem[2];
	ItemFactory* m_item_factory;

	//�X�C�b�`�i�Q�j
	Switch m_switch[Switch::NUM::MAX];

};

