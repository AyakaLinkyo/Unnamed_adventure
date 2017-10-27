#include "..\\pch.h"

#include "GamePlay.h"
#include "GameMain.h"
#include <d3d11.h>
#include "SimpleMath.h"
#include "..\\Singleton\Key.h"
#include "..\\Singleton\Timer.h"
//#include "Player.h"




using namespace DirectX;
using namespace DirectX::SimpleMath;


GameBase* GamePlay::m_base = NULL;

GameBase * GamePlay::GetInstance()
{
	m_base = new GamePlay();

	return m_base;
}

GamePlay::GamePlay()
{
	this->Initialize();
}


GamePlay::~GamePlay()
{


}

void GamePlay::Initialize()
{

	Key& key = Key::GetInstance();
	Draw& draw = Draw::GetInstance();
	//�J�����̐���
	m_Camera = std::make_unique<FollowCamera>(800, 600);
	
	//�Rd�I�u�W�F�N�g�̐ÓI�����o��������
	Obj3d::InitializeStatic(draw.m_d3dDevice, draw.m_d3dContext, m_Camera.get());
	
	//PrimitiveBatch�̏�����
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(draw.m_d3dContext);

	m_effect = std::make_unique<BasicEffect>(draw.m_d3dDevice);

	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0,
		800, 600, 0, 0, 1));
	m_view = Matrix::CreateLookAt(Vector3(0.f, 2.f, 2.f),
		Vector3(1, 0, 0), Vector3::UnitY);
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(800) / float(600), 0.1f, 500.f);

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	draw.m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//�G�t�F�N�g�t�@�N�g���[����
	m_factory = std::make_unique<EffectFactory>(draw.m_d3dDevice);
	//�e�N�X�`���̓ǂݍ��݃p�X�w��
	m_factory->SetDirectory(L"Resources");
	//���f���̓ǂݍ���
	m_obj_ground.LoadModel(L"Resources\\graund200m.cmo");
	//�V�����f���̓ǂݍ���
	m_obj_skydome.LoadModel(L"Resources\\skydome.cmo");

	//�v���C���[�̐���
	m_player = std::make_unique<Player>(key.m_keyboard.get());

	//�v���C���[���J�����ɃZ�b�g����
	m_Camera->SetPlayer(m_player.get());


	m_obj_skydome.DisableLighting();
	timeCnt = 0;
	endCnt = 0;
}

void GamePlay::UpdateGame(GameMain * main)
{
	Key& key = Key::GetInstance();
	auto kb = key.m_keyboard->GetState();


	Timer& time = Timer::GetInstance();

	if (endCnt == 0)
	{
		key.Update();
		time.Update();
		m_player->Update();
	}
	timeCnt++;
	if (timeCnt > 120)
	{
		timeCnt = 0;
	}
	//���@�ɃJ�������_�����Ă���
	{
		m_Camera->Update();
		m_view = m_Camera->GetViewMatrix();
		m_proj = m_Camera->GetProjectionMatrix();
	}

	//for (std::vector<std::unique_ptr<ENEMY>>::iterator it = m_enemy.begin(); it != m_enemy.end(); it++)
	//{
	//	(*it)->Update(m_player.get());
	//}


	m_obj_skydome.Update();
	m_obj_ground.Update();



	//��]�s��i�����j
	//Matrix rotmat = rotmatZ*rotmatX*rotmatY;
	Matrix rotmat;

	//���s�ړ�
	//����
	Matrix transmat_in = Matrix::CreateTranslation(20.0f, 0.0f, 0.0f);
	//�O��
	Matrix transmat_out = Matrix::CreateTranslation(40.0f, 0.0f, 0.0f);


	ModelEffectManager::getInstance()->Update();

	//if (time.GetTime() < 0)
	//{
	//	endCnt++;
	//	if (endCnt > 30)
	//	{
	//		main->Scene(GameResult::GetInstance());
	//	}
	//}



}


void GamePlay::RenderGame()
{
	Draw& draw = Draw::GetInstance();

	//draw.RenderFont(L"Play");

	//���t���[���`�揈��
	DirectX::CommonStates m_states(draw.m_d3dDevice);
	draw.m_d3dContext->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	draw.m_d3dContext->OMSetDepthStencilState(m_states.DepthNone(), 0);
	draw.m_d3dContext->RSSetState(m_states.CullNone());

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	m_effect->SetWorld(m_world);
	m_effect->Apply(draw.m_d3dContext);
	draw.m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	////�V�����f���̕`��
	m_obj_skydome.Draw();

	////�n�ʃ��f���̕`��
	m_obj_ground.Draw();

	//�^�C���̕`��
	Timer& time = Timer::GetInstance();
	time.Render();

	m_player->Render();

	//for (std::vector<std::unique_ptr<ENEMY>>::iterator it = m_enemy.begin(); it != m_enemy.end(); it++)
	//{
	//	(*it)->Render();
	//}
	ModelEffectManager::getInstance()->Draw();

}

void GamePlay::Dispose()
{
	if (m_base != NULL)
	{
		delete m_base;
	}
}
