#include "..\pch.h"
#include "Door.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

Door::Door()
{
}

Door::~Door()
{
}

void Door::Initialize(Door::NUM num)
{
	Vector3 pos;
	Vector3 scale;

	switch (num)
	{
	case FIRST:
		pos = Vector3(30, 0, 90);
		scale = Vector3(0, 6, FLOOR_SCALE_Z);
		m_ObjDoor.LoadModel(L"Resources/box.cmo");
		break;

	case SECOND:
		pos = Vector3(0, 0, 65);
		scale = Vector3(FLOOR_SCALE_X, 6, 1);
		m_ObjDoor.LoadModel(L"Resources/box.cmo");
		break;

	case THIRD:
		pos = Vector3(-20, 0, 90);
		scale = Vector3(0, 6, FLOOR_SCALE_Z);
		m_ObjDoor.LoadModel(L"Resources/box.cmo");
		break;

	case FOUR:
		pos = Vector3(0, 0, -25);
		scale = Vector3(FLOOR_SCALE_X, 6, 1);
		m_ObjDoor.LoadModel(L"Resources/box.cmo");
		break;

	}

	m_ObjDoor.Set_trans(pos);
	m_ObjDoor.Set_scale(scale);

	m_collisionNode.SetTrans(pos);
	m_collisionNode.SetSize(scale);

	m_state = CLOSE;
}

bool Door::Collision(Sphere _PlayerNode)
{
	//壁との判定
	Vector3* p;
	p = new Vector3;

	Box _box = m_collisionNode;

	if (CheckSphere2Box(_PlayerNode, _box, p))
	{
		return true;
	}
	else
	{
		//m_player->MoveReset();
	}

	return false;

}

void Door::Update()
{
	//扉が閉まっていたらオブジェクトを更新
	if (m_state == CLOSE)
	{
		m_ObjDoor.Update();
		m_collisionNode.Update();
	}

}

void Door::Render()
{
	if (m_state == CLOSE)
	{
		m_ObjDoor.Draw();
	}
}

Door::STATE Door::GetState()
{
	return m_state;
}

void Door::SetState(Door::STATE state)
{
	m_state = state;
}

Box Door::GetNode()
{
	return m_collisionNode;
}
