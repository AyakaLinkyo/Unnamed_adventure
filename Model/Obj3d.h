//∞----------------------------------------------------∞
//∞*ファイル名：Obj3d.h								∞
//∞*内容　　　：3Dオブジェクトのクラス					∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.22								∞
//∞----------------------------------------------------∞
#pragma once

#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include "..\Camera\Camera.h"
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

class Obj3d
{
	//静的メンバ
public:
	//静的メンバ変数の初期化
	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera* camera);
protected:
	//デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	//カメラ
	static Camera* m_Camera;
	//汎用描画ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//エフェクトファクトリー
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


public:
	//コンストラクタ
	Obj3d();

	//モデルをロード
	void LoadModel(const wchar_t* filename);

	//更新
	void Update();

	//描画
	void Draw();

	//setter
	//スケーリング（XYZ)
	void Set_scale(DirectX::SimpleMath::Vector3 scalemat);
	//回転角(XYZ）
	void Set_rotate(DirectX::SimpleMath::Vector3 rotmat);
	//回転角(クォータニオン）
	void Set_rotateQ(DirectX::SimpleMath::Quaternion rotmat);
	void Set_world(DirectX::SimpleMath::Matrix world);
	//平行移動（XYZ）
	void Set_trans(DirectX::SimpleMath::Vector3 transmat);
	//親の3Dオブジェクトのポインタ
	void Set_perant(Obj3d* perant);

	//getter
	//スケーリング（XYZ)
	DirectX::SimpleMath::Vector3 Get_scale();
	//回転角(XYZ）
	DirectX::SimpleMath::Vector3 Get_rotate();
	//平行移動（XYZ）
	DirectX::SimpleMath::Vector3 Get_transmat();
	//回転角
	DirectX::SimpleMath::Quaternion Get_Qua();
	//親の3Dオブジェクトのポインタ
	Obj3d* Get_perant();

	//ワールド行列
	DirectX::SimpleMath::Matrix Get_world();

	void DisableLighting();

protected:
	//メンバー変数
	//3Dモデル
	std::unique_ptr<DirectX::Model> m_model;

	//スケーリング（XYZ)
	DirectX::SimpleMath::Vector3 m_scalemat;

	//回転角(XYZ）
	DirectX::SimpleMath::Vector3 m_rotmat;

	//回転角(クォータニオン）
	DirectX::SimpleMath::Quaternion m_rotmatQ;

	//平行移動（XYZ）
	DirectX::SimpleMath::Vector3 m_transmat;
	
	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//親のワールド行列のポインタ
	Obj3d* m_perent;

	//クォータニオン使用フラグ
	bool m_useQuaternion;
	
};

