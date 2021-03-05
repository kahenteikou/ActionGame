#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

#include "MapChip.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>

//前方宣言
class Player;
class MapChip;
class Bullet;
class Entry;
class Enemy;

/*####################################################
* ステージ描画
*
* 説明
* ステージを描画する
######################################################*/
class Stage
{
public:
	Stage(Entry *e,int Block_Handle, int Brick_Handle, int Shop_Handle);	//コンストラクタ
	~Stage();			//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	//当たり判定各種
	void ColPlayer(std::shared_ptr<Player> player);										//プレイヤーとの当たり判定
	void ColPlayer_Bullet(std::shared_ptr<std::vector<Bullet>> bullet);		//プレイヤーのバレットとの当たり判定
	void Scroll(std::shared_ptr<Player> player, std::shared_ptr<std::vector<Enemy>> enemey, std::shared_ptr<std::vector<Bullet>> bullet);	//画面スクロール
	void ColEnemy(std::shared_ptr<std::vector<Enemy>> enemy);			//エネミーとの当たり判定
	void ColEnemy_Bullet(std::shared_ptr<std::vector<Enemy>> enemy);	//エネミーのバレットとの当たり判定


private:

	std::vector<MapChip> mStage;	//マップデータ
	glm::ivec2 mStageSize;			//画面に描画するセル数
	glm::ivec2 mScroll_Vec;			//スクロールしている向き

	
	std::vector<std::vector<byte>> Stage_Grid;	//ステージ

	bool mGameStart;	//ゲームが始まって最初のフレームかかどうか？
	bool mIsShop;	//ショップが終わったかどうか？
	Entry* Owner;	//Entryクラス

};


#endif
	