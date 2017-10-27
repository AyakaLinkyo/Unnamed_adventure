#include "..\\pch.h"
#include "Player.h"
#include <stdlib.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;

// 1フレームでの角度変化制限<度→ラジアン>
const float Player::ANGLE_DELTA_MAX = DirectX::XMConvertToRadians(30.0f);
float Player::GRAVITY = 0.03f;

//∞----------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞----------------------------------------------------∞
Player::Player(DirectX::Keyboard* keyboard)
{
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);

	//自機パーツの読み込み
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/sphere.cmo");
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(Vector3(68, 0.5, 67));
	//m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resource/player.cmo");
	//m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	//m_ObjPlayer[PLAYER_PARTS_DOWNBODY].LoadModel(L"Resources/down_body.cmo");



	////親からのオフセット
	//m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(Vector3(1, 0, 0));

	m_ObjPlayer[PLAYER_PARTS_BODY].Set_scale(Vector3(1, 1, 1));
	//m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(0, 10, 0));

	//当たり判定は描画されない
	isCollision = true;

	//きーぼーどの初期化
	this->keyboard = keyboard;
	keyTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	std::unique_ptr<Keyboard::KeyboardStateTracker> keyTracker(new Keyboard::KeyboardStateTracker);

	m_jump = true;
	jumping = 0;

	m_BoxN.Initialize();

	segment.Start = Vector3(0, 0.5f, 0);
	segment.End = Vector3(0, 2.0f, 0);

	m_playerCapsule.Initialize();
	m_playerCapsule.SetHiehtRadius(1.5f, 0.5f);
	m_playerCapsule.SetSize(this->Get_transmat());

	m_sphereN.Initialize();
	m_sphereN.SetLocalRadius(0.5f);

	rollCnt = 0;
	WalkCase = 0;

	TankMove = false;
}

//∞----------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
Player::~Player()
{
}


void Player::Init()
{
}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：武器オブジェクト,親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Update()
{
	//キーボードの情報取得
	Keyboard::State key = keyboard->GetState();
	keyTracker->Update(key);

	if (rollCnt == 0)
	{
		m_SpdWalk = Vector2(0, 0);
	}

	if (TankMove == false && key.T)
	{
		TankMove = true;
	}

	if (TankMove == true && key.R)
	{
		TankMove = false;
	}

	//Aキーが押されたら
	if (key.A)
	{
		LeftRotation();
	}
	//Dキーが押されたら
	if (key.D)
	{
		RightRotation();
	}
	//上キーが押されたら
	if (key.Up)
	{
		Advance();
	}
	//下キーが押されたら
	if (key.Down)
	{
		Back();
	}
	//左キーが押されたら
	if (key.Left)
	{
		Left();
	}
	//右キーが押されたら
	if (key.Right)
	{
		Right();
	}


	//スペースキーが押されたら（jump）
	if (keyTracker->pressed.Space && m_jump)
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

	if (TankMove == false)
	{
		if (rollCnt != 0)
		{
			switch (WalkCase)
			{
			case 0:
				rollCnt--;
				Left();
				break;
			case 1:
				rollCnt--;
				Right();
				break;
			case 2:
				rollCnt--;
				Advance();
				break;
			case 3:
				rollCnt--;
				Back();
				break;
			default:
				if (rollCnt < 0) { RightRotation(); rollCnt++; }
				else { LeftRotation(); rollCnt--; }
				break;
			}
		}
		else {
			WalkCase = 99;
		}
	}

	m_sphereN.SetTrans(this->Get_transmat());
	m_BoxN.SetTrans(this->Get_transmat());
	m_playerCapsule.SetTrans(this->Get_transmat());

	Colc();
}

void Player::Render()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}

	m_sphereN.Render();
}

void Player::Colc()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	m_BoxN.Update();
	m_sphereN.Update();
	m_playerCapsule.Update();

}

//∞----------------------------------------------------∞
//∞*func：前進
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Advance()
{
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);
}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Back()
{
	Vector3 moveV(0, 0, 0.1f);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//∞----------------------------------------------------∞
//∞*func：左
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Left()
{
	Vector3 moveV(-0.1f, 0, 0);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//∞----------------------------------------------------∞
//∞*func：右
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Right()
{
	Vector3 moveV(0.1f, 0, 0);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}


//∞----------------------------------------------------∞
//∞*func：左回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::LeftRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	float angle_x = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle_x, angle + 0.01f, 0));
}

//∞----------------------------------------------------∞
//∞*func：右回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::RightRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	float angle_x = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle_x, angle - 0.01f, 0));
}

//∞----------------------------------------------------∞
//∞*func：上回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::UpRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	float angle_y = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	if (m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x < 0.15)
	{
		m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle + 0.005f, angle_y, 0));
	}
}
//∞----------------------------------------------------∞
//∞*func：下回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::DownRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	float angle_y = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	if (m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x > -0.09)
	{
		m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle - 0.005f, angle_y, 0));
	}

}

/// <summary>
/// 
/// ジャンプする
/// 
/// </summary>
void Player::Jumping()
{
	if (!m_jump)
	{
		return;
	}

	m_jump = !m_jump;
	jumping = 0.5f;
}

void Player::Jump()
{
	jumping -= GRAVITY;

	Vector3 moveV(0, jumping, 0);
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

BoxNode& Player::GetBoxNode()
{
	return m_BoxN;
}

CapsuleNode& Player::GetCapsule()
{
	return m_playerCapsule;
}

SphereNode& Player::GetSphere()
{
	return m_sphereN;
}

void Player::StopMove()
{
	if (m_jump) { m_jump = !m_jump; }
	switch (WalkCase)
	{
	case 0:
		Right();
		break;
	case 1:
		Left();
		break;
	case 2:
		Back();
		break;
	case 3:
		Advance();
		break;
	}
}