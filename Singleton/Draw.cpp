//∞----------------------------------------------------∞
//∞*ファイル名：Draw.cpp								∞
//∞*内容　　　：描画クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞----------------------------------------------------∞


#include "..\\pch.h"
#include "Draw.h"
#include <string>
#include <iostream>
#include <locale> 
#include <codecvt> 
#include <cstdio>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//Device、Contextを読み込む
void Draw::InitializeStatic(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext)
{
	m_d3dContext = d3dContext;
	m_d3dDevice = d3dDevice;
	// スプライトバッチ
	m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext);
	// スプライトフォント
	m_spriteFont = std::make_unique<SpriteFont>(m_d3dDevice, L"myfile.spritefont");

}
//取得
Draw& Draw::GetInstance()
{
	static Draw* instance = new Draw();
	if (instance == nullptr)
	{
		instance = new Draw();
	}

	return *instance;
}


Draw::Draw()
{
}


Draw::~Draw()
{
}

void Draw::Loader(const wchar_t * texture_name, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _texture)
{
	//画像を読み込む
	ComPtr<ID3D11Resource> resource;

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_d3dDevice, texture_name,
			resource.GetAddressOf(),
			_texture.ReleaseAndGetAddressOf()));

	ComPtr<ID3D11Texture2D> texture;
	DX::ThrowIfFailed(resource.As(&texture));

	CD3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);
}

////画像の描画(ファイル名、ポジション)
//void Draw::Render(const wchar_t* texture_name, Vector2 pos)
//{
//	//画像を読み込む
//	ComPtr<ID3D11Resource> resource;
//
//	DX::ThrowIfFailed(
//		CreateWICTextureFromFile(m_d3dDevice, texture_name,
//			resource.GetAddressOf(),
//			m_texture.ReleaseAndGetAddressOf()));
//
//	ComPtr<ID3D11Texture2D> texture;
//	DX::ThrowIfFailed(resource.As(&texture));
//
//	CD3D11_TEXTURE2D_DESC textureDesc;
//	texture->GetDesc(&textureDesc);
//
//	m_origin.x = float(textureDesc.Width / 2);
//	m_origin.y = float(textureDesc.Height / 2);
//
//
//	//描画する
//	m_spriteBatch->Begin();
//
//	m_spriteBatch->Draw(m_texture.Get(), pos, nullptr, Colors::White, 0.f, m_origin);
//
//	m_spriteBatch->End();
//}
//
////文字の描画(描画するテキスト)
//void Draw::RenderFont(wchar_t* text)
//{
//	m_spriteBatch->Begin();
//	SpriteEffects spriteeffect = SpriteEffects::SpriteEffects_None;
//	m_spriteFont->DrawString(m_spriteBatch.get(), text, DirectX::SimpleMath::Vector2(0, 0), DirectX::Colors::White,0.f,Vector2(0,0),6.0f, spriteeffect, 0.5f);
//	//m_spriteFont->DrawString()
//	m_spriteBatch->End();
//}
//
////数字の描画(ファイル名、位置、RECT({ (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) })、描画する数字
//void Draw::RenderNum(const wchar_t * texture_name, DirectX::SimpleMath::Vector2 pos, float grpX, float grpY, float grpW, float grpH, int num)
//{
//	//Rectメモ
//	//left,top,right,bottom
//	//rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
//
//	//画像を読み込む
//	ComPtr<ID3D11Resource> resource;
//
//	DX::ThrowIfFailed(
//		CreateWICTextureFromFile(m_d3dDevice, texture_name,
//			resource.GetAddressOf(),
//			m_texture.ReleaseAndGetAddressOf()));
//
//	ComPtr<ID3D11Texture2D> texture;
//	DX::ThrowIfFailed(resource.As(&texture));
//
//	CD3D11_TEXTURE2D_DESC textureDesc;
//	texture->GetDesc(&textureDesc);
//
//	m_origin.x = float(textureDesc.Width / 2);
//	m_origin.y = float(textureDesc.Height / 2);
//
//
//
//	//描画
//	m_spriteBatch->Begin();	
//
//	int number = num;	//作業用
//	int i = 0;			//文字数
//
//	float m_grpX = grpX;
//	float m_grpY = grpY;
//	float m_grpW = grpW;
//	float m_grpH = grpH;
//
//	RECT rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
//
//
//	if (number <= 0)
//	{
//
//		m_spriteBatch->Draw(m_texture.Get(), pos, &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
//	}
//	else
//	{
//		while (number)
//		{
//			m_grpX = (number % 10) * m_grpW;
//			rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
//			m_spriteBatch->Draw(m_texture.Get(), Vector2((pos.x - i * m_grpW), pos.y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
//			number = number / 10;
//			i++;
//		}
//	}
//	m_spriteBatch->End();
//}
//
//
////切り取りを使用した描画(ファイル名、位置、RECT({ (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) })
//void Draw::RenderRect(const wchar_t* texture_name, Vector2 pos, RECT rect)
//{
//	//Rectメモ
//	//left,top,right,bottom
//	//rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
//
//	//画像を読み込む
//	ComPtr<ID3D11Resource> resource;
//
//	DX::ThrowIfFailed(
//		CreateWICTextureFromFile(m_d3dDevice, texture_name,
//			resource.GetAddressOf(),
//			m_texture.ReleaseAndGetAddressOf()));
//
//	ComPtr<ID3D11Texture2D> texture;
//	DX::ThrowIfFailed(resource.As(&texture));
//
//	CD3D11_TEXTURE2D_DESC textureDesc;
//	texture->GetDesc(&textureDesc);
//	RECT render_r = rect;
//
//	//描画
//	m_spriteBatch->Begin();
//
//	m_spriteBatch->Draw(m_texture.Get(), pos, &render_r, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
//
//	m_spriteBatch->End();
//}
//
//void Draw::RenderNum(int num, Vector2 pos, DirectX::XMVECTOR color, float scale)
//{
//
//	int number = num;
//	//数値からstringへ
//	std::string strnum = std::to_string(number);
//	//stringからwchar_t
//	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
//	std::wstring ws = cv.from_bytes(strnum);
//
//	SpriteEffects spriteeffect = SpriteEffects::SpriteEffects_None;
//	DirectX::XMVECTOR Color = color;
//	m_spriteBatch->Begin();
//
//	m_spriteFont->DrawString(m_spriteBatch.get(), ws.c_str(), pos, Color, 0.f, Vector2(0, 0), scale, spriteeffect, 0.5f);
//	//m_spriteFont->DrawString(m_spriteBatch.get(), ws.c_str(), pos, DirectX::Colors::Black);
//
//	m_spriteBatch->End();
//
//}
//


