#include "..\\pch.h"

#include "GamePlay.h"
#include "GameMain.h"
#include <d3d11.h>
#include "SimpleMath.h"
#include "..\\Singleton\Key.h"
#include "..\\Singleton\Timer.h"


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
	//singleton�̐ݒ�
	Key& key = Key::GetInstance();
	Draw& draw = Draw::GetInstance();

	//�J�����̐���
	m_Camera = std::make_unique<FollowCamera>(800, 600);

	//�Rd�I�u�W�F�N�g�̐ÓI�����o��������
	Obj3d::InitializeStatic(draw.m_d3dDevice, draw.m_d3dContext, m_Camera.get());

	//PrimitiveBatch�̏�����
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(draw.m_d3dContext);

	m_effect = std::make_unique<BasicEffect>(draw.m_d3dDevice);

	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0, 800, 600, 0, 0, 1));
	m_view = Matrix::CreateLookAt(Vector3(0.f, 2.f, 2.f), Vector3(1, 0, 0), Vector3::UnitY);
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, float(800) / float(600), 0.1f, 500.f);

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

	//�ǂ̐ݒ�
	WallInitialize();

	//���̐ݒ�
	m_door[Door::NUM::FIRST].Initialize(Door::NUM::FIRST);
	m_door[Door::NUM::SECOND].Initialize(Door::NUM::SECOND);
	m_door[Door::NUM::THIRD].Initialize(Door::NUM::THIRD);
	m_door[Door::NUM::FOUR].Initialize(Door::NUM::FOUR);


	m_obj_skydome.DisableLighting();
	timeCnt = 0;
	endCnt = 0;

	//�v���C���[�̐���
	m_player = std::make_unique<Player>();

	//�v���C���[���J�����ɃZ�b�g����
	m_Camera->SetPlayer(m_player.get());
	m_player->SetItem(Item::ID::NONE);

	//�A�C�e������
	m_StageItem[Item::ID::LIGHTER] = m_item_factory->Create(Item::ID::LIGHTER, Vector3(1, 0, 88));
	//m_StageItem[Item::ID::BOMB] = m_item_factory->Create(Item::ID::BOMB, Vector3(-60, 0, -63));
	m_StageItem[Item::ID::BOMB] = m_item_factory->Create(Item::ID::BOMB, Vector3(3, 0, 87));


	//�X�C�b�`�̐���
	m_switch[Switch::NUM::FIRST].Initialize(Switch::NUM::FIRST);
	m_switch[Switch::NUM::SECOND].Initialize(Switch::NUM::SECOND);

}

