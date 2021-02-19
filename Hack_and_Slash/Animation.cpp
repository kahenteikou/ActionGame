#include "Animation.hpp"

//コンストラクタ
Animation::Animation(int c)
{
	Clip = 0;
	max_Clip = c;
	nextFrame = 1;
	first = false;
}


//デストラクタ
Animation::~Animation()
{

}

//アニメーションを取得
int Animation::getClip(int speed)
{
	if (first == false)
	{
		nextFrame += speed;
		nextFrame -= 60;
		first = true;
	}


	
	if (Fps::getFrame() % nextFrame == 0)
	{
		nextFrame += speed;
		nextFrame -= 60;

	}

}
