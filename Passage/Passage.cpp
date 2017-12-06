#include "Passage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Passage::Passage()
{
}


Passage::~Passage()
{
}

//当たり判定
int Passage::passageCollision(Sphere player)
{
	Vector3* p;
	p = new Vector3;

	Box _box = m_collisionNode;

	if (CheckSphere2Box(player, _box, p))
	{
		// 下方向からの衝突処理
		if (player.Center.y + player.Radius >= _box.Pos0.y && player.Center.y + player.Radius < _box.Pos2.y)
		{
			//m_player->JumpChange(false);
			//m_player->SetJump(0);
			return 2;
		}
		// 上方向からの衝突処理
		else if (player.Center.y - player.Radius <= _box.Pos7.y)
		{
			//BoxNode& pN = m_player->GetBoxNode();
			//m_player->SetTrans(Vector3(
			//	m_player->Get_transmat().x,
			//	_box.Pos0.y + (pN.GetSize().y) / 2.0f,
			//	m_player->Get_transmat().z));
			//m_player->SetJump(0);
			//m_player->JumpChange(true);

			return 1;
		}
		else
		{
			return 3;
		}
		
	}

	m_collisionNode.Update();
	m_objPassage.Update();

	return 0;

}


void Passage::SetId(Passage::ID id)
{
	m_id = id;
}

Passage::ID Passage::GetId()
{
	return m_id;
}

Box Passage::GetBoxCollision()
{
	return m_collisionNode;
}

void MovingPassage::Initialize(DirectX::SimpleMath::Vector3 pos)
{
	//モデルの読み込み
	m_objPassage.LoadModel(L"Resources/box.cmo");
	m_objPassage.Set_trans(pos);
	m_objPassage.Set_scale(Vector3(2, 0.3, 2));

	//ノードの設定
	m_collisionNode.Initialize();
	m_collisionNode.SetTrans(m_objPassage.Get_transmat());
	m_collisionNode.SetSize(m_objPassage.Get_scale());

	m_time = 0;
}

void MovingPassage::SpdInit(DirectX::SimpleMath::Vector3 spd)
{
	m_spd = spd;
}

void MovingPassage::TimeInit(int time)
{
	m_endTime = time;
}

void MovingPassage::Update()
{
	m_time++;

	m_objPassage.Set_trans(m_objPassage.Get_transmat() + m_spd);
	m_collisionNode.SetTrans(m_objPassage.Get_transmat());

	//120フレーム（2秒）ごとに方向を変更
	if (m_time > m_endTime)
	{
		m_spd = m_spd * -1;
		m_time = 0;
	}

}

void MovingPassage::Render()
{
	m_objPassage.Draw();
}


void DisappearPassage::Initialize(DirectX::SimpleMath::Vector3 pos)
{
	//モデルの読み込み
	m_objPassage.LoadModel(L"Resources/box.cmo");
	m_objPassage.Set_trans(pos);
	m_objPassage.Set_scale(Vector3(2, 0.3, 2));

	//ノードの設定
	m_collisionNode.Initialize();
	m_collisionNode.SetTrans(m_objPassage.Get_transmat());
	m_collisionNode.SetSize(m_objPassage.Get_scale());

	m_time = 0;
}

void DisappearPassage::Update()
{
	m_time++;

	//180フレーム（３秒）ごとにstateを変更
	if (m_time > 180)
	{
		m_state = !m_state;
		m_time = 0;
	}
}

void DisappearPassage::Render()
{
	if (m_state)
	{
		m_objPassage.Draw();
	}
}

bool DisappearPassage::GetState()
{
	return m_state;
}

void DisappearPassage::StateInit(bool state)
{
	m_state = state;
}


void NotMovingPassage::Initialize(DirectX::SimpleMath::Vector3 pos)
{
	//モデルの読み込み
	m_objPassage.LoadModel(L"Resources/box.cmo");
	m_objPassage.Set_trans(pos);
	m_objPassage.Set_scale(Vector3(2, 0.3, 2));

	//ノードの設定
	m_collisionNode.Initialize();
	m_collisionNode.SetTrans(m_objPassage.Get_transmat());
	m_collisionNode.SetSize(m_objPassage.Get_scale());

}

void NotMovingPassage::Update()
{
}

void NotMovingPassage::Render()
{
	m_objPassage.Draw();
}
