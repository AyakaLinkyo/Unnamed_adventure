#pragma once

#include "..\\Model\Obj3d.h"
#include "..\\Collision\CollisionNode.h"


//アイテムの基底クラス
class Item
{
public:
	enum ID { LIGHTER, BOMB, MAX, NONE };
	enum STATE{ FIELD, HAVE, RELEASE, LOSE };

	Item();
	~Item();
	virtual void Initialize(DirectX::SimpleMath::Vector3 pos) = 0;
	bool Item::Update(Sphere _PlayerNode);
	void Render();

	Item::STATE GetState();
	void SetState(Item::STATE state);


	void SetId(Item::ID setId);

	Item::ID GetId();

protected:
	Obj3d m_ObjItem;
	BoxNode m_collisionNode;
	Item::ID m_id;
	Item::STATE m_state;
};


//アイテムのクラス

class None : public Item
{
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
};

class Lighter : public Item
{
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
};

class Bomb : public Item
{
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
};

