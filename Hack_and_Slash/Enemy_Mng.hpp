#ifndef ___ENEMY_MNG_HPP_
#define ___ENEMY_MNG_HPP_

#include "Enemy.hpp"
#include <vector>
#include <iostream>


class Enemy;

class Enemy_Mng {

public:

	Enemy_Mng();	//コンストラクタ
	~Enemy_Mng();	//デストラクタ


	void Update();	//更新
	void Draw();	//描画

	std::shared_ptr<std::vector<Enemy>> getEnemy();	//エネミー情報

private:
	int Handle;	//スプライト
	std::shared_ptr<std::vector<Enemy>> enemy;	//エネミー　クラス



};

#endif;