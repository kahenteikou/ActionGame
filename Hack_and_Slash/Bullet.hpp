#ifndef ___BULLET_HPP_
#define ___BULLET_HPP_

#include "DxLib.h"
#include "glm/glm.hpp"
#include "Actor.hpp"
#include "Entry.hpp"
#include "Collision.hpp"

#include "Animation.hpp"


#define BULLET_EFFECT_SPEED  30//ヒットエフェクトの再生速度

/*####################################################
* バレット(弾)
*
* 説明
* vectorで管理
* プレイヤーの攻撃
* 
######################################################*/

class Bullet : public Actor
{
public:

	/*コンストラクタ引数
	* 
	*　座標
	* 方向
	* バレットのハンドル
	* マップにヒットしたときのエフェクト
	* エネミーとヒットした時のエフェクト 
	*/


	Bullet(glm::ivec2 pos, glm::ivec2 vec, int handle, int MapEffect_Handle[3], int EnemyEffect_Handle[3]);	//コンストラクタ
	~Bullet();																								//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	void FixPos(glm::ivec2 pos);	//座標を修正

	BoxCollision mCol;	//当たり判定

	
private:
	Animation anim;			//アニメーションクラス
	int sprite;			//スプライト
	bool isMapHIt;			//マップとヒットしたかどうか？
	bool isEenemyHit;		//エネミーとヒットしたかどうか？
	bool isDelete;			//削除するかどうか？

	int mapEffectSprite[3];	// マップヒットのエフェクトスプライト
	int enemyEffectSprite[3];	// エネミーヒットのエフェクトスプライト

	int speed;				//バレットの速度
	
};


#endif






