#include "Entry.hpp"

//コンストラクタ
Entry::Entry()
{
	//printf("SCRREN_WIDTH : %d\n", SCREEN_WIDTH);
	//printf("SCRREN_HEIGHT : %d\n",SCREEN_HEIGHT);

	InputKey = std::make_shared<Input>();
	game = std::make_shared<Game_Scene>(Scene_Type::Game,this);
	type = Scene_Type::Game;
}


int Entry::GetRand(int start,int end) {
	std::random_device rnd;								// 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());								//  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> Rand(start,end);    // [start,end] 範囲の一様乱数

	return Rand(mt);
}

//スプライトをロード
int Entry::LoadSprite(const char* FileName)
{
	int a = LoadGraph(FileName);

	if (a == -1)
	{
		printf("ファイルが存在しません。%s \n",FileName);
		return -1;
	}
	else {
		return a;
	}
}





//計算
void Entry::Update()
{

	InputKey->Update();
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

