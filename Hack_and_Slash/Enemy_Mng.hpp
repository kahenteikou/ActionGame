#ifndef ___ENEMY_MNG_HPP_
#define ___ENEMY_MNG_HPP_

#include "Enemy.hpp"
#include <vector>
#include <iostream>


//前方宣言
class Enemy;
class Player;
class MapChip;
class Stage;
/*####################################################
* エネミー管理
*
* 説明
* 敵の移動と行動する管理するクラス
######################################################*/
class Enemy_Mng {

public:

	Enemy_Mng(int Enemy_Handle, int Enemy_Bullet_Hanlde, int Stage_HitEffect_Handle[3], int Player_HitEffect_Handle[3]);	//コンストラクタ
	~Enemy_Mng();	//デストラクタ


	void Update();	//更新
	void Draw();	//描画
	int getEnemyNum();

	void setEnemy(std::shared_ptr<Stage> stage);	//エネミーを出現


	std::shared_ptr<std::vector<Enemy>> getEnemy();					//エネミー情報
	
	void ColPlayer_Bullet(std::shared_ptr<Player> player);			//プレイヤーとバレットとの当たり判定
	bool newStage;	//新しいステージかどうか？

private:
	

	int mEnemy_sprite;
	int mEnemy_Bullet_sprite;
	int mStage_HitEffect_sprite[3];
	int mPlayer_HitEffect_sprite[3];



	std::shared_ptr<std::vector<Enemy>> enemy;	//エネミー　クラス


};

#endif;