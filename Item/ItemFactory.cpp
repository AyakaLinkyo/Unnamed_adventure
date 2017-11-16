#include "..\pch.h"
#include "ItemFactory.h"


ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

std::unique_ptr<Item> ItemFactory::Create(Item::ID id)
{
	std::unique_ptr<Item> item;

	switch (id)
	{
	case Item::ID::LIGHTER:
		item = std::make_unique<Lighter>();
		break;
		
	case Item::ID::BOMB:
		item = std::make_unique<Bomb>();
		break;

	default:
		return item;
		break;
	}
	//アイテムの初期化
	item->Initialize();
	return item;
}
