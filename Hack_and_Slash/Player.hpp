#ifndef ___PLAYER_HPP_
#define ___PLAYER_HPP_

#include "Actor.hpp"
#include "Input.hpp"
#include "Entry.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"

#include <iostream>
#include <vector>

#define SPEED 10

/*####################################################
* プレイヤークラス
######################################################*/

//前方宣言
class Bullet;

class Player : public Actor
{
public:
	Player();	//コンストラクタ
	~Player();	//デストラクタ

	
	void Update()override;	//更新
	void Draw()override;	//描画
	
	// バレット
	void Bullet_Update();	//更新
	void Bullet_Draw();		//描画

	//プレイヤー
	void Player_Update();	//更新
	void Player_Draw();		//描画

	Box_Collision mCol;
private:

	int mSprite;		//プレイヤー　スプライト
	int mBullet_Sprite;	//バレット　スプライト

	int mSpeed;		//速度

	std::shared_ptr<Input> mInput;	//キー入力
	std::vector<Bullet> mBullet;	//バレット




};


#endif


