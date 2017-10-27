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
	void UpdateGame(GameMain* main);	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��
	static void Dispose();

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



};

