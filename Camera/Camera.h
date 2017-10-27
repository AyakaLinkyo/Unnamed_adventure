#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>

class Camera
{
public:
	// メンバ関数
	// コンストラクタ
	Camera(int width,int height);

	// デストラクタ
	virtual ~Camera();

	// 更新
	virtual void Update();

	// ビュー行列を取得
	DirectX::SimpleMath::Matrix GetViewMatrix();

	// 射影行列を取得
	DirectX::SimpleMath::Matrix GetProjectionMatrix();

	void Seteyepos(DirectX::SimpleMath::Vector3 eyepos);
	void Setrefpos(DirectX::SimpleMath::Vector3 refpos);
	void Setupvec(DirectX::SimpleMath::Vector3 upvec);
	void SetfovY(float fovY);
	void Setaspect(float aspect);
	void SetnearClip(float nearClip);
	void SetfarClip(float farClip);

protected:
	// メンバ変数

	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	// 視点
	DirectX::SimpleMath::Vector3 m_eyepos;
	// 参照点/注視点 
	DirectX::SimpleMath::Vector3 m_refpos;
	// 上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;
	// 垂直方向視野角
	float m_fovY;
	// アスペクト比（横・縦の比率）
	float m_aspect;
	// ニアクリップ（手前の表示限界距離）
	float m_nearClip;
	// ファークリップ（奥の表示限界距離）
	float m_farClip;
};