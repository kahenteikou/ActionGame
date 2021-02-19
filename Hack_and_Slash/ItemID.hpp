#ifndef ITEM_ID_HPP
#define ITEM_ID_HPP


//アイテムID
enum class Item_ID
{
	Attack_UP,		//攻撃力　上昇
	Defense_UP,		//防御力　上昇
	HitPoint_Rec,	//HP　回復


	None,	//項目やその他の場合
};


// ゲームアイテム
typedef struct ItemData
{

	int mSpeed_Max;		//最大速度

	int HP_Max;			//最大HP
	int HP_Rec;			//HP
	int HP_autoRec;		//自動回復

	int Attack;			//攻撃力
	int Coin;			//通貨
}ItemData;


//アイテムデータを取得
ItemData GetItemData(unsigned char ID);









#endif
