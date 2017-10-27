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

	//ID
	enum PLAYER_SHAPE
	{
		CUPSULE,
		SPHERE,
		CUBE,
	};

	Player(DirectX::Keyboard* keyboard);
	~Player();

	void Init();
	void Update();
	void Render();
	void Colc();

	void Advance();
	void Back();
	void Left();
	void Right();
	void LeftRotation();
	void RightRotation();
	void UpRotation();
	void DownRotation();
	
	void Jumping();
	void Jump();
	//�X�P�[�����O�iXYZ)
	DirectX::SimpleMath::Vector3 Get_scale();
	//��]�p(XYZ�j
	float Get_rotate();
	//���s�ړ��iXYZ�j
	DirectX::SimpleMath::Vector3 Get_transmat();

	DirectX::SimpleMath::Matrix Get_world();

	void SetTrans(DirectX::SimpleMath::Vector3 vec) { m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec); m_BoxN.SetTrans(vec); }

	BoxNode& GetBoxNode();

	// �W�����v�̑傫����ݒ�
	void SetJump(float spd) { jumping = spd; }
	// �W�����v�̑傫�����擾
	float GetJump() { return jumping; }
	// �W�����v���Ă��邩���擾
	bool isJump() { return m_jump; }
	// �W�����v���Ă��邩��ς���
	void JumpChange(bool is) { m_jump = is; }

	CapsuleNode& GetCapsule();

	SphereNode & GetSphere();

	void StopMove();

	DirectX::SimpleMath::Vector2 GetSpdW() { return m_SpdWalk; }

private:
	DirectX::SimpleMath::Vector2 m_SpdWalk;

	bool m_jump;			//�W�����v�t���O
	float jumping;			//�����x�N�g���̏�����

	DirectX::SimpleMath::Vector3 m_vec;

	bool isCollision;			//�����蔻��̕\��
	
	bool TankMove;//�^���N�p�Ɉړ���

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// ���̂����蔻��m�[�h
	BoxNode m_BoxN;
	// ���̂����蔻��m�[�h
	SphereNode m_sphereN;
	// �J�v�Z���̂����蔻��
	CapsuleNode m_playerCapsule;
	// �����̂����蔻��
	Segment segment;

	std::vector<Obj3d> m_ObjPlayer;

	// ��]�J�E���g
	int rollCnt;
	// �������
	int WalkCase;

	//�L�[�{�[�h
	DirectX::Keyboard* keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyTracker;
};
