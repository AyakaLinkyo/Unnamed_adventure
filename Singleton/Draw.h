//��----------------------------------------------------��
//��*�t�@�C�����FDraw.h 								��
//��*���e�@�@�@�F�`��N���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��----------------------------------------------------��

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
	
	//�ÓI�����o�ϐ��̏�����
	void InitializeStatic(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext);

	static Draw & GetInstance();

	~Draw();

	//�e�N�X�`���ǂݍ���
	void Loader(const wchar_t* texture_name, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);

	////2D�摜�`��(�t�@�C�����A�o�͂���ʒu)
	//void Render(const wchar_t* texture_name, DirectX::SimpleMath::Vector2 pos);

	////�����`��(�o�͂���e�L�X�g)
	//void RenderFont(wchar_t* text);

	////�����̕`��(�t�@�C�����A�ʒu�AgrpX�AgrpY�AgrpW�AgrpH�A�`�悷�鐔��
	//void RenderNum(const wchar_t * texture_name, DirectX::SimpleMath::Vector2 pos, float grpX, float grpY, float grpW, float grpH, int num);

	////�؂�����g�p�����`��
	//void RenderRect(const wchar_t * texture_name, DirectX::SimpleMath::Vector2 pos, RECT rect);

	////�����̕`��(�o�͂���ϐ�(int)�A�ꏊ)
	//void RenderNum(int num, DirectX::SimpleMath::Vector2 pos, DirectX::XMVECTOR color, float scale);


	//�f�o�C�X
	ID3D11Device* m_d3dDevice;
	//�f�o�C�X�R���e�L�X�g
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

