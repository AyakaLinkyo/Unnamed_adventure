#include "..\pch.h"
#include "Switch.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

Switch::Switch()
{
}

Switch::~Switch()
{
}

void Switch::Initialize(Switch::NUM num)
{
	Vector3 pos;

	//モデルの読み込み
	m_ObjSwitch.LoadModel(L"Resources/box.cmo");
	m_ObjSwitchOn.LoadModel(L"Resources/box.cmo");


	switch (num)
	{
	case FIRST:
		pos = Vector3(0, 0, 90);
		break;
	case SECOND:
		pos = Vector3(78, 0, -80);
		break;
	}

	m_ObjSwitch.Set_trans(pos);
	m_ObjSwitch.Set_scale(Vector3(1, 0.5, 1));

	m_collisionNode.SetTrans(m_ObjSwitch.Get_transmat());
	m_collisionNode.SetSize(m_ObjSwitch.Get_scale());

	m_ObjSwitchOn.Set_trans(m_ObjSwitch.Get_transmat());
	m_ObjSwitchOn.Set_scale(m_ObjSwitch.Get_scale());

	m_state = OFF;
}

void Switch::Update(Sphere _PlayerNode)
{
	Vector3* p;
	p = new Vector3;

	Box _box = m_collisionNode;

	//当たり判定
	if (CheckSphere2Box(_PlayerNode, _box, p))
	{
		//判定されたらスイッチON
		m_state = ON;
	}

	m_collisionNode.Update();
	switch (m_state)
	{
	case ON:
		m_ObjSwitchOn.Update();
		break;
	case OFF:
		m_ObjSwitch.Update();
		break;
	}
}

void Switch::Render()
{
	switch (m_state)
	{
	case ON:
		m_ObjSwitchOn.Draw();
		break;
	case OFF:
		m_ObjSwitch.Draw();
		break;
	}
}

Switch::STATE Switch::GetState()
{
	return m_state;
}

void Switch::SetState(Switch::STATE state)
{
	m_state = state;
}
