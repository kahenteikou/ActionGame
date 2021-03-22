#include "MapChip.hpp"
#include "Entry.hpp"
//コンストラクタ
MapChip::MapChip(Tag t, glm::vec2  pos, glm::vec2  colsize,int handle) : Actor(nullptr)
{


	position = pos;			//座標
	worldPosition = pos;	//ワールド座標
	sprite = handle;		//スプライト	
	//printf("%f\n",size.x);



	//当たり判定
	size.x = CELL;
	size.y = CELL;


//	mCol = std::make_shared<BoxCollision>();
//	mCol = std::make_shared<BoxCollision>();

	minValue = position;
	maxValue = position + size;
	

	mCol.setTag(t);			//タグ
	mCol.setMin(&minValue);	//最小値
	mCol.setMax(&maxValue);	//最大値


/*
	mCol->setTag(t);			//タグ
	mCol->setMin(&minValue);	//最小値
	mCol->setMax(&maxValue);	//最大値
	*/
	//printf("ああああ　%f %f\n", mCol->getMax().x, mCol->getMax().y);
//	printf("ああああ　%f %f\n", mCol->getMin().x, mCol->getMin().y);

}

//ワールド座標を取得
glm::vec2  MapChip::getWorldPosition()
{
	return worldPosition;
}






//デフォルトコンストラクタ
MapChip::MapChip() : Actor(nullptr)
{

}

void MapChip::Update()
{
	minValue = position;	
	maxValue = position + size;


}

void MapChip::Draw()
{
	DrawGraph((int)position.x, (int)position.y,sprite,true);
	DrawCircle(maxValue.x, maxValue.y, 5, GetColor(0, 255, 0), true);
	DrawCircle(minValue.x, minValue.y ,5, GetColor(255, 0, 0), true);

}


//デストラクタ
MapChip::~MapChip()
{

}
