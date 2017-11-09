#pragma once
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include "..\\Camera\Camera.h"
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include <Keyboard.h>
#include <vector>
#include "..\\Model\Obj3d.h"

#include "..\\Collision\Collision.h"
#include "..\\Collision\CollisionNode.h"

class Player 
{
public:
	static float GRAVITY;

	// 1�t���[���ł̊p�x�ω�����<�x�����W�A��>
	static const float ANGLE_DELTA_MAX;

	//���@�p�[�c
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,

		PLAYER_PARTS_NUM,
	};

	//�v���C���[�̓���������
	enum PLAYER_MOVE
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};


	Player();
	~Player();

	void Init();
	void Update();
	void Render();
	void Colc();

	void Up();
	void Down();
	void Left();
	void Right();
	void LeftRotation();
	void RightRotation();
	
	void Jumping();
	void Jump();

	//�X�P�[�����O�iXYZ)
	DirectX::SimpleMath::Vector3 Get_scale();
	//��]�p(XYZ�j
	float Get_rotate();
	//���s�ړ��iXYZ�j
	DirectX::SimpleMath::Vector3 Get_transmat();

	DirectX::SimpleMath::Matrix Get_world();

	void SetTrans(DirectX::SimpleMath::Vector3 vec) { m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec); m_sphereN.SetTrans(vec); }

	// �W�����v�̑傫����ݒ�
	void SetJump(float spd) { m_jumping = spd; }
	// �W�����v�̑傫�����擾
	float GetJump() { return m_jumping; }
	// �W�����v���Ă��邩���擾
	bool isJump() { return m_jump; }
	// �W�����v���Ă��邩��ς���
	void JumpChange(bool is) { m_jump = is; }
	//�����蔻��m�[�h�̎擾
	SphereNode& GetSphere();

	void StopMove();
	DirectX::SimpleMath::Vector2 GetSpdW() { return m_SpdWalk; }

private:
	DirectX::SimpleMath::Vector2 m_SpdWalk;

	bool m_jump;			//�W�����v�t���O
	float m_jumping;			//�����x�N�g���̏�����

	DirectX::SimpleMath::Vector3 m_vec;

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// ���̂����蔻��m�[�h
	SphereNode m_sphereN;

	std::vector<Obj3d> m_ObjPlayer;

	// �������
	int m_moveType;

};

