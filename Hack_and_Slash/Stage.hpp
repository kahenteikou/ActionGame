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
class Enemy_Mng;

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
	
	std::shared_ptr<std::vector<std::vector<byte>>> getStage();

	//当たり判定 各種

	void ColPlayer(std::shared_ptr<Player> player);			//プレイヤーとの当たり判定
	void ColPlayer_Bullet(std::shared_ptr<Player> player);	//プレイヤーのバレットとの当たり判定

	void ColEnemy(std::shared_ptr<Enemy_Mng> enemy);		//エネミーとの当たり判定
	void ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy);	//エネミーのバレットとの当たり判定

	void setStage(std::shared_ptr<Enemy_Mng> enemy, std::shared_ptr<Player> player);		//ステージを読み込み


	void Scroll(std::shared_ptr<Player> player, std::shared_ptr<Enemy_Mng> enemy);	//画面スクロール

	

private:

	std::shared_ptr<std::vector<MapChip>> mStage;	//マップデータ
	glm::vec2  mStageSize;			//画面に描画するセル数
	glm::vec2  mScroll_Vec;			//スクロールしている向き

	

	void LoadStage();	//ステージを読み込む
	std::shared_ptr<std::vector<std::vector<byte>>> Stage_Grid;	//ステージ
	glm::vec2  offsetCol;
	int col = 0;
	bool mGameStart;	//ゲームが始まって最初のフレームかかどうか？
	bool mIsShop;	//ショップが終わったかどうか？
	Entry* Owner;	//Entryクラス

	std::vector<std::string> FileNameList;	//ステージファイルのリスト

	//サイズ関係
	glm::vec2  BlockSize;
	glm::vec2  BrickSize;
	glm::vec2  ShopSize;

	//スプライト
	int Block_sprite;	
	int Brick_sprite;
	int Shop_sprite;

};


#endif
	