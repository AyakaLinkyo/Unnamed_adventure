#include "..\\pch.h"
#include "Player.h"
#include <stdlib.h>
#include "..\\Singleton\Key.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 1フレームでの角度変化制限<度→ラジアン>
const float Player::ANGLE_DELTA_MAX = DirectX::XMConvertToRadians(30.0f);
// 重力
float Player::GRAVITY = 0.03f;

//∞----------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞----------------------------------------------------∞
Player::Player()
{
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);

	//自機パーツの読み込み
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/sphere.cmo");
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(Vector3(0, 0, 102.5));
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_scale(Vector3(1, 1, 1));


	//初期設定
	m_jump = true;
	m_jumping = 0;
	m_moveType = NONE;

	//ノードの初期設定
	m_sphereN.Initialize();
	m_sphereN.SetLocalRadius(0.5f);

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
//∞*func：更新
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Update()
{
	//キーボードの情報取得
	Key& keyboard = Key::GetInstance();
	Keyboard::State key = keyboard.keyboard->GetState();
	keyboard.keyTracker->Update(key);


	//カメラの角度動作（左右キー）
	{
		//左キーが押されたら
		if (key.Left)
		{
			LeftRotation();
		}
		//右キーが押されたら
		if (key.Right)
		{
			RightRotation();
		}
	}

	//前後移動（上下キー）
	{
		//上キーが押されたら
		if (key.Up)
		{
			Up();
			m_moveType = UP;
		}
		//下キーが押されたら
		if (key.Down)
		{
			Down();
			m_moveType = DOWN;
		}
	}


	//スペースキーが押されたら（jump）
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


//∞----------------------------------------------------∞
//∞*func： オブジェクトの描画処理
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Render()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}

	m_sphereN.Render();
}


//∞----------------------------------------------------∞
//∞*func： オブジェクトの更新処理
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞

void Player::Colc()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	m_sphereN.Update();

}

//∞----------------------------------------------------∞
//∞*func：前進
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Up()
{
	Vector3 moveV(0, 0, -0.3);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Down()
{
	Vector3 moveV(0, 0, 0.3);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//∞----------------------------------------------------∞
//∞*func：左
//∞*arg：なし
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
//∞*arg：なし
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
//∞*arg：なし
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
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::RightRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	float angle_x = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().x;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(angle_x, angle - 0.01f, 0));
}


//∞----------------------------------------------------∞
//∞*func：ジャンプ処理
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
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


//∞----------------------------------------------------∞
//∞*func：当たり判定時の動き
//∞*arg：なし
//∞*return：なし
//∞*note：逆方向に動かしてめり込まないようにする
//∞----------------------------------------------------∞
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

