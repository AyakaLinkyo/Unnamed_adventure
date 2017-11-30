#include "..\pch.h"
#include "ItemFactory.h"


ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

std::unique_ptr<Item> ItemFactory::Create(Item::ID id, DirectX::SimpleMath::Vector3 pos)
{
	std::unique_ptr<Item> item;

	switch (id)
	{
	case Item::ID::NONE:
		item = std::make_unique<None>();
		item->SetId(Item::ID::NONE);
		break;

	case Item::ID::LIGHTER:
		item = std::make_unique<Lighter>();
		item->SetId(Item::ID::LIGHTER);
		break;
		
	case Item::ID::BOMB:
		item = std::make_unique<Bomb>();
		item->SetId(Item::ID::BOMB);
		break;

	default:
		return item;
		break;
	}
	//ƒAƒCƒeƒ€‚Ì‰Šú‰»
	item->Initialize(pos);
	return item;
}
