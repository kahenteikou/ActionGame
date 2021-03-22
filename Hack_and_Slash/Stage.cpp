#include "Stage.hpp"
#include "Enemy_Mng.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;



//コンストラクタ
Stage::Stage(Entry* e, int Block_Handle, int Brick_Handle, int Shop_Handle)
{
	Owner = e;

	mStage = std::make_shared<std::vector<MapChip>>();

//	printf("screen X: %d\n", SCREEN_WIDTH / CELL);
//	printf("screen Y: %d\n",SCREEN_HEIGHT / CELL);

//	printf("stage X: %d\n", STAGE_WIDTH / CELL);
//	printf("stage Y: %d\n",STAGE_HEIGHT / CELL);

	mIsShop = false;	//ショップ中かどうか？
	mGameStart = false;

	mScroll_Vec = glm::ivec2(0,0);			//スクロールしている向き

	Stage_Grid = std::make_shared<std::vector<std::vector<byte>>>();

	//画面に描画するセル数
	mStageSize.x = STAGE_WIDTH / CELL;
	mStageSize.y = STAGE_HEIGHT / CELL;
	
	// ###### スプライトをロード

	//ブロック
	Block_sprite = Block_Handle;
	GetGraphSize(Block_sprite,&BlockSize.x, &BlockSize.y);	//サイズを取得

	//レンガ
	Brick_sprite = Brick_Handle;	
	GetGraphSize(Brick_sprite, &BrickSize.x, &BrickSize.y);	//サイズを取得

	//ショップ
	Shop_sprite = Shop_Handle;	
	GetGraphSize(Shop_sprite, &ShopSize.x, &ShopSize.y);	//サイズを取得


	// ##### ステージバイナリファイルをロード ##### 
	std::string filename = "\\Stage_Data";	//バイナリファイルの格納ディレクトリ
	std::string path = fs::current_path().string();
	path = path + filename;
	if (fs::exists(path) == false)
	{
		printf("Stage_Dataフォルダが存在しないため新規作成しました。\n");
	//	fs::create_directory(path);
	}
	else
	{
		printf("バイナリファイルをロード\n");
		
		for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
		{
			printf("%s\n", itr->path().string().c_str());

			FileNameList.push_back(itr->path().string());	//パスを追加			
		}
		printf("\n\n");
	}

}


//ステージを読み込み
void Stage::LoadStage()
{

	printf("LoadStage\n");
	mStage->clear();	//ステージをクリア

	// *** ステージロード ***
	glm::ivec2 StageSize = glm::ivec2(0, 0);	//画面サイズ
	FILE* fp = NULL;		//ファイルポインタ

//	fopen_s(&fp, "Assets/Stage/Debug_AI.bin", "rb");	//読み込みモードでファイルを開く
	fopen_s(&fp, "Assets/Stage/Debug.bin", "rb");	//読み込みモードでファイルを開く

	if (fp != NULL)
	{
		//printf("あああ\n");
		//ステージサイズを読み込む(先頭８バイト)
		fread(&StageSize.x, sizeof(int), 1, fp);
		fread(&StageSize.y, sizeof(int), 1, fp);

		for (int y = 0; y < StageSize.y; y++)
		{
			std::vector<byte> tmp;
			for (int x = 0; x < (int)StageSize.x; x++)
			{
				byte b = 0;
				fread(&b, sizeof(byte), 1, fp);
				tmp.push_back(b);

			}


			Stage_Grid->push_back(tmp);

		}

		fclose(fp);	//ファイルを閉じる
		
		//mStage->resize(StageSize.x * StageSize.y);
		

		//マップオブジェクトを設定
		for (int y = 0; y < StageSize.y; y++)
		{
			for (int x = 0; x < StageSize.x; x++)
			{
				switch (Stage_Grid->at(y).at(x))
				{
					//ブロック
					case 0x01:
					{
						mStage->push_back(MapChip(Tag::Block, glm::ivec2(x * CELL, y * CELL), BlockSize, Block_sprite));
						//printf("えええええ\n");

					}
					break;

					//レンガ
					case 0x02:
					{
						mStage->push_back(MapChip(Tag::Brick, glm::ivec2(x * CELL, y * CELL), BrickSize, Brick_sprite));
					}
					break;

					//ショップ
					case 0x03:
					{
						mStage->push_back(MapChip(Tag::Shop, glm::ivec2(x * CELL, y * CELL), ShopSize, Shop_sprite));
					}
					break;

					//なし
					default:
					{
					//	mStage->push_back(MapChip(StageObjectType::None, glm::ivec2(x * CELL, y * CELL), glm::ivec2(0, 0), -1));
					}break;

				}
				
				
			}
		}

		
	}
	else {
		printf("ファイルを読み込めません。\n");
	}


//	printf("%d , %d\n", mStage->at(0).getPosition().x, mStage->at(0).getPosition().y);


	//fclose(fp);

}




//新しいステージを読み込み
/*
* 全てのエネミーを破壊したら新しいステージを読み込み
*/
void Stage::setStage(std::shared_ptr<Enemy_Mng> enemy, std::shared_ptr<Player> player)
{
	if (enemy->getEnemyEmpty() == true)
	{
		printf("新しいステージ\n");
		enemy->newStage = true;
	}

	if (enemy->newStage == true)
	{
		//printf("ううううう\n");
		//printf("NewStage \n");
		LoadStage();		//ステージをロード
		player->setReset();	//座標をリセット
		mGameStart = false;	//初期スクロール
	}
}

//更新
void Stage::Update()
{
	for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
	{
		itr->Update();
	}
}

