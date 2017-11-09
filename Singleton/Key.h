//∞----------------------------------------------------∞
//∞*ファイル名：Key.h									∞
//∞*内容　　　：キーボード処理							∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞----------------------------------------------------∞

#pragma once
#include <Keyboard.h>

class Key
{
public:
	// キーボード関係
	std::unique_ptr<DirectX::Keyboard> keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyTracker;

	static Key& GetInstance();
	void Update();

private:
	Key();
};