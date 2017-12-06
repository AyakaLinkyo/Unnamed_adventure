#pragma once
#include "..\Collision\CollisionNode.h"
#include "..\Model\Obj3d.h"

//�������̊��N���X
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


//���̃N���X�i��ނŕ��ʁj

//���E�ɓ���
class MovingPassage : public Passage
{
public:
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
	void SpdInit(DirectX::SimpleMath::Vector3 spd);		//�ǂ̌����ɂǂꂭ�炢�̑��x�œ����̂��ݒ�
	void TimeInit(int time);		//�ǂ̌����ɂǂꂭ�炢�̑��x�œ����̂��ݒ�

	void Update() override;
	void Render() override;

private:
	DirectX::SimpleMath::Vector3 m_spd;
	int m_time;
	int m_endTime;
};

//���ԍ��ŏo����������������肷��
class DisappearPassage : public Passage
{
public:
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
	void StateInit(bool state);		//�n�߂ɏ����Ă��邩�o�����Ă��邩(true���\��)

	void Update() override;
	void Render() override;
	bool GetState();

private:
	int m_time;
	bool m_state;
};

//�����Ȃ�
class NotMovingPassage : public Passage
{
public:
	void Initialize(DirectX::SimpleMath::Vector3 pos) override;
	void Update() override;
	void Render() override;

};