//描画
void Stage::Draw()
{
	for (int i = 0;  i < mStage->size(); i++)
	{
		mStage->at(i).Draw();		
	}


	
}

//プレイヤーとの当たり判定
void Stage::ColPlayer(std::shared_ptr<Player> player)
{
	
}

//ステージを取得
std::shared_ptr<std::vector<std::vector<byte>>> Stage::getStage()
{
	return Stage_Grid;
}

//プレイヤーのバレットとの当たり判定
void Stage::ColPlayer_Bullet(std::shared_ptr<Player> player)
{

}

//画面スクロール
void Stage::Scroll(std::shared_ptr<Player> player, std::shared_ptr<Enemy_Mng> enemy)
{

#define SCROLL_OFFSET_X ((int)200)
#define SCROLL_OFFSET_Y ((int)200)
	

	//最初のフレームの時
	if (mGameStart == false)
	{
		//X 補正
		if (player->stagePosition.x > (SCREEN_WIDTH - SCROLL_OFFSET_X))
		{
			int p = player->stagePosition.x - (SCREEN_WIDTH - SCROLL_OFFSET_X);
			printf("X %d\n",p);
			//プレイヤー補正
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -p;
				itr->setPosition(pos);

			}

			//プレイヤーバレット補正
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -p;
				itr->setPosition(pos);
			}


		}

		//Y 補正
		if (player->stagePosition.y > (SCREEN_HEIGHT - SCROLL_OFFSET_Y))
		{
			int p = player->stagePosition.y - (SCREEN_HEIGHT - SCROLL_OFFSET_Y);
			//printf("%d\n",p);
			printf("Y %d\n", p);

			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += -p;
				itr->setPosition(pos);
			}
		}
		mGameStart = true;
	}
	else {




		//左右移動
		if (player->getPosition().x > (SCREEN_WIDTH - SCROLL_OFFSET_X) + player->getSpeed() && player->getVector() == VECTOR_RIGHT)
		{

			//マップオブジェクトを移動
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -player->getSpeed();
				itr->setPosition(pos);
			}

			//エネミーのバレット移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				for (std::vector<Bullet>::iterator it = itr->getBullet()->begin(); it != itr->getBullet()->end(); it++)
				{
					glm::ivec2 pos;
					pos = it->getPosition();
					pos.x += -player->getSpeed();
					it->setPosition(pos);
				}
			}

			//エネミーの移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -player->getSpeed();
				itr->setPosition(pos);

			}

			//プレイヤーバレットを移動
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.x += -player->getSpeed();
				itr->setPosition(pos);
			}

			//プレイヤーを移動しない
			glm::ivec2 pos = player->getPosition();
			pos.x = player->getPosition().x - player->getSpeed();
			player->setPosition(pos);
		}
		else if (player->getPosition().x < (SCROLL_OFFSET_X)+player->getSpeed() && player->getVector() == VECTOR_LEFT)
		{


			//マップオブジェクトを移動
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += player->getSpeed();
				itr->setPosition(pos);
			}

			//エネミーのバレット移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				for (std::vector<Bullet>::iterator it = itr->getBullet()->begin(); it != itr->getBullet()->end(); it++)
				{
					glm::ivec2 pos;
					pos = it->getPosition();
					pos.x += player->getSpeed();
					it->setPosition(pos);
				}
			}

			//エネミーの移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += player->getSpeed();
				itr->setPosition(pos);

			}

			//プレイヤーバレットを移動
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.x += player->getSpeed();
				itr->setPosition(pos);
			}



			//プレイヤーを移動しない
			glm::ivec2 pos = player->getPosition();
			pos.x = player->getPosition().x + player->getSpeed();
			player->setPosition(pos);

			//上下移動
		}
		else if (player->getPosition().y > (SCREEN_HEIGHT - SCROLL_OFFSET_Y) + player->getSpeed() && player->getVector() == VECTOR_DOWN)
		{


			//マップオブジェクトを移動
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += -player->getSpeed();
				itr->setPosition(pos);
			}

			//エネミーのバレット移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				for (std::vector<Bullet>::iterator it = itr->getBullet()->begin(); it != itr->getBullet()->end(); it++)
				{
					glm::ivec2 pos;
					pos = it->getPosition();
					pos.y += -player->getSpeed();
					it->setPosition(pos);
				}
			}

			//エネミーの移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += -player->getSpeed();
				itr->setPosition(pos);

			}

			//プレイヤーバレットを移動
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.y += -player->getSpeed();
				itr->setPosition(pos);
			}

			//プレイヤーを移動しない
			glm::ivec2 pos = player->getPosition();
			pos.y = player->getPosition().y - player->getSpeed();
			player->setPosition(pos);
		}
		else if (player->getPosition().y < (SCROLL_OFFSET_Y)+player->getSpeed() && player->getVector() == VECTOR_UP)
		{

			//マップオブジェクトを移動
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += player->getSpeed();
				itr->setPosition(pos);
			}

			//エネミーのバレット移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				for (std::vector<Bullet>::iterator it = itr->getBullet()->begin(); it != itr->getBullet()->end(); it++)
				{
					glm::ivec2 pos;
					pos = it->getPosition();
					pos.y += player->getSpeed();
					it->setPosition(pos);
				}
			}

			//エネミーの移動
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += player->getSpeed();
				itr->setPosition(pos);

			}

			//プレイヤーバレットを移動
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
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
}

//エネミーとの当たり判定
void Stage::ColEnemy(std::shared_ptr<Enemy_Mng> enemy)
{




}




//エネミーのバレットとの当たり判定
void Stage::ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy)
{

	
}





//デストラクタ
Stage::~Stage()
{

}

