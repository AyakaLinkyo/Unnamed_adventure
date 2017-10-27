#include "..\\pch.h"

#include "Key.h"


Key & Key::GetInstance()
{
	static Key* instance = new Key();
	if (instance == nullptr)
	{
		instance = new Key();
	}

	return *instance;
}

void Key::Update()
{
	// ƒL[“ü—Íî•ñ‚ðŽæ“¾
	DirectX::Keyboard::State key = m_keyboard->GetState();
	m_keyTracker->Update(key);

}

Key::Key()
{
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}


