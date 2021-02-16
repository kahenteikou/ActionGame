#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "glm/glm.hpp"
#include "Actor.hpp"
#include "Collision.hpp"
#include "dxlib.h"





/*####################################################
* マップチップクラス
*
* 説明
* ステージのマップチップの情報
######################################################*/

//ステージのオブジェクトの種別
enum class StageObjectType
{
	None,


	Enemy,
	Player,
	Item,
	
	Block,
	Brick,

	Shop,

};

class Box_Collision;

class MapChip : public Actor
{
public:
	MapChip(StageObjectType t,glm::ivec2 pos,glm::ivec2 size,int handle);	//コンストラクタ
	~MapChip();																//デストラクタ

	void Update();	//計算
	void Draw();	//描画
	


	Box_Collision mCol;
private:
	int mSprite;			//スプライト

};


#endif
