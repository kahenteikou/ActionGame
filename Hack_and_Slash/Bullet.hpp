#ifndef ___BULLET_HPP_
#define ___BULLET_HPP_

#include "DxLib.h"
#include "glm/glm.hpp"
#include "Actor.hpp"
#include "Entry.hpp"
#include "Collision.hpp"

#include "Animation.hpp"

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
	Bullet(glm::ivec2 pos, glm::ivec2 vec, int handle,int effectHandle[3]);	//コンストラクタ
	~Bullet();											//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	void FixPos(glm::ivec2 pos);	//座標を修正

	Box_Collision mCol;	//当たり判定
	bool mIsHit;	//ヒットしたかどうか？
	
private:
	Animation anim;			//アニメーションクラス
	int mSprite;			//スプライト
	int mEffectSprite[3];	// エフェクトスプライト

	int mSpeed;		//バレットの速度
	
};


#endif






