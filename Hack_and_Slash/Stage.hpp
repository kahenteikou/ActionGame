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
	Stage(Entry *e);	//コンストラクタ
	~Stage();			//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	void ColPlayer(Player &player);									//プレイヤーとの当たり判定
	void ColBullet(std::shared_ptr<std::vector<Bullet>> bullet);	//バレットとの当たり判定
	void ScrollMap(Player& player);									//画面スクロール
	void ColEnemy(std::shared_ptr<std::vector<Enemy>> enemy);		//エネミーとの当たり判定




private:

	std::vector<MapChip> mStage;	//マップデータ
	glm::ivec2 mStageSize;			//画面に描画するセル数
	
	bool mIsShop;	//ショップが終わったかどうか？
	Entry* Owner;	//Entryクラス

};


#endif
	