void GamePlay::UpdateGame(GameMain * main)
{

	Key& key = Key::GetInstance();

	Timer& time = Timer::GetInstance();

	key.Update();
	time.Update();
	m_player->Update();
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

	m_obj_skydome.Update();
	m_obj_ground.Update();


	Vector3* p;
	p = new Vector3;
	Sphere _PlayerNode = m_player->GetSphere();

	//�ǂƂ̔���
	for (int i = 0; i < WALL_NUM; i++)
	{
		Box _box = m_wallNode[i];

		if (CheckSphere2Box(_PlayerNode, _box, p))
		{
			m_player->StopMove();
			//m_player->Colc();
		}
		else
		{
			//m_player->MoveReset();
		}
		m_wall[i].Update();

		m_wallNode[i].Update();
	}

	//�P�ڂ̃X�C�b�`�Ŕ����
	if (m_switch[Switch::NUM::FIRST].GetState() == Switch::STATE::ON)
	{
		m_door[Door::NUM::FIRST].SetState(Door::STATE::OPEN);
	}

	//�Q�ڂ̃X�C�b�`�Ŕ����
	if (m_switch[Switch::NUM::SECOND].GetState() == Switch::STATE::ON)
	{
		m_door[Door::NUM::SECOND].SetState(Door::STATE::OPEN);
	}

	//�h�A�̔���
	for (int i = 0; i < Door::NUM::MAX; i++)
	{
		if (m_door[i].GetState() == Door::STATE::CLOSE)
		{
			if (m_door[i].Collision(_PlayerNode))
			{
				m_player->StopMove();
				if (m_player->GetItemId() != Item::LIGHTER)
				{
					m_door[Door::NUM::THIRD].SetState(Door::STATE::OPEN);
				}

			}
		}
		m_door[i].Update();
	}

	//�A�C�e���̔���
	for (int i = 0; i < Item::ID::MAX; i++)
	{
		//�A�C�e���̍X�V�i�����蔻��������Ɏ擾�j
		if (m_StageItem[i]->Update(_PlayerNode))
		{
			if (m_player->GetItemId() != Item::ID::NONE)
			{
				//�ʂ̕����������Ă�����
				if (m_StageItem[i]->GetId() != m_player->GetItemId())
				{
					m_StageItem[m_player->GetItemId()] = m_item_factory->Create(m_player->GetItemId(), m_player->Get_transmat() + Vector3(3, 0, 0));
					m_StageItem[m_player->GetItemId()]->SetState(Item::STATE::FIELD);
				}
			}

			//�A�C�e������������
			m_player->SetItem(m_StageItem[i]->GetId());
			//�A�C�e�����v���C���[���������Ă����ԂɕύX
			m_StageItem[i]->SetState(Item::STATE::HAVE);

		}
	}

	//�X�C�b�`�̔���
	for (int i = 0; i < Switch::NUM::MAX; i++)
	{
		m_switch[i].Update(_PlayerNode);
	}


	//if (m_player->GetItemId() != Item::LIGHTER)
	//{
	//	m_open.Update();
	//	m_openNode.Update();
	//}

	//��]�s��i�����j
	//Matrix rotmat = rotmatZ*rotmatX*rotmatY;
	Matrix rotmat;

	//���s�ړ�
	//����
	Matrix transmat_in = Matrix::CreateTranslation(20.0f, 0.0f, 0.0f);
	//�O��
	Matrix transmat_out = Matrix::CreateTranslation(40.0f, 0.0f, 0.0f);


	ModelEffectManager::getInstance()->Update();

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
	//m_obj_skydome.Draw();

	////�n�ʃ��f���̕`��
	m_obj_ground.Draw();

	//�ǂ̕`��
	for (int i = 0; i < WALL_NUM; i++)
	{
		m_wall[i].Draw();
		m_wallNode[i].Render();
	}

	//�^�C���̕`��
	Timer& time = Timer::GetInstance();
	time.Render();

	m_player->Render();

	//if (m_player->GetItemId() != Item::LIGHTER)
	//{
	//	m_open.Draw();
	//	m_openNode.Render();
	//}

	//if (m_switch[Switch::NUM::SECOND].GetState() != Switch::STATE::ON)
	//{
	for (int i = 0; i < Door::NUM::MAX; i++)
	{
		m_door[i].Render();
	}
	//m_openNode.Render();
//}


	for (int i = 0; i < Item::ID::MAX; i++)
	{
		if (m_StageItem[i] != nullptr)
		{
			m_StageItem[i]->Render();
		}
	}

	for (int i = 0; i < Switch::NUM::MAX; i++)
	{
		m_switch[i].Render();
	}

	ModelEffectManager::getInstance()->Draw();

}

void GamePlay::Dispose()
{
	if (m_base != NULL)
	{
		delete m_base;
	}
}

