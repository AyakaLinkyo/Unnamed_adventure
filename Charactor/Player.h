#pragma once
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include "..\\Camera\Camera.h"
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include <Keyboard.h>
#include <vector>
#include "..\\Model\Obj3d.h"

#include "..\\Collision\Collision.h"
#include "..\\Collision\CollisionNode.h"

class Player 
{
public:
	static float GRAVITY;

	// 1フレームでの角度変化制限<度→ラジアン>
	static const float ANGLE_DELTA_MAX;

	//自機パーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,

		PLAYER_PARTS_NUM,
	};

	//ID
	enum PLAYER_SHAPE
	{
		CUPSULE,
		SPHERE,
		CUBE,
	};

	Player(DirectX::Keyboard* keyboard);
	~Player();

	void Init();
	void Update();
	void Render();
	void Colc();

	void Advance();
	void Back();
	void Left();
	void Right();
	void LeftRotation();
	void RightRotation();
	void UpRotation();
	void DownRotation();
	
	void Jumping();
	void Jump();
	//スケーリング（XYZ)
	DirectX::SimpleMath::Vector3 Get_scale();
	//回転角(XYZ）
	float Get_rotate();
	//平行移動（XYZ）
	DirectX::SimpleMath::Vector3 Get_transmat();

	DirectX::SimpleMath::Matrix Get_world();

	void SetTrans(DirectX::SimpleMath::Vector3 vec) { m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec); m_BoxN.SetTrans(vec); }

	BoxNode& GetBoxNode();

	// ジャンプの大きさを設定
	void SetJump(float spd) { jumping = spd; }
	// ジャンプの大きさを取得
	float GetJump() { return jumping; }
	// ジャンプしているかを取得
	bool isJump() { return m_jump; }
	// ジャンプしているかを変える
	void JumpChange(bool is) { m_jump = is; }

	CapsuleNode& GetCapsule();

	SphereNode & GetSphere();

	void StopMove();

	DirectX::SimpleMath::Vector2 GetSpdW() { return m_SpdWalk; }

private:
	DirectX::SimpleMath::Vector2 m_SpdWalk;

	bool m_jump;			//ジャンプフラグ
	float jumping;			//方向ベクトルの初期化

	DirectX::SimpleMath::Vector3 m_vec;

	bool isCollision;			//当たり判定の表示
	
	bool TankMove;//タンク用に移動式

	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// 箱のあたり判定ノード
	BoxNode m_BoxN;
	// 球のあたり判定ノード
	SphereNode m_sphereN;
	// カプセルのあたり判定
	CapsuleNode m_playerCapsule;
	// 線分のあたり判定
	Segment segment;

	std::vector<Obj3d> m_ObjPlayer;

	// 回転カウント
	int rollCnt;
	// 歩く種類
	int WalkCase;

	//キーボード
	DirectX::Keyboard* keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyTracker;
};

