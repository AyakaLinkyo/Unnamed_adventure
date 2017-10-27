//∞----------------------------------------------------∞
//∞*ファイル名：Draw.h 								∞
//∞*内容　　　：描画クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞----------------------------------------------------∞

#pragma once

#include <d3d11.h>
#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include <string.h>
#include <SpriteFont.h>

class Draw
{
public:
	
	//静的メンバ変数の初期化
	void InitializeStatic(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext);

	static Draw & GetInstance();

	~Draw();

	//テクスチャ読み込み
	void Loader(const wchar_t* texture_name, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);

	////2D画像描画(ファイル名、出力する位置)
	//void Render(const wchar_t* texture_name, DirectX::SimpleMath::Vector2 pos);

	////文字描画(出力するテキスト)
	//void RenderFont(wchar_t* text);

	////数字の描画(ファイル名、位置、grpX、grpY、grpW、grpH、描画する数字
	//void RenderNum(const wchar_t * texture_name, DirectX::SimpleMath::Vector2 pos, float grpX, float grpY, float grpW, float grpH, int num);

	////切り取りを使用した描画
	//void RenderRect(const wchar_t * texture_name, DirectX::SimpleMath::Vector2 pos, RECT rect);

	////数字の描画(出力する変数(int)、場所)
	//void RenderNum(int num, DirectX::SimpleMath::Vector2 pos, DirectX::XMVECTOR color, float scale);


	//デバイス
	ID3D11Device* m_d3dDevice;
	//デバイスコンテキスト
	ID3D11DeviceContext* m_d3dContext;


protected:
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	std::unique_ptr<DirectX::CommonStates> m_commonStates;

private:
	Draw();
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

