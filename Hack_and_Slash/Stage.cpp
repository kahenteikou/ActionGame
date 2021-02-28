#include "Stage.hpp"

//コンストラクタ
Stage::Stage(Entry* e, int Block_Handle, int Brick_Handle, int Shop_Handle)
{
	Owner = e;
//	printf("screen X: %d\n", SCREEN_WIDTH / CELL);
//	printf("screen Y: %d\n",SCREEN_HEIGHT / CELL);

//	printf("stage X: %d\n", STAGE_WIDTH / CELL);
//	printf("stage Y: %d\n",STAGE_HEIGHT / CELL);

	mIsShop = false;	//ショップ中かどうか？
	mGameStart = false;

	//画面に描画するセル数
	mStageSize.x = STAGE_WIDTH / CELL;
	mStageSize.y = STAGE_HEIGHT / CELL;
	
	// ###### スプライトをロード

	//ブロック
	int Block_sprite = Block_Handle;
	glm::ivec2 BlockSize;	
	GetGraphSize(Block_sprite,&BlockSize.x, &BlockSize.y);	//サイズを取得

	//レンガ
	int Brick_sprite = Brick_Handle;
	glm::ivec2 BrickSize;	
	GetGraphSize(Brick_sprite, &BrickSize.x, &BrickSize.y);	//サイズを取得

	//ショップ
	int Shop_sprite = Shop_Handle;
	glm::ivec2 ShopSize;
	GetGraphSize(Shop_sprite, &ShopSize.x, &ShopSize.y);	//サイズを取得





	// *** ステージロード ***
	glm::ivec2 StageSize;	//画面サイズ
	FILE* fp = NULL;		//ファイルポインタ

	fopen_s(&fp,"sample.bin","rb");	//読み込みモードでファイルを開く
	byte Stage_Grid[STAGE_HEIGHT / CELL][STAGE_WIDTH / CELL];	//ステージ
	if (fp != NULL) {
		//ステージサイズを読み込む(先頭８バイト)
		fread(&StageSize.x, sizeof(int), 1, fp);
		fread(&StageSize.y, sizeof(int), 1, fp);

		for (int y = 0; y < (int)(STAGE_HEIGHT / CELL); y++)
		{
			for (int x = 0; x < (int)(STAGE_WIDTH / CELL); x++)
			{
				byte b = 0;
				fread(&b, sizeof(byte), 1, fp);
				if (b == 1)
				{
					Stage_Grid[y][x] = b;
				}
			}

		}
		fclose(fp);

	}
	else {
		printf("ファイルを読み込めません。\n");
	}

	/*
	unsigned char Stage_Grid[STAGE_HEIGHT / CELL][STAGE_WIDTH / CELL] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,},
		{0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	};
	*/

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

//プレイヤーとの当たり判定
void Stage::ColPlayer(std::shared_ptr<Player> player)
{
	for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
	{
		if (Box_Collision::Intersect(itr->mCol,player->mCol) == true)
		{
			switch (itr->mCol.getObjectType())
			{
				//ショップ
				case StageObjectType::Shop:
				{
					if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
					{
						player->setIsMenu(true);
						player->FixPos(itr->mCol.getPosition());
					}
				}
				break;

				//レンガとの当たり判定
				case StageObjectType::Brick:
				{					
					player->FixPos(itr->mCol.getPosition());
				}
				break;

				//ブロックとの当たり判定
				case StageObjectType::Block:
				{
					
					player->FixPos(itr->mCol.getPosition());
				}
				break;
			}
		}
	}
}


//バレットとの当たり判定
void Stage::ColPlayer_Bullet(std::shared_ptr<std::vector<Bullet>> bullet)
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


				//ブロックとの当たり判定
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
void Stage::Scroll(std::shared_ptr<Player> player, std::shared_ptr<std::vector<Enemy>> enemy, std::shared_ptr<std::vector<Bullet>> bullet)
{

#define SCROLL_OFFSET_X ((int)200)
#define SCROLL_OFFSET_Y ((int)200)


	//最初のフレームの時
	if (mGameStart == false)
	{
		//X 補正
		if (player->mStagePosition.x > (SCREEN_WIDTH - SCROLL_OFFSET_X))
		{
			int p = player->mStagePosition.x - (SCREEN_WIDTH - SCROLL_OFFSET_X);

			for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -p;
				itr->setPosition(pos);
			}	
		}

		//Y 補正
		if (player->mStagePosition.y > (SCREEN_HEIGHT - SCROLL_OFFSET_Y))
		{
			int p = player->mStagePosition.y - (SCREEN_HEIGHT - SCROLL_OFFSET_Y);
			//printf("%d\n",p);

			for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += -p;
				itr->setPosition(pos);
			}
		}
		mGameStart = true;
	}




	//左右移動
	if (player->getPosition().x > (SCREEN_WIDTH - SCROLL_OFFSET_X) + player->getSpeed() && player->getVector() == VECTOR_RIGHT)
	{

		//マップオブジェクトを移動
		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += -player->getSpeed();
			itr->setPosition(pos);
		}

		//エネミーを移動
		for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += -player->getSpeed();
			itr->setPosition(pos);
		}

		//バレットを移動
		for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += -player->getSpeed();
			itr->setPosition(pos);
		}

		//プレイヤーを移動しない
		glm::ivec2 pos = player->getPosition();
		pos.x = player->getPosition().x - player->getSpeed();
		player->setPosition(pos);
	}
	else if (player->getPosition().x < (SCROLL_OFFSET_X) + player->getSpeed() && player->getVector() == VECTOR_LEFT)
	{

		//マップオブジェクトを移動
		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += player->getSpeed();
			itr->setPosition(pos);
		}
		
		//エネミーを移動
		for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += player->getSpeed();
			itr->setPosition(pos);
		}

		//バレットを移動
		for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.x += player->getSpeed();
			itr->setPosition(pos);
		}



		//プレイヤーを移動しない
		glm::ivec2 pos = player->getPosition();
		pos.x = player->getPosition().x + player->getSpeed();
		player->setPosition(pos);

		//上下移動
	}else if (player->getPosition().y > (SCREEN_HEIGHT - SCROLL_OFFSET_Y) + player->getSpeed() && player->getVector() == VECTOR_DOWN)
	{
		//マップオブジェクトを移動
		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{	
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += -player->getSpeed();
			itr->setPosition(pos);
		}
		
		//エネミーを移動
		for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += -player->getSpeed();
			itr->setPosition(pos);

		}

		//バレットを移動
		for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += -player->getSpeed();
			itr->setPosition(pos);
		}

		//プレイヤーを移動しない
		glm::ivec2 pos = player->getPosition();
		pos.y = player->getPosition().y - player->getSpeed();
		player->setPosition(pos);
	}
	else if (player->getPosition().y < (SCROLL_OFFSET_Y) + player->getSpeed() && player->getVector() == VECTOR_UP)
	{

		//マップオブジェクトを移動
		for (std::vector<MapChip>::iterator itr = mStage.begin(); itr != mStage.end(); itr++)
		{	
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += player->getSpeed();
			itr->setPosition(pos);
		}

		//エネミーを移動
		for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += player->getSpeed();
			itr->setPosition(pos);
		}


		//バレットを移動
		for (std::vector<Bullet>::iterator itr = bullet->begin(); itr != bullet->end(); itr++)
		{
			glm::ivec2 pos;
			pos = itr->getPosition();
			pos.y += player->getSpeed();
			itr->setPosition(pos);
		}



		//プレイヤーを移動しない
		glm::ivec2 pos = player->getPosition();
		pos.y = player->getPosition().y + player->getSpeed();
		player->setPosition(pos);
	}
	else {
		
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
					itr->FixPos(chip.mCol.getPosition());	//座標を修正
					itr->setMove_Rand();					//乱数を再設定
					itr->setMovePixel();					//移動量をリセット
				}break;

					//レンガ
				case StageObjectType::Brick:
				{
					itr->FixPos(chip.mCol.getPosition());	//座標を修正
					itr->setMove_Rand();					//乱数を再設定
					itr->setMovePixel();					//移動量をリセット

				}break;


				}
			}
		}
	}
}




//エネミーのバレットとの当たり判定
void Stage::ColEnemy_Bullet(std::shared_ptr<std::vector<Enemy>> enemy)
{
	//エネミー
	for (std::vector<Enemy>::iterator itr = enemy->begin(); itr != enemy->end(); itr++)
	{
		Enemy ene = *itr;

		//バレット
		for (std::vector<Bullet>::iterator it = ene.getBullet()->begin(); it != ene.getBullet()->end(); it++)
		{
			Bullet b = *it;

			//マップチップ
			for (std::vector<MapChip>::iterator i = mStage.begin(); i != mStage.end(); i++)
			{
				if (Box_Collision::Intersect(b.mCol, i->mCol) == true)
				{
					
					it->FixPos(i->mCol.getPosition());
					it->mIsHit = true;
				}
			}
		}
	}
}





//デストラクタ
Stage::~Stage()
{

}

