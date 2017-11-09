#include "..\\pch.h"
#include "FollowCamera.h"
#include "..\\Singleton\Key.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const float FollowCamera::CAMERA_DISTANCE = 6.0f;

FollowCamera::FollowCamera(int width, int height)
	: m_targetPos(0, 0, 0)
	,Camera(width, height)
{
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	m_isChangeFPS = false;
	m_player = nullptr;
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update()
{
	//Key& key = Key::GetInstance();

	//// キーボードの状態取得
	//Keyboard::State keyboardState = key.keyboard->GetState();
	//key.keyTracker->Update(keyboardState);

	//if (keyboardState.C)
	//{
	//	// フラグ切り替え
	//	m_isChangeFPS = !m_isChangeFPS;
	//}

	if (m_player)
	{
		//目標座標
		SetTargetPos(m_player->Get_transmat());
		SetTargetAngle(m_player->Get_rotate());
	}
	
	if (m_isChangeFPS == true)
	{
		// 視点、参照点
		Vector3 eyepos, refpos;

		// ターゲットの座標は、自分の座標に追従（少し上方向にずらす）
		eyepos = m_targetPos + Vector3(0, 2.5f, 0.0);
		// ターゲット座標からカメラ座標への差分
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		// カメラの視線方向の逆方向に回転
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle) * -1;
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		// カメラ座標を計算
		refpos =m_targetPos + Vector3(0, 3, 0);
		eyepos = eyepos - cameraV;


		Seteyepos(eyepos);
		Setrefpos(refpos);

		// 基底クラスの更新
		Camera::Update();
	}
	else
	{
		// 視点、参照点
		Vector3 eyepos, refpos;

		// ターゲットの座標は、自分の座標に追従（少し上方向にずらす）
		refpos = m_targetPos + Vector3(0, 2.5f, 0.0);
		// ターゲット座標からカメラ座標への差分
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		// カメラの視線方向の逆方向に回転
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		// カメラ座標を計算
		eyepos = refpos + cameraV;

		// 視点を現在位置から補完する
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.1f;
		// 参照点を現在位置から補完する
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;

		Seteyepos(eyepos);
		Setrefpos(refpos);

		// 基底クラスの更新
		Camera::Update();
	}

}

void FollowCamera::SetTargetPos(Vector3 targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard* keyboard)
{
	m_keyboard = keyboard;
}

// TPSゴム紐カメラマン
/*
// 視点、参照点
Vector3 eyepos, refpos;

// ターゲットの座標は、自分の座標に追従（少し上方向にずらす）
refpos = m_targetPos + Vector3(0, 2.0f, 0);
// ターゲット座標からカメラ座標への差分
Vector3 cameraV(0, 0, CAMERA_DISTANCE);

// カメラの視線方向の逆方向に回転
Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
cameraV = Vector3::TransformNormal(cameraV, rotmat);

// カメラ座標を計算
eyepos = refpos + cameraV;

// 視点を現在位置から補完する
eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
// 参照点を現在位置から補完する
refpos = m_refpos + (refpos - m_refpos) * 0.2f;

Seteyepos(eyepos);
Setrefpos(refpos);

// 基底クラスの更新
Camera::Update();
*/

// FPSカメラマン
/*
// 視点、参照点
Vector3 eyepos, refpos;

// ターゲットの座標は、自分の座標に追従（少し上方向にずらす）
eyepos = m_targetPos + Vector3(0, 0.25f, 0);
// ターゲット座標からカメラ座標への差分
Vector3 cameraV(0, 0, CAMERA_DISTANCE);

// カメラの視線方向の逆方向に回転
Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
cameraV = Vector3::TransformNormal(cameraV, rotmat);

// カメラ座標を計算
refpos = eyepos + cameraV;

Seteyepos(eyepos);
Setrefpos(refpos);

// 基底クラスの更新
Camera::Update();
*/