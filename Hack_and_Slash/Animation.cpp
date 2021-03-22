#include "Animation.hpp"
#include "Fps.hpp"

//コンストラクタ
Animation::Animation(int c)
{
	clip = 0;		//現在の番号
	maxClip = c;	//番号の数
	nextFrame = 1;	//次の番号になるフレーム数
	first = false;	//フレームを再計算するかどうか？
	isAnim = false;	//一回だけ再生したかどうか？
}


//デストラクタ
Animation::~Animation()
{

}

//アニメーションをループ再生
int Animation::getClip_loop(int speed)
{
	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//次のクリップのフレームを計算
		first = true;

//		return Clip;
	}
	
	
	if (Fps::getElapsed() == nextFrame) {

		clip++;

		//最大クリップを超えた時
		if (clip > maxClip) 
		{
			clip = 0;
		}

		first = false;
		return clip;
	}
	else 
	{
		return clip;
	}

}

//1回だけ取得
bool Animation::getClip(int& num, int speed)
{

	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//次のクリップのフレームを計算
		first = true;
	}


	if (Fps::getElapsed() >= nextFrame) {

		clip++;

		//最大クリップを超えた時
		if (clip > maxClip)
		{
			clip = 0;

			isAnim = true;
			first = false;
			return isAnim;
		}

		//printf("いいいいいいい\n");

		first = false;

		num = clip;
		return isAnim;
	}
	else
	{
		//printf("あああああ\n");
		num = clip;
		return isAnim;
	}

}













