#pragma once
#include "..\Collision\CollisionNode.h"
#include "..\Model\Obj3d.h"

//動く床の基底クラス
class Passage
{
public:
	enum ID { Moving, DISAPPEAR, NotMoving, MAX };

	Passage();
	~Passage();

	virtual void Initialize(DirectX::SimpleMath::Vector3 pos) = 0;
	virtual void Update() = 0;
	int passageCollision(Sphere player);
	virtual void Render() = 0;

	void SetId(Passage::ID id);
	Passage::ID GetId();
	Box GetBoxCollision();

protected:
	Obj3d m_objPassage;
	BoxNode m_collisionNode;
	Passage::ID m_id;
};


//床のクラス（種類で分別）

//左右に動く
class MovingPassage : public Passage
{
public:
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
	void SpdInit(DirectX::SimpleMath::Vector3 spd);		//どの向きにどれくらいの速度で動くのか設定
	void TimeInit(int time);		//どの向きにどれくらいの速度で動くのか設定

	void Update() override;
	void Render() override;

private:
	DirectX::SimpleMath::Vector3 m_spd;
	int m_time;
	int m_endTime;
};

//時間差で出現したり消失したりする
class DisappearPassage : public Passage
{
public:
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
	void StateInit(bool state);		//始めに消えているか出現しているか(trueが表示)

	void Update() override;
	void Render() override;
	bool GetState();

private:
	int m_time;
	bool m_state;
};

//動かない
class NotMovingPassage : public Passage
{
public:
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
	void Update() override;
	void Render() override;

};
