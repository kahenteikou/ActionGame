#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "glm/glm.hpp"
#include <dxlib.h>
#include <iostream>

#include "Actor.hpp"
#include "Collision.hpp"

/*####################################################
* マップチップクラス
*
* 説明
* ステージのマップチップの情報
######################################################*/

class MapChip : public Actor
{
public:
	MapChip(Tag t, glm::vec2  pos, glm::vec2  colsize, int handle);	//コンストラクタ
	MapChip();	//デフォルトコンストラクタ

	~MapChip();																//デストラクタ


	glm::vec2  getWorldPosition();	//ワールド座標を取得
	void Update();	//計算
	void Draw();	//描画
	
	
	void setSize(glm::vec2  size);				//サイズを設定
	void setHandle(int handle);					//ハンドルを設定



	//std::shared_ptr<BoxCollision> mCol;
	BoxCollision mCol;
private:
	int sprite;			//スプライト
	glm::vec2  worldPosition;	//ワールド座標

	glm::vec2 minValue;	//
	glm::vec2 maxValue;	//



};


#endif
