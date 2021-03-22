#ifndef ___ENEMY_HPP_
#define ___ENEMY_HPP_

#include <iostream>
#include <vector>

#include "Actor.hpp"
#include "Collision.hpp"
#include "Entry.hpp"
#include "Entry.hpp"
#include "Input.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"
#include "ItemID.hpp"



class Entry;
class Bullet;
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


	Enemy(glm::ivec2 pos, int Enemy_sprite,int Enemy_Bullet_sprite,int Stage_HitEffect_sprite[3],int Player_HitEffect_sprite[3]);	//コンストラクタ
	~Enemy();			//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	// ### 設定　関係
	void FixPos(glm::ivec2 &pos);	//座標を修正
	void setMove_Rand();			//移動乱数を再設定
	void setMovePixel();			//移動量をリセット

	std::shared_ptr<std::vector<Bullet>> getBullet();
	
	void Destroy();		//破壊する。
	bool getIsDestroy();//破壊されたかどうか？		

	BoxCollision mCol;	//当たり判定
private:

	//スプライト
	int enemySprite;					//エネミー
	int enemy_Bullet_sprite;			//バレット
	int stageHitEffect_sprite[3];		//ステージ　ヒットエフェクト
	int playerHitEffect_sprite[3];	//プレイヤー　ヒットエフェクト




	int randMove;		//行動の乱数
	int randAttack;		//攻撃するかどうか？

	int prevRandAction;	//前の行動の乱数
	int speed;				//移動速度
	int moveValue;			//移動量


	bool isLefe; //生きているかどうか？

	std::shared_ptr<std::vector<Bullet>> bullet;	//バレット




};


#endif

