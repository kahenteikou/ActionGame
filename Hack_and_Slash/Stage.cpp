#include "Stage.hpp"
#include "Enemy_Mng.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;



//�R���X�g���N�^
Stage::Stage(Entry* e, int Block_Handle, int Brick_Handle, int Shop_Handle)
{
	Owner = e;

	mStage = std::make_shared<std::vector<MapChip>>();

//	printf("screen X: %d\n", SCREEN_WIDTH / CELL);
//	printf("screen Y: %d\n",SCREEN_HEIGHT / CELL);

//	printf("stage X: %d\n", STAGE_WIDTH / CELL);
//	printf("stage Y: %d\n",STAGE_HEIGHT / CELL);

	mIsShop = false;	//�V���b�v�����ǂ����H
	mGameStart = false;

	mScroll_Vec = glm::ivec2(0,0);			//�X�N���[�����Ă������

	Stage_Grid = std::make_shared<std::vector<std::vector<byte>>>();

	//��ʂɕ`�悷��Z����
	mStageSize.x = STAGE_WIDTH / CELL;
	mStageSize.y = STAGE_HEIGHT / CELL;
	
	// ###### �X�v���C�g�����[�h

	//�u���b�N
	Block_sprite = Block_Handle;
	GetGraphSize(Block_sprite,&BlockSize.x, &BlockSize.y);	//�T�C�Y���擾

	//�����K
	Brick_sprite = Brick_Handle;	
	GetGraphSize(Brick_sprite, &BrickSize.x, &BrickSize.y);	//�T�C�Y���擾

	//�V���b�v
	Shop_sprite = Shop_Handle;	
	GetGraphSize(Shop_sprite, &ShopSize.x, &ShopSize.y);	//�T�C�Y���擾


	// ##### �X�e�[�W�o�C�i���t�@�C�������[�h ##### 
	std::string filename = "\\Stage_Data";	//�o�C�i���t�@�C���̊i�[�f�B���N�g��
	std::string path = fs::current_path().string();
	path = path + filename;
	if (fs::exists(path) == false)
	{
		printf("Stage_Data�t�H���_�����݂��Ȃ����ߐV�K�쐬���܂����B\n");
	//	fs::create_directory(path);
	}
	else
	{
		printf("�o�C�i���t�@�C�������[�h\n");
		
		for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
		{
			printf("%s\n", itr->path().string().c_str());

			FileNameList.push_back(itr->path().string());	//�p�X��ǉ�			
		}
		printf("\n\n");
	}

}


//�X�e�[�W��ǂݍ���
void Stage::LoadStage()
{

	printf("LoadStage\n");
	mStage->clear();	//�X�e�[�W���N���A

	// *** �X�e�[�W���[�h ***
	glm::ivec2 StageSize = glm::ivec2(0, 0);	//��ʃT�C�Y
	FILE* fp = NULL;		//�t�@�C���|�C���^

//	fopen_s(&fp, "Assets/Stage/Debug_AI.bin", "rb");	//�ǂݍ��݃��[�h�Ńt�@�C�����J��
	fopen_s(&fp, "Assets/Stage/Debug.bin", "rb");	//�ǂݍ��݃��[�h�Ńt�@�C�����J��

	if (fp != NULL)
	{
		//printf("������\n");
		//�X�e�[�W�T�C�Y��ǂݍ���(�擪�W�o�C�g)
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

		fclose(fp);	//�t�@�C�������
		
		//mStage->resize(StageSize.x * StageSize.y);
		

		//�}�b�v�I�u�W�F�N�g��ݒ�
		for (int y = 0; y < StageSize.y; y++)
		{
			for (int x = 0; x < StageSize.x; x++)
			{
				switch (Stage_Grid->at(y).at(x))
				{
					//�u���b�N
					case 0x01:
					{
						mStage->push_back(MapChip(Tag::Block, glm::ivec2(x * CELL, y * CELL), BlockSize, Block_sprite));
						//printf("����������\n");

					}
					break;

					//�����K
					case 0x02:
					{
						mStage->push_back(MapChip(Tag::Brick, glm::ivec2(x * CELL, y * CELL), BrickSize, Brick_sprite));
					}
					break;

					//�V���b�v
					case 0x03:
					{
						mStage->push_back(MapChip(Tag::Shop, glm::ivec2(x * CELL, y * CELL), ShopSize, Shop_sprite));
					}
					break;

					//�Ȃ�
					default:
					{
					//	mStage->push_back(MapChip(StageObjectType::None, glm::ivec2(x * CELL, y * CELL), glm::ivec2(0, 0), -1));
					}break;

				}
				
				
			}
		}

		
	}
	else {
		printf("�t�@�C����ǂݍ��߂܂���B\n");
	}


//	printf("%d , %d\n", mStage->at(0).getPosition().x, mStage->at(0).getPosition().y);


	//fclose(fp);

}




//�V�����X�e�[�W��ǂݍ���
/*
* �S�ẴG�l�~�[��j�󂵂���V�����X�e�[�W��ǂݍ���
*/
void Stage::setStage(std::shared_ptr<Enemy_Mng> enemy, std::shared_ptr<Player> player)
{
	if (enemy->getEnemyEmpty() == true)
	{
		printf("�V�����X�e�[�W\n");
		enemy->newStage = true;
	}

	if (enemy->newStage == true)
	{
		//printf("����������\n");
		//printf("NewStage \n");
		LoadStage();		//�X�e�[�W�����[�h
		player->setReset();	//���W�����Z�b�g
		mGameStart = false;	//�����X�N���[��
	}
}

//�X�V
void Stage::Update()
{
	for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
	{
		itr->Update();
	}
}

