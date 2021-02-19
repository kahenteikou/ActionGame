#ifndef ___BULLET_HPP_
#define ___BULLET_HPP_

#include "DxLib.h"
#include "glm/glm.hpp"
#include "Actor.hpp"
#include "Entry.hpp"
#include "Collision.hpp"


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
	Bullet(glm::ivec2 pos, glm::ivec2 vec, int handle);	//コンストラクタ
	~Bullet();											//デストラクタ

	void Update();	//更新
	void Draw();	//描画


	Box_Collision mCol;	//当たり判定
private:
	int mSprite;	//スプライト
	int mSpeed;		//バレットの速度
};


#endif






