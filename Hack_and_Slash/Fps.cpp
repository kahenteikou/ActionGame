#include "Fps.hpp"

int Fps::count = 0;
int Fps::startCount = 0;

//コンストラクタ
Fps::Fps() {
	startTime = 0;
	count = 0;
	fps = 0;
}

//更新
bool Fps::Update() {
	startCount++;
	if (count == 0) { //1フレーム目なら時刻を記憶
		startTime = GetNowCount();
	}
	if (count == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		fps = 1000.f / ((t - startTime) / (float)N);
		count = 0;
		startTime = t;
	}
	count++;
	return true;
}

//現在のフレームを取得
int Fps::getFrame() {
	return count;
}

//経過フレームを取得
int Fps::getElapsed()
{
	return startCount;
}



//待機
void Fps::Wait() {
	int tookTime = GetNowCount() - startTime;	//かかった時間
	int waitTime = count * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {

		Sleep(waitTime);	//待機
	}

	//経過フレーム
	if (startCount > 60000) {
		startCount = 0;
	}
}