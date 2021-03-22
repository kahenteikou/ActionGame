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
	MapChip(Tag t, glm::ivec2 pos, glm::ivec2 size, int handle);	//コンストラクタ
	MapChip();	//デフォルトコンストラクタ

	~MapChip();																//デストラクタ


	glm::ivec2 getWorldPosition();	//ワールド座標を取得
	void Update();	//計算
	void Draw();	//描画
	
	//void setObjectType(StageObjectType type);	//オブジェクトタイプを設定
	void setSize(glm::ivec2 size);				//サイズを設定
	void setHandle(int handle);					//ハンドルを設定



	glm::ivec2 worldPosition;	//ワールド座標
	std::shared_ptr<BoxCollision> mCol;
private:
	int mSprite;			//スプライト

};


#endif
