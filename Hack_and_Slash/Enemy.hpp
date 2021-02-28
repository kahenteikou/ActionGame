#ifndef ___ENEMY_HPP_
#define ___ENEMY_HPP_

#include "Actor.hpp"
#include "Collision.hpp"
#include "Entry.hpp"
#include "Bullet.hpp"


class Entry;
/*####################################################
* エネミー
* 
* 説明
* 敵の移動と行動するクラス
######################################################*/

class Enemy :public Actor
{
public:

	/*コンストラクタ引数
	* 
	* エネミースプライト
	* バレットスプライト
	* ステージヒットエフェクト
	* プレイヤーヒットエフェクト 
	*/


	Enemy(int Enemy_sprite,int Enemy_Bullet_sprite,int Stage_HitEffect_sprite[3],int Player_HitEffect_sprite[3]);	//コンストラクタ
	~Enemy();			//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	// ### 設定　関係
	void FixPos(glm::ivec2 pos);	//座標を修正
	void setMove_Rand();			//移動乱数を再設定
	void setMovePixel();			//移動量をリセット
	std::shared_ptr<std::vector<Bullet>> getBullet();


	Box_Collision mCol;	//当たり判定
private:

	//スプライト
	int mEnemy_sprite;					//エネミー
	int mEnemy_Bullet_sprite;			//バレット
	int mStage_HitEffect_sprite[3];		//ステージ　ヒットエフェクト
	int mPlayer_HitEffect_sprite[3];	//プレイヤー　ヒットエフェクト




	int Rand_Action;		//行動の乱数
	int Rand_Attack;		//攻撃するかどうか？

	int Prev_Rand_Action;	//前の行動の乱数
	int mSpeed;				//移動速度
	int MovePixel;			//移動量

	std::shared_ptr<std::vector<Bullet>> bullet;	//バレット




};


#endif

