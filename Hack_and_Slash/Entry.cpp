#include "Entry.hpp"

//コンストラクタ
Entry::Entry()
{
	//printf("SCRREN_WIDTH : %d\n", SCREEN_WIDTH);
	//printf("SCRREN_HEIGHT : %d\n",SCREEN_HEIGHT);


	game = std::make_shared<Game_Scene>(Scene_Type::Game);
	type = Scene_Type::Game;
}

//計算
void Entry::Update()
{
	switch (type)
	{
		//メインゲーム
	case Scene_Type::Game:
		{
			game->Update();
			type = game->getSceneType();
		}



	};
}

//描画
void Entry::Draw()
{
	switch (type)
	{
		//メインゲーム
	case Scene_Type::Game:
		{
			game->Draw();
			type = game->getSceneType();
		}




	};
}

//デストラクタ
Entry::~Entry()
{
	
}

