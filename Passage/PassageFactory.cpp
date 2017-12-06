#include "..\pch.h"
#include "PassageFactory.h"


PassageFactory::PassageFactory()
{
}


PassageFactory::~PassageFactory()
{
}

std::unique_ptr<Passage> PassageFactory::Create(Passage::ID id, DirectX::SimpleMath::Vector3 pos)
{
	std::unique_ptr<Passage> passage;

	switch (id)
	{
	case Passage::ID::Moving:
		passage = std::make_unique<MovingPassage>();
		passage->SetId(Passage::ID::Moving);
		break;

	case Passage::ID::DISAPPEAR:
		passage = std::make_unique<DisappearPassage>();
		passage->SetId(Passage::ID::DISAPPEAR);
		break;
		
	case Passage::ID::NotMoving:
		passage = std::make_unique<NotMovingPassage>();
		passage->SetId(Passage::ID::NotMoving);
		break;

	default:
		return passage;
		break;
	}
	//ƒAƒCƒeƒ€‚Ì‰Šú‰»
	passage->Initialize(pos);
	return passage;
}
