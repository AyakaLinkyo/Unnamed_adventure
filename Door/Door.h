#pragma once

#include "..\\Model\Obj3d.h"
#include "..\\Collision\CollisionNode.h"


//î‡
class Door
{
public:
	//ÉtÉçÉAóp
	const static int FLOOR_SCALE_X = 47;
	const static int FLOOR_SCALE_Z = 47;
	//í òH
	const static int PASSEGE_SCALE_X = 24;
	const static int PASSEGE_SCALE_Z = 24;


	enum NUM { FIRST, SECOND, THIRD, FOUR, MAX };
	enum STATE{ CLOSE, OPEN };

	Door();
	~Door();
	virtual void Initialize(Door::NUM num);
	void Update();
	bool Collision(Sphere _PlayerNode);

	void Render();
	Door::STATE GetState();
	void SetState(Door::STATE state);

	Box GetNode();

protected:
	Obj3d m_ObjDoor;
	BoxNode m_collisionNode;
	Door::NUM m_num;
	Door::STATE m_state;
};



