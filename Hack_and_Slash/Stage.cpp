#include "Stage.hpp"

//コンストラクタ
Stage::Stage(Entry* e)
{
	Owner = e;
//	printf("screen X: %d\n", SCREEN_WIDTH / CELL);
//	printf("screen Y: %d\n",SCREEN_HEIGHT / CELL);

//	printf("stage X: %d\n", STAGE_WIDTH / CELL);
//	printf("stage Y: %d\n",STAGE_HEIGHT / CELL);

	mIsShop = false;	//ショップ中かどうか？


	//画面に描画するセル数
	mStageSize.x = STAGE_WIDTH / CELL;
	mStageSize.y = STAGE_HEIGHT / CELL;
	
	// ###### スプライトをロード

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
	unsigned char Stage_Grid[STAGE_HEIGHT / CELL][STAGE_WIDTH / CELL] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0},
		{0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,0,2,2,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//プレイヤーとの当たり判定
void Stage::ColPlayer(Player &player)
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		if (Box_Collision::Intersect(itr->mCol,player.mCol) == true)
		{
			switch (itr->mCol.getObjectType())
			{
				//ショップ
				case StageObjectType::Shop:
				{
					if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
					{
						player.setIsMenu(true);
						player.FixPos(itr->mCol.getPosition());
					}
				}
				break;

				//レンガとの当たり判定
				case StageObjectType::Brick:
				{					
					player.FixPos(itr->mCol.getPosition());
				}
				break;

				//ブロックとの当たり判定
				case StageObjectType::Block:
				{
					
					player.FixPos(itr->mCol.getPosition());
				}
				break;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//バレットとの当たり判定
void Stage::ColBullet(std::shared_ptr<std::vector<Bullet>> bullet)
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		MapChip chip = *itr;	//マップチップ
		for (std::vector<Bullet>::iterator b = bullet->begin(); b != bullet->end();)
		{
			if (Box_Collision::Intersect(chip.mCol, b->mCol) == true)
			{

				switch (chip.mCol.getObjectType())
				{
					//レンガとの当たり判定
				case StageObjectType::Brick:
				{
					chip.HP += -1;	//耐久値を減らす
					if (chip.HP < 0)
					{
						itr = mStage.erase(itr);	//ヒットしたブロックを消す
					}

					b->mIsHit = true;	//ヒットエフェクトを再生
					b->FixPos(chip.mCol.getPosition());	//バレットの座標を修正	
				}
				break;


				//レンガとの当たり判定
				case StageObjectType::Block:
				{
					b->mIsHit = true;	//ヒットエフェクトを再生
					b->FixPos(chip.mCol.getPosition());	//バレットの座標を修正	
				}
				break;


				}
			}

			//ヒットエフェクトが再生されたy要素を削除
			if (b->isDelete == true)
			{
				b = bullet->erase(b);
		//		printf("バレット削除\n");
			}
			else {
				b++;
			}
		}
	}
}

//画面スクロール
void Stage::ScrollMap(Player& player)
{
	//左右移動
	if (player.getPosition().x > (SCREEN_WIDTH - 100) + player.getSpeed() && player.getVector() == VECTOR_RIGHT) {
		//printf("Right\n");

		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{
		
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += -player.getSpeed();

			itr->setPosition(pos);
		}
	}
	else if (player.getPosition().x < ( 100 ) + player.getSpeed() && player.getVector() == VECTOR_LEFT)
	{
		//printf("Left\n");
		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += player.getSpeed();

			itr->setPosition(pos);
		}

		//上下移動
	}else if (player.getPosition().y > (SCREEN_HEIGHT - 100) + player.getSpeed() && player.getVector() == VECTOR_DOWN) {
		//printf("Dwon\n");

		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{

			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += -player.getSpeed();

			itr->setPosition(pos);
		}
	}
	else if (player.getPosition().y < (100) + player.getSpeed() && player.getVector() == VECTOR_UP)
	{
		//printf("Up\n");
		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += player.getSpeed();

			itr->setPosition(pos);
		}
	}
	else {


		//移動
		int speed = player.getSpeed();
		glm::ivec2 vec = player.getVector();
		glm::ivec2 pos = player.getPosition();
		pos.x += vec.x * speed;
		pos.y += vec.y * speed;

		player.setPosition(pos);
	}
}

//エネミーとの当たり判定
void Stage::ColEnemy(std::shared_ptr<std::vector<Enemy>> enemy)
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		MapChip chip = *itr;
		for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
		{
			//交差判定
			if (Box_Collision::Intersect(chip.mCol, itr->mCol) == true )
			{
				switch (chip.mCol.getObjectType())
				{

					//ブロック
				case StageObjectType::Block:
				{
					itr->FixPos(chip.mCol.getPosition());
					itr->setMove_Rand();
				}


				}
			}
		}
	}

}






//デストラクタ
Stage::~Stage()
{

}

