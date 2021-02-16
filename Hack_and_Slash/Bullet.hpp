#ifndef ___BULLET_HPP_
#define ___BULLET_HPP_

#include "DxLib.h"

#include "Actor.hpp"
#include "Entry.hpp"

/*####################################################
* バレット(弾)
*
* 説明
* vectorで管理
* プレイヤーの攻撃
* 
######################################################*/

class Bullet : public Actor
{
public:
	Bullet(glm::ivec2 pos, glm::ivec2 vec,int handle);	//コンストラクタ
	~Bullet();											//デストラクタ

	void Update() override;	//更新
	void Draw() override;	//描画

private:
	int mSprite;	//スプライト
	int mSpeed;		//バレットの速度


	

};


#endif






