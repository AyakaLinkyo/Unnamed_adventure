#include "..\pch.h"
#include "Item.h"
#include "ItemFactory.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

Item::Item()
{
	m_state = FIELD;
}

Item::~Item()
{
}

Item::ID Item::Update(Sphere _PlayerNode)
{

	//アイテムが表示されていたら
	if (m_state == FIELD)
	{
		Vector3* p;
		p = new Vector3;

		Box _box = m_collisionNode;

		if (CheckSphere2Box(_PlayerNode, _box, p))
		{
			m_state = HAVE;

			return m_id;
		}

		m_collisionNode.Update();
		m_ObjItem.Update();
		
		return Item::ID::NONE;
	}
}

void Item::Render()
{
	if (m_state == FIELD)
	{
		m_ObjItem.Draw();
	}
}

Item::STATE Item::GetState()
{
	return m_state;
}

void Item::SetState(Item::STATE _state)
{
	m_state = _state;
}

void Item::SetId(Item::ID setId)
{
	m_id = setId;
}

Item::ID Item::GetId()
{
	return m_id;
}

void Lighter::Initialize(DirectX::SimpleMath::Vector3 pos)
{
	//モデルの読み込み
	m_ObjItem.LoadModel(L"Resources/box.cmo");
	m_ObjItem.Set_trans(pos);
	m_ObjItem.Set_scale(Vector3(0.5, 0.3, 1));

	//ノードの設定
	m_collisionNode.Initialize();
	m_collisionNode.SetTrans(m_ObjItem.Get_transmat() + Vector3(0, 0.5f, 0));
	m_collisionNode.SetSize(m_ObjItem.Get_scale());

	m_id = Item::ID::LIGHTER;

}

void Bomb::Initialize(DirectX::SimpleMath::Vector3 pos)
{
	//モデルの読み込み
	m_ObjItem.LoadModel(L"Resources/box.cmo");
	m_ObjItem.Set_trans(pos);
	m_ObjItem.Set_scale(Vector3(1, 1, 1));

}

void None::Initialize(DirectX::SimpleMath::Vector3 pos)
{

}
