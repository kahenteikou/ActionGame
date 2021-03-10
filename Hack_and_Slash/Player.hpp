#ifndef ___PLAYER_HPP_
#define ___PLAYER_HPP_


#include <iostream>
#include <vector>

#include "Actor.hpp"
#include "Bullet.hpp"
#include "ItemID.hpp"
#include "Collision.hpp"
#include "Animation.hpp"






/*####################################################
* プレイヤークラス
######################################################*/

//前方宣言
class Bullet;
class Enemy;
class Enemy_Mng;
class Actor;
class Box_Collision;
class Animaiton;


class Player : public Actor
{
public:
	Player(Entry* e,int Player_Handle[8], int Player_Bullet_Handle,int Enemy_HitEffect_Handle[3], int Stage_HitEffect_Handle[3]);	//コンストラクタ
	~Player();	//デストラクタ

	
	void Update();	//更新
	void Draw();	//描画
	
	// バレット
	void Bullet_Update();	//更新
	void Bullet_Draw();		//描画

	//プレイヤー
	void Player_Update();	//更新
	void Player_Draw();		//描画


	// #################### 取得　関係

	bool getIsMenu();	//ショップ画面を開いているかどうか？	
	std::shared_ptr<std::vector<Bullet>> getBullet();	//バレット
	int getSpeed();		//速度を取得

	// ####################　設定　関係

	void set_Bulid(ItemData data);		//ステータスを設定
	void FixPos(glm::ivec2 pos);		//当たり判定で座標を修正
	void OffsetFixPos(glm::ivec2 pos);	//座標のオフセットを修正
	void setIsMenu(bool b);				//メニューを開くかどうか設定
	void setSpeed(int speed);			//速度を設定
	void setReset();					//座標をリセット




	void ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy);	//エネミーのバレットとの当たり判定



	glm::ivec2 mStagePosition;


	Box_Collision mCol;	//当たり判定
private:

	

	//スプライト
	int mPlayer_sprite_Up[2];
	int mPlayer_sprite_Left[2];
	int mPlayer_sprite_Down[2];
	int mPlayer_sprite_Right[2];

	int mEnemy_HitEffect_sprite[3];
	int mStage_HitEffect_sprite[3];
	int mPlayer_Bullet_sprite;





	glm::ivec2 stagePosition;	//ステージ内の座標
	std::shared_ptr<std::vector<Bullet>> mBullet;	//バレット

	bool mMenu;	//ショップ画面を開くかどうか？

	Animation anim;


// ステータス

	int mSpeed;			//速度
	int mSpeed_Max;		//最大速度

	int HP_Max;			//最大HP
	int HP;				//HP
	int HP_autoRec;		//自動回復

	int Attack;			//攻撃力

	int Coin;			//通貨



};


#endif