//�`��
void Stage::Draw()
{
	for (int i = 0;  i < mStage->size(); i++)
	{
		mStage->at(i).Draw();		
	}


	
}

//�v���C���[�Ƃ̓����蔻��
void Stage::ColPlayer(std::shared_ptr<Player> player)
{
	
}

//�X�e�[�W���擾
std::shared_ptr<std::vector<std::vector<byte>>> Stage::getStage()
{
	return Stage_Grid;
}

//�v���C���[�̃o���b�g�Ƃ̓����蔻��
void Stage::ColPlayer_Bullet(std::shared_ptr<Player> player)
{

}

//��ʃX�N���[��
void Stage::Scroll(std::shared_ptr<Player> player, std::shared_ptr<Enemy_Mng> enemy)
{

#define SCROLL_OFFSET_X ((int)200)
#define SCROLL_OFFSET_Y ((int)200)
	

	//�ŏ��̃t���[���̎�
	if (mGameStart == false)
	{
		//X �␳
		if (player->stagePosition.x > (SCREEN_WIDTH - SCROLL_OFFSET_X))
		{
			int p = player->stagePosition.x - (SCREEN_WIDTH - SCROLL_OFFSET_X);
			printf("X %d\n",p);
			//�v���C���[�␳
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -p;
				itr->setPosition(pos);

			}

			//�v���C���[�o���b�g�␳
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -p;
				itr->setPosition(pos);
			}


		}

		//Y �␳
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




		//���E�ړ�
		if (player->getPosition().x > (SCREEN_WIDTH - SCROLL_OFFSET_X) + player->getSpeed() && player->getVector() == VECTOR_RIGHT)
		{

			//�}�b�v�I�u�W�F�N�g���ړ�
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -player->getSpeed();
				itr->setPosition(pos);
			}

			//�G�l�~�[�̃o���b�g�ړ�
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

			//�G�l�~�[�̈ړ�
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += -player->getSpeed();
				itr->setPosition(pos);

			}

			//�v���C���[�o���b�g���ړ�
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.x += -player->getSpeed();
				itr->setPosition(pos);
			}

			//�v���C���[���ړ����Ȃ�
			glm::ivec2 pos = player->getPosition();
			pos.x = player->getPosition().x - player->getSpeed();
			player->setPosition(pos);
		}
		else if (player->getPosition().x < (SCROLL_OFFSET_X)+player->getSpeed() && player->getVector() == VECTOR_LEFT)
		{


			//�}�b�v�I�u�W�F�N�g���ړ�
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += player->getSpeed();
				itr->setPosition(pos);
			}

			//�G�l�~�[�̃o���b�g�ړ�
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

			//�G�l�~�[�̈ړ�
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.x += player->getSpeed();
				itr->setPosition(pos);

			}

			//�v���C���[�o���b�g���ړ�
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.x += player->getSpeed();
				itr->setPosition(pos);
			}



			//�v���C���[���ړ����Ȃ�
			glm::ivec2 pos = player->getPosition();
			pos.x = player->getPosition().x + player->getSpeed();
			player->setPosition(pos);

			//�㉺�ړ�
		}
		else if (player->getPosition().y > (SCREEN_HEIGHT - SCROLL_OFFSET_Y) + player->getSpeed() && player->getVector() == VECTOR_DOWN)
		{


			//�}�b�v�I�u�W�F�N�g���ړ�
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += -player->getSpeed();
				itr->setPosition(pos);
			}

			//�G�l�~�[�̃o���b�g�ړ�
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

			//�G�l�~�[�̈ړ�
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += -player->getSpeed();
				itr->setPosition(pos);

			}

			//�v���C���[�o���b�g���ړ�
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.y += -player->getSpeed();
				itr->setPosition(pos);
			}

			//�v���C���[���ړ����Ȃ�
			glm::ivec2 pos = player->getPosition();
			pos.y = player->getPosition().y - player->getSpeed();
			player->setPosition(pos);
		}
		else if (player->getPosition().y < (SCROLL_OFFSET_Y)+player->getSpeed() && player->getVector() == VECTOR_UP)
		{

			//�}�b�v�I�u�W�F�N�g���ړ�
			for (std::vector<MapChip>::iterator itr = mStage->begin(); itr != mStage->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += player->getSpeed();
				itr->setPosition(pos);
			}

			//�G�l�~�[�̃o���b�g�ړ�
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

			//�G�l�~�[�̈ړ�
			for (std::vector<Enemy>::iterator itr = enemy->getEnemy()->begin(); itr != enemy->getEnemy()->end(); itr++)
			{
				glm::ivec2 pos;
				pos = itr->getPosition();
				pos.y += player->getSpeed();
				itr->setPosition(pos);

			}

			//�v���C���[�o���b�g���ړ�
			for (std::vector<Bullet>::iterator itr = player->getBullet()->begin(); itr != player->getBullet()->end(); itr++)
			{
				glm::ivec2 pos = itr->getPosition();
				pos.y += player->getSpeed();
				itr->setPosition(pos);
			}



			//�v���C���[���ړ����Ȃ�
			glm::ivec2 pos = player->getPosition();
			pos.y = player->getPosition().y + player->getSpeed();
			player->setPosition(pos);
		}
		else {

		}

	}
}

//�G�l�~�[�Ƃ̓����蔻��
void Stage::ColEnemy(std::shared_ptr<Enemy_Mng> enemy)
{




}




//�G�l�~�[�̃o���b�g�Ƃ̓����蔻��
void Stage::ColEnemy_Bullet(std::shared_ptr<Enemy_Mng> enemy)
{

	
}





//�f�X�g���N�^
Stage::~Stage()
{

}

