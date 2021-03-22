#ifndef ___PLAYER_HPP_
#define ___PLAYER_HPP_


#include <iostream>
#include <vector>

#include "Actor.hpp"
#include "Bullet.hpp"
#include "Animation.hpp"






/*####################################################
* プレイヤークラス
######################################################*/

//前方宣言

class Bullet;
class Animaiton;
class BoxCollision;
class Enemy_Mng;
class MapChip;
struct ItemData;

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
	float getSpeed();		//速度を取得

	// ####################　設定　関係

	void set_Bulid(ItemData data);			//ステータスを設定
	void FixPos(MapChip m);					//当たり判定で座標を修正
	void OffsetFixPos(glm::vec2  pos);		//座標のオフセットを修正
	void setIsMenu(bool b);					//メニューを開くかどうか設定
	void setSpeed(int speed);				//速度を設定
	void setReset();						//座標をリセット

	void setWorldPosition(glm::vec2  pos);			//ステージ座標を設定
	glm::vec2  getWorldPosition();	//ステージ座標を取得





	void ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy);	//エネミーのバレットとの当たり判定


	glm::vec2  stagePosition;	//ステージ内の座標


	std::shared_ptr<BoxCollision> mCol;	//当たり判定
private:

	

	//スプライト
	int playerSpriteUp[2];
	int playerSpriteLeft[2];
	int playerSpriteDown[2];
	int playerSpriteRight[2];

	int enemyHitEffectSprite[3];
	int stageHitEffectSprite[3];
	int playerBulletSprite;

	glm::vec2 minValue;	//最小値
	glm::vec2 maxValue;	//最大値

	glm::vec2  worldPosition;	//ワールド座標
	//mPosition //ステージ座標

//	glm::vec2  stagePosition;	//ステージ内の座標
	std::shared_ptr<std::vector<Bullet>> bullet;	//バレット

	bool mMenu;	//ショップ画面を開くかどうか？

	Animation anim;


// ステータス

	float speed;			//速度



};


#endif


