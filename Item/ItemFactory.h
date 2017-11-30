#pragma once
#include "Item.h"

class ItemFactory
{
public:

	ItemFactory();
	~ItemFactory();

	std::unique_ptr<Item> Create(Item::ID id, DirectX::SimpleMath::Vector3 pos);
};

