#include "Game_Scene.hpp"

//�R���X�g���N�^
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry �N���X


	// #####�@�X�v���C�g�����[�h #####

//	int Player_Handle = Owner->LoadSprite("Assets/Player/Player_0.png");	//�v���C���[

	int Player_Handle[8];
	LoadDivGraph("Sprite_Data/Player.png", 8, 8, 1, CELL, CELL, Player_Handle);	//�v���C���[

	int Enemy_Handle = Owner->LoadSprite("Assets/Enemy.png");					//�G�l�~�[		

	int Player_Bullet_Handle = Owner->LoadSprite("Assets/Player_Bullet.png");	//�v���C���[�̃o���b�g
	int Enemy_Bullet_Handle = Owner->LoadSprite("Assets/Enemy_Bullet.png");		//�G�l�~�[�̃o���b�g

	int Block_Handle = Owner->LoadSprite("Assets/Block.png");	//�u���b�N	
	int Brick_Handle = Owner->LoadSprite("Assets/Brick.png");	//�����K
	int Shop_Handle = Owner->LoadSprite("Assets/Shop.png");		//�V���b�v
	
	//�q�b�g�G�t�F�N�g
	int Enemy_HitEffect_Handle[3];	//�G�l�~�[
	int Stage_HitEffect_Handle[3];	//�X�e�[�W
	int Player_HitEffect_Handle[3];	//�v���C���[
	LoadDivGraph("Assets/Enemy_Explosion.png", 3, 3, 1, CELL, CELL, Enemy_HitEffect_Handle);	//�G�l�~�[
	LoadDivGraph("Assets/Stage_Explosion.png", 3, 3, 1, CELL, CELL, Stage_HitEffect_Handle);	//�X�e�[�W
	LoadDivGraph("Assets/Player_Explosion.png", 3, 3, 1, CELL, CELL,Player_HitEffect_Handle);	//�v���C���[
	

	player = std::make_shared<Player>(Owner,Player_Handle, Player_Bullet_Handle,Enemy_HitEffect_Handle, Stage_HitEffect_Handle);	//�v���C���[
	stage = std::make_shared<Stage>(Owner,Block_Handle, Brick_Handle, Shop_Handle);													//�X�e�[�W
	shop = std::make_shared<Shop>(Owner);																							//�V���b�v���j���[
	enemy_mng = std::make_shared<Enemy_Mng>(Enemy_Handle,Enemy_Bullet_Handle,Stage_HitEffect_Handle, Player_HitEffect_Handle);		//�G�l�~�[�Ǘ�

}

//�X�V
void Game_Scene::Update()
{

	stage->setStage(enemy_mng,player);	//�X�e�[�W��ǂݍ���
	enemy_mng->setEnemy(stage);			//�G�l�~�[���o��



	enemy_mng->Update();	//�G�l�~�[�X�V
	stage->Update();		//�X�e�[�W�X�V
	player->Update();		//�v���C���[�X�V






	//�@#####�@�����蔻�� #####
	
	//�G�l�~�[�ƃX�e�[�W
	stage->ColEnemy(enemy_mng);			//�@46	
	stage->ColEnemy_Bullet(enemy_mng);	//46

	//�v���C���[�ƃX�e�[�W
	stage->ColPlayer_Bullet(player);	// 26
	stage->ColPlayer(player);			// 16


	//�v���C���[�ƃG�l�~�[
	player->ColEnemy_Bullet(enemy_mng);		//



	enemy_mng->ColPlayer_Bullet(player);	//

	//�@##### #####	


	stage->Scroll(player, enemy_mng);	//��ʃX�N���[��	//14


}

//�`��
void Game_Scene::Draw()
{
	stage->Draw();		//�X�e�[�W�`��
	player->Draw();		//�v���C���[�`��
	enemy_mng->Draw();	//�G�l�~�[�`��
}

//�f�X�g���N�^
Game_Scene::~Game_Scene()
{

}
