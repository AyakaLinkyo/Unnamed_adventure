#pragma once

#include "..\\Model\Obj3d.h"
#include "..\\Collision\CollisionNode.h"


//スイッチ
class Switch
{
public:
	enum NUM { FIRST, SECOND, MAX };
	enum STATE{ ON, OFF };

	Switch();
	~Switch();
	virtual void Initialize(Switch::NUM num);
	void Switch::Update(Sphere _PlayerNode);
	void Render();

	Switch::STATE GetState();
	void SetState(Switch::STATE state);

protected:
	Obj3d m_ObjSwitch;
	Obj3d m_ObjSwitchOn;
	BoxNode m_collisionNode;
	Switch::NUM m_num;
	Switch::STATE m_state;
};



