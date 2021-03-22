#ifndef ___ANIMATION_HPP_
#define ___ANIMATION_HPP_

/*####################################################
* アニメーション
*
* 説明
* アニメーションの番号を管理
######################################################*/
class Animation
{
public:

	Animation(int c);	//コンストラクタ
	~Animation();		//デストラクタ

	//アニメーション番号を取得

	int getClip_loop(int speed);		//ループで取得
	bool getClip(int &num,int speed);	//1回だけ取得

private:


	bool first;
	int clip;		//現在の番号
	int maxClip;	//番号の数
	int nextFrame;	//次の番号までのフレーム
	bool isAnim;	//一回だけ再生したかどうか？
};


#endif
