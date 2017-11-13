#include "..\\pch.h"
#include "Player.h"
#include <stdlib.h>
#include "..\\Singleton\Key.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 1�t���[���ł̊p�x�ω�����<�x�����W�A��>
const float Player::ANGLE_DELTA_MAX = DirectX::XMConvertToRadians(30.0f);
// �d��
float Player::GRAVITY = 0.03f;

//��----------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��----------------------------------------------------��
Player::Player()
{
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);

	//���@�p�[�c�̓ǂݍ���
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/sphere.cmo");
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(Vector3(0, 0, 102.5));
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_scale(Vector3(1, 1, 1));


	//�����ݒ�
	m_jump = true;
	m_jumping = 0;
	m_moveType = NONE;

	//�m�[�h�̏����ݒ�
	m_sphereN.Initialize();
	m_sphereN.SetLocalRadius(0.5f);

}

//��----------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
Player::~Player()
{
}


void Player::Init()
{
}


//��----------------------------------------------------��
//��*func�F�X�V
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Update()
{
	//�L�[�{�[�h�̏��擾
	Key& keyboard = Key::GetInstance();
	Keyboard::State key = keyboard.keyboard->GetState();
	keyboard.keyTracker->Update(key);


	//�J�����̊p�x����i���E�L�[�j
	{
		//���L�[�������ꂽ��
		if (key.Left)
		{
			LeftRotation();
		}
		//�E�L�[�������ꂽ��
		if (key.Right)
		{
			RightRotation();
		}
	}

	//�O��ړ��i�㉺�L�[�j
	{
		//��L�[�������ꂽ��
		if (key.Up)
		{
			Up();
			m_moveType = UP;
		}
		//���L�[�������ꂽ��
		if (key.Down)
		{
			Down();
			m_moveType = DOWN;
		}
	}


	//�X�y�[�X�L�[�������ꂽ��ijump�j
	if (key.Space && m_jump)
	{
		Jumping();
	}

	Jump();

	if (m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat().y <= 0.5f)
	{
		m_jump = true;
		Vector3 vec = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
		vec.y = 0.5f;
		this->SetTrans(vec);
	}

	m_sphereN.SetTrans(this->Get_transmat());
	Colc();
}


//��----------------------------------------------------��
//��*func�F �I�u�W�F�N�g�̕`�揈��
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Render()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}

	m_sphereN.Render();
}


//��----------------------------------------------------��
//��*func�F �I�u�W�F�N�g�̍X�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��

void Player::Colc()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	m_sphereN.Update();

}

//��----------------------------------------------------��
//��*func�F�O�i
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Up()
{
	Vector3 moveV(0, 0, -0.3);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//��----------------------------------------------------��
//��*func�F��i
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Down()
{
	Vector3 moveV(0, 0, 0.3);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//��----------------------------------------------------��
//��*func�F��
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Left()
{
	Vector3 moveV(-0.1f, 0, 0);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//��----------------------------------------------------��
//��*func�F�E
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Right()
{
	Vector3 moveV(0.1f, 0, 0);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}


//��----------------------------------------------------��
//��*func�F����]
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::LeftRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	float angle_x = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle_x, angle + 0.01f, 0));
}

//��----------------------------------------------------��
//��*func�F�E��]
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::RightRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	float angle_x = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle_x, angle - 0.01f, 0));
}


//��----------------------------------------------------��
//��*func�F�W�����v����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Jumping()
{
	if (!m_jump)
	{
		return;
	}

	m_jump = !m_jump;
	m_jumping = 0.5f;
}

void Player::Jump()
{
	m_jumping -= GRAVITY;

	Vector3 moveV(0, m_jumping, 0);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}


DirectX::SimpleMath::Vector3 Player::Get_scale()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_scale();
}

float Player::Get_rotate()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
}

DirectX::SimpleMath::Vector3 Player::Get_transmat()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
}

DirectX::SimpleMath::Matrix Player::Get_world()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_world();
}


SphereNode& Player::GetSphere()
{
	return m_sphereN;
}


//��----------------------------------------------------��
//��*func�F�����蔻�莞�̓���
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*note�F�t�����ɓ������Ă߂荞�܂Ȃ��悤�ɂ���
//��----------------------------------------------------��
void Player::StopMove()
{
	if (m_jump)
	{
		m_jump = !m_jump;
	}

	switch (m_moveType)
	{
	case UP:
		Down();
		break;
	case DOWN:
		Up();
		break;
	case LEFT:
		Right();
		break;
	case RIGHT:
		Left();
		break;
	}
}

