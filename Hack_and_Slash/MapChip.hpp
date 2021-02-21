#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

#include "Entry.hpp"
#include "Actor.hpp"
#include "Collision.hpp"

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

class MapChip : public Actor
{
public:
	MapChip(StageObjectType t,glm::ivec2 pos,glm::ivec2 size,int handle);	//コンストラクタ
	~MapChip();																//デストラクタ

	void Update();	//計算
	void Draw();	//描画
	

	int HP;
	Box_Collision mCol;
private:
	int mSprite;			//スプライト

};


#endif
