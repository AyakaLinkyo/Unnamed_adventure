#pragma once
#pragma once

#include <d3d11.h>
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include "Draw.h"

class Timer
{
private:
	Timer()
	{
		time = 60;
		time_cnt = 0;
	}

	int time;
	int time_cnt;

public:
	static Timer& GetInstance()
	{
		static Timer* instance = new Timer();
		if (instance == nullptr)
		{
			instance = new Timer();
		}

		return *instance;
	}

	void Update()
	{
		if (time_cnt > 60)
		{
			this->time--;
			time_cnt = 0;
		}
		time_cnt++;
	}

	int GetTime()
	{
		return this->time;
	}

	void ResetTime()
	{
		this->time = 60;
	}
	//∞------------------------------------------------------------------∞
	//∞*func：スコア描画
	//∞*arg：なし
	//∞*return：なし
	//∞------------------------------------------------------------------∞
	void Timer::Render()
	{
		Draw& draw = Draw::GetInstance();
		//if (time <= 0)
		//{
		//	draw.RenderNum(0, DirectX::SimpleMath::Vector2(400, 0),DirectX::Colors::Black,1.5f);
		//}
		//else
		//{
		//	draw.RenderNum(time, DirectX::SimpleMath::Vector2(400, 0), DirectX::Colors::Black, 1.5f);
		//}
	}



};