void GamePlay::WallInitialize()
{
	//�ǃ��f���̓ǂݍ���
	for (int i = 0; i < WALL_NUM; i++)
	{
		m_wall[i].LoadModel(L"Resources/box.cmo");
	}

	//�ǂ̐ݒ�
	{
		//���̕�
		m_wall[0].Set_trans(Vector3(0, 0, -87));
		m_wall[0].Set_scale(Vector3(200, 6, 1));
		//��O�̕�
		m_wall[1].Set_trans(Vector3(0, 0, 108));
		m_wall[1].Set_scale(Vector3(200, 6, 1));
		//�E
		m_wall[2].Set_trans(Vector3(96, 0, 8));
		m_wall[2].Set_scale(Vector3(1, 6, 200));
		//��
		m_wall[3].Set_trans(Vector3(-101, 0, 8));
		m_wall[3].Set_scale(Vector3(1, 6, 200));
	}

	//�t���A�A���E�̋�؂�
	{
		//�O���t���A
		//LEFT
		m_wall[4].Set_trans(Vector3(-101 + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, 100));
		m_wall[4].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z / 3));
		m_wall[5].Set_trans(Vector3(m_wall[4].Get_transmat().x, 0, m_wall[4].Get_transmat().z - PASSEGE_SCALE_Z));
		m_wall[5].Set_scale(Vector3(PASSEGE_SCALE_X, 6, PASSEGE_SCALE_Z));
		//RIGHT
		m_wall[6].Set_trans(Vector3(m_wall[4].Get_transmat().x + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, 100));
		m_wall[6].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z / 3));
		m_wall[7].Set_trans(Vector3(m_wall[6].Get_transmat().x, 0, m_wall[6].Get_transmat().z - PASSEGE_SCALE_Z));
		m_wall[7].Set_scale(Vector3(PASSEGE_SCALE_X, 6, PASSEGE_SCALE_Z));

		//���ԃt���A
		//LEFT
		m_wall[8].Set_trans(Vector3(-101 + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, 100 - FLOOR_SCALE_Z - PASSEGE_SCALE_Z));
		m_wall[8].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z));
		//RIGHT
		m_wall[9].Set_trans(Vector3(m_wall[8].Get_transmat().x + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, m_wall[8].Get_transmat().z));
		m_wall[9].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z));

		//���ԂQ�t���A
		//LEFT
		m_wall[10].Set_trans(Vector3(-101 + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, 100 - FLOOR_SCALE_Z * 1.5 - PASSEGE_SCALE_Z * 1.5 - 10));
		m_wall[10].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z * 1.5));
		//RIGHT
		m_wall[11].Set_trans(Vector3(m_wall[10].Get_transmat().x + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, m_wall[10].Get_transmat().z));
		m_wall[11].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z * 1.5));

		//���t���A
		//LEFT
		m_wall[12].Set_trans(Vector3(-101 + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, 100 - FLOOR_SCALE_Z * 2 - PASSEGE_SCALE_Z * 2 - 10));
		m_wall[12].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z * 1.5));
		//RIGHT
		m_wall[13].Set_trans(Vector3(m_wall[12].Get_transmat().x + FLOOR_SCALE_X + PASSEGE_SCALE_X, 0, m_wall[12].Get_transmat().z));
		m_wall[13].Set_scale(Vector3(PASSEGE_SCALE_X, 6, FLOOR_SCALE_Z * 1.5));

	}

	//�t���A�A�O��̋�؂�
	{
		//BACK
		//�O���ƒ��Ԃ̊�
		m_wall[14].Set_trans(Vector3(-101 + FLOOR_SCALE_X / 2, 0, 108 - FLOOR_SCALE_Z));
		m_wall[14].Set_scale(Vector3(FLOOR_SCALE_X / 1.5, 6, PASSEGE_SCALE_Z));
		m_wall[15].Set_trans(Vector3(m_wall[14].Get_transmat().x + PASSEGE_SCALE_X + FLOOR_SCALE_X / 1.8, 0, 108 - FLOOR_SCALE_Z));
		m_wall[15].Set_scale(Vector3(FLOOR_SCALE_X + PASSEGE_SCALE_X / 2, 6, PASSEGE_SCALE_Z));
		m_wall[16].Set_trans(Vector3(m_wall[15].Get_transmat().x + PASSEGE_SCALE_X + FLOOR_SCALE_X, 0, m_wall[15].Get_transmat().z));
		m_wall[16].Set_scale(Vector3(FLOOR_SCALE_X + PASSEGE_SCALE_X / 2, 6, PASSEGE_SCALE_Z));

		//���Ԃƒ��ԂQ�̊�
		m_wall[17].Set_trans(Vector3(-101 + FLOOR_SCALE_X / 2, 0, 108 - FLOOR_SCALE_Z * 2));
		m_wall[17].Set_scale(Vector3(FLOOR_SCALE_X / 1.5, 6, PASSEGE_SCALE_Z));
		m_wall[18].Set_trans(Vector3(m_wall[17].Get_transmat().x + PASSEGE_SCALE_X + FLOOR_SCALE_X / 1.8, 0, m_wall[17].Get_transmat().z));
		m_wall[18].Set_scale(Vector3(FLOOR_SCALE_X + PASSEGE_SCALE_X / 2, 6, PASSEGE_SCALE_Z));
		m_wall[19].Set_trans(Vector3(m_wall[18].Get_transmat().x + PASSEGE_SCALE_X + FLOOR_SCALE_X, 0, m_wall[17].Get_transmat().z));
		m_wall[19].Set_scale(Vector3(FLOOR_SCALE_X + PASSEGE_SCALE_X / 2, 6, PASSEGE_SCALE_Z));

		//���ԂQ�ƌ���̊�
		m_wall[20].Set_trans(Vector3(-101 + FLOOR_SCALE_X / 2, 0, 108 - FLOOR_SCALE_Z * 3));
		m_wall[20].Set_scale(Vector3(FLOOR_SCALE_X / 1.5, 6, PASSEGE_SCALE_Z));
		m_wall[21].Set_trans(Vector3(m_wall[20].Get_transmat().x + PASSEGE_SCALE_X + FLOOR_SCALE_X / 1.8, 0, m_wall[20].Get_transmat().z));
		m_wall[21].Set_scale(Vector3(FLOOR_SCALE_X + PASSEGE_SCALE_X / 2, 6, PASSEGE_SCALE_Z));
		m_wall[22].Set_trans(Vector3(m_wall[21].Get_transmat().x + PASSEGE_SCALE_X + FLOOR_SCALE_X, 0, m_wall[20].Get_transmat().z));
		m_wall[22].Set_scale(Vector3(FLOOR_SCALE_X + PASSEGE_SCALE_X / 2, 6, PASSEGE_SCALE_Z));

	}
	//�ǂ̃m�[�h�ݒ�
	for (int i = 0; i < WALL_NUM; i++)
	{
		m_wallNode[i].SetTrans(m_wall[i].Get_transmat() + Vector3(0, 0.5f, 0));
		m_wallNode[i].SetSize(m_wall[i].Get_scale());
	}


}


