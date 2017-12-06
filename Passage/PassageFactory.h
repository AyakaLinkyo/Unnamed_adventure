#pragma once
#include "Passage.h"

class PassageFactory
{
public:

	PassageFactory();
	~PassageFactory();

	std::unique_ptr<Passage> Create(Passage::ID id, DirectX::SimpleMath::Vector3 pos);
};

