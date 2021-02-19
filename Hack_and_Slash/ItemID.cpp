#include "ItemID.hpp"

//アイテムデータを取得
ItemData GetItemData(unsigned char ID)
{
	ItemData item;

	switch (ID)
	{
		//攻撃
	case 0x0001:
	{
		item = ItemData{5, 0,0,0, 0,0  };	//パラメータを設定

		return item;

	}break;


	};
}


