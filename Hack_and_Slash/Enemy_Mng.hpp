#ifndef ___ENEMY_MNG_HPP_
#define ___ENEMY_MNG_HPP_

#include "Enemy.hpp"
#include <vector>
#include <iostream>


//前方宣言
class Enemy;

/*####################################################
* エネミー管理
*
* 説明
* 敵の移動と行動する管理するクラス
######################################################*/
class Enemy_Mng {

public:

	Enemy_Mng();	//コンストラクタ
	~Enemy_Mng();	//デストラクタ


	void Update();	//更新
	void Draw();	//描画

	std::shared_ptr<std::vector<Enemy>> getEnemy();					//エネミー情報
	void ColPlayer(Player& player);									//プレイヤーとの当たり判定
	void ColBullet(std::shared_ptr<std::vector<Bullet>> bullet);	//バレットとの当たり判定

private:
	int Handle;	//スプライト
	std::shared_ptr<std::vector<Enemy>> enemy;	//エネミー　クラス



};

#endif;