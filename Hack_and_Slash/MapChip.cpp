#include "MapChip.hpp"

//コンストラクタ
MapChip::MapChip(Tag t, glm::ivec2 pos, glm::ivec2 size,int handle) : Actor(nullptr)
{

	position = pos;			//座標
	worldPosition = position;	//ワールド座標
	size = size;				//サイズ
	mSprite = handle;			//スプライト	
	

	mCol = std::make_shared<BoxCollision>();

	



}

//ワールド座標を取得
glm::ivec2 MapChip::getWorldPosition()
{
	return worldPosition;
}


//デフォルトコンストラクタ
MapChip::MapChip() : Actor(nullptr)
{

}

void MapChip::Update()
{
	
	

}

void MapChip::Draw()
{
	DrawGraph(position.x, position.y,mSprite,true);
}


//デストラクタ
MapChip::~MapChip()
{

}
