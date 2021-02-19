#ifndef ___ANIMATION_HPP_
#define ___ANIMATION_HPP_
#include "Fps.hpp"




/*####################################################
* アニメーション
*
* 説明
* アニメーションの数値を走査する。
######################################################*/
class Animation
{
public:

	Animation(int c);	//コンストラクタ
	~Animation();		//デストラクタ

	int getClip(int speed);	//アニメーションを取得

private:

	bool first;
	int Clip;		//現在のクリップ
	int max_Clip;	//クリップ数
	int nextFrame;	//次のクリップのフレーム
};


#endif
