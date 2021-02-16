#ifndef ___FPS_HPP_
#define ___FPS_HPP_

#include <math.h>
#include "DxLib.h"


/*####################################################
* フレームレート制御
######################################################*/

class Fps {
	
public:
	Fps();
	bool Update();	//更新
	void Wait();	//待機
	
private:
	int mStartTime;				//測定開始時刻
	int mCount;					//カウンタ
	float mFps;					//fps
	static const int N = 60;	//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

};
#endif