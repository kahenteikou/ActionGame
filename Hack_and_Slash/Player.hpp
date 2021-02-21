#ifndef ___PLAYER_HPP_
#define ___PLAYER_HPP_


#include <iostream>
#include <vector>

//#include "Animation.hpp"


//#include "Actor.hpp"
#include "Entry.hpp"

#include "Input.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"
#include "ItemID.hpp"



/*####################################################
* プレイヤークラス
######################################################*/

//前方宣言
class Bullet;

class Player : public Actor
{
public:
	Player(Entry* e);	//コンストラクタ
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

	void set_Bulid(ItemData data);	//ステータスを設定
	void FixPos(glm::ivec2 pos);	//当たり判定で座標を修正
	void setIsMenu(bool b);			//メニューを開くかどうか設定





	Box_Collision mCol;	//当たり判定
private:

	int mSprite;		//プレイヤー　スプライト
	int mBullet_Sprite;	//バレット　スプライト
	int mBulletEffect_Sprite[3];	//バレットエフェクト　スプライト








	std::shared_ptr<std::vector<Bullet>> mBullet;	//バレット

	bool mMenu;	//ショップ画面を開くかどうか？





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


