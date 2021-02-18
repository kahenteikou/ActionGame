#include "Stage.hpp"

//コンストラクタ
Stage::Stage()
{
	//printf("X: %d", SCREEN_WIDTH / CELL);
	//printf("Y: %d",SCREEN_HEIGHT / CELL);

	mIsShop = false;	//ショップ中かどうか？


	//画面に描画するセル数
	mStageSize.x = SCREEN_WIDTH / CELL;
	mStageSize.y = SCREEN_HEIGHT / CELL;
	
	//スプライトをロード

	//ブロック
	int Block_sprite = LoadGraph("Assets/Block.png");
	glm::ivec2 BlockSize;	
	GetGraphSize(Block_sprite,&BlockSize.x, &BlockSize.y);	//サイズを取得

	//レンガ
	int Brick_sprite = LoadGraph("Assets/Brick.png");
	glm::ivec2 BrickSize;	
	GetGraphSize(Brick_sprite, &BrickSize.x, &BrickSize.y);	//サイズを取得

	//ショップ
	int Shop_sprite = LoadGraph("Assets/Shop.png");
	glm::ivec2 ShopSize;
	GetGraphSize(Brick_sprite, &ShopSize.x, &ShopSize.y);	//サイズを取得

	//ステージ
	unsigned char Stage_Grid[SCREEN_HEIGHT / CELL][SCREEN_WIDTH / CELL] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	//マップオブジェクトを設定
	for (int y = 0; y < mStageSize.y; y++)
	{
		for (int x = 0; x < mStageSize.x; x++)
		{			
			switch (Stage_Grid[y][x])
			{
				//レンガ
				case 1:
				{
					mStage.push_back(MapChip(StageObjectType::Brick,glm::ivec2(x * CELL, y * CELL),BrickSize,Brick_sprite));
				}
				break;

				//ブロック
				case 2:
				{
					mStage.push_back(MapChip(StageObjectType::Block, glm::ivec2(x * CELL, y * CELL), BlockSize, Block_sprite));
				}
				break;

				//ショップ
				case 3:
				{
					mStage.push_back(MapChip(StageObjectType::Shop, glm::ivec2(x * CELL, y * CELL), ShopSize, Shop_sprite));
				}
				break;
			}
		}
	}
}

//更新
void Stage::Update()
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		itr->Update();
	}
}

//描画
void Stage::Draw()
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		itr->Draw();
	}

}

//当たり判定
void Stage::ColPlayer(Player &player)
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		if (Box_Collision::Intersect(itr->mCol,player.mCol) == true)
		{

			switch (itr->mCol.getObjectType())
			{

				//ショップ
				case StageObjectType::Shop :
				{
				
					player.setIsMenu(true);
				
					player.FixPos(itr->mCol.getPosition());
				}
				break;




				//レンガとの当たり判定
				case StageObjectType::Brick:
				{
					
					player.FixPos(itr->mCol.getPosition());
				}
				break;


			}








		}
	}

}




//デストラクタ
Stage::~Stage()
{

}

