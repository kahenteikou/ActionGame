#include "Collision.hpp"
#include "Entry.hpp"


/*####################################################
* 当たり判定の基底クラス
######################################################*/

//コンストラクタ
Collision::Collision()
{
	col_TagType = Tag::Invalid;	//取得　タグ
	my_TagType = Tag::Invalid;	//自身　タグ

	IsTrigger = false;		//トリガータイプ
	isCol = false;			//交差したかどうか？
	Vector = nullptr;		//方向
}

// #################################### 取得　関係

//トリガータイプを取得
bool Collision::getTriggerType()
{
	return IsTrigger;
}

//取得したタイプを取得
Tag Collision::getTag()
{
	return col_TagType;
}

//方向を取得
glm::vec2 Collision::getVector()
{
	return *Vector;
}

//タイプを取得
Tag Collision::getMyTag()
{
	return my_TagType;
}

//当たったかどうか？
bool Collision::getCol()
{
	return isCol;
}


//速度を取得
glm::vec2 Collision::getSpeed()
{
	return *Speed;
}

// #################################### 設定　関係

//トリガータイプを設定
void Collision::setTriggerType(bool tri)
{
	IsTrigger = tri;
}

//タグタイプを設定
void Collision::setTag(Tag type)
{	
	my_TagType = type;
}

//オブジェクトタイプを設定
void Collision::setVector(glm::vec2 *vec)
{
	Vector = vec;
}

//当たり判定のタグを設定
void Collision::setColTag(Tag type)
{
	col_TagType = type;
}

//当たり判定のタグを設定
void Collision::setCol(bool b)
{
	isCol = b;
}



//速度を設定
void Collision::setSpeed(glm::vec2 *spp)
{
	Speed = spp;
}


//デストラクタ
Collision::~Collision()
{

}


/*##############################################################################################################################################*/

/*####################################################
* 矩形の当たり判定
######################################################*/

//コンストラクタ
BoxCollision::BoxCollision()
{
	box.mMax = nullptr;	//AABB初期化
	box.mMin = nullptr;	//AABB初期化
}


//交差判定
//void BoxCollision::Intersect(std::shared_ptr<BoxCollision> col)
void BoxCollision::Intersect(BoxCollision *col)
//void BoxCollision::Intersect(BoxCollision& col)
{
	//printf("えええ\n");
	//printf("%f , %f \n",box.mMin->x,box.mMin->y);
	//printf("%f , %f \n",box.mMax->x,box.mMax->y);
	// 

	//printf("%f , %f \n", col->getMin().x, col->getMin().y);
	//printf("%f , %f \n", col->getMax().x, col->getMax().y);

//	printf("col->getMin()");
	printf("\n\n");


	if ((col->getMax().x > box.mMin->x && box.mMax->x > col->getMin().x)
		&& (col->getMax().y > box.mMin->y && box.mMax->y > col->getMin().y))
	{
		printf("true \n");
		setCol(true);				//当たり判定を設定
		setColTag(col->getMyTag());	//タグを取得
		col->setColTag(getMyTag());	//タグを設定

	
		if(getTriggerType() == false)
		{

			//サイズを取得
			 
			//相手
			glm::vec2 colSize = col->getMax() - col->getMin();
			colSize.x = colSize.x / 2;
			colSize.y = colSize.y / 2;

			//自分
			glm::vec2 boxSize = *box.mMax - *box.mMin;
			boxSize.x = boxSize.x / 2;
			boxSize.y = boxSize.y / 2;

			float colCenterX = (col->getMin().x + colSize.x);
			float colCenterY = (col->getMin().y + colSize.y);
			float boxCenterX = (box.mMin->x + boxSize.x);
			float boxCenterY = (box.mMin->y + boxSize.y);


			float deltaX = boxCenterX - colCenterX; //正ならboxが右にいる
			float deltaY = boxCenterY - colCenterY; //正ならboxが上にいる
			float adjust = 0.0;

			if (fabs(deltaX) < fabs(deltaY))
			{
			//	printf(", Y adjust \n");
				if (deltaY > 0)
				{
					adjust = col->getMax().y - box.mMin->y + 0.001f; // +する
				}
				else
				{
					adjust = -(box.mMax->y - col->getMin().y + 0.001f); // -する
				}
				box.mMin->y += adjust;
				box.mMax->y += adjust;
			}
			else
			{
			//	printf(", X adjust \n");
				if (deltaX > 0)
				{
					adjust = col->getMax().x - box.mMin->x + 0.001f; // +する

				}
				else
				{
					adjust = -(box.mMax->x - col->getMin().x + 0.001f); // -する
				}
				box.mMin->x += adjust;
				box.mMax->x += adjust;
			}
		}
		else {
			//Trigger true
		}
	}
	else
	{
		
		//当たってない時
		setCol(false);
		setColTag(Tag::Invalid);
		col->setColTag(Tag::Invalid);

	}




}


// #################################### 取得　関係

//最大値を取得
glm::vec2 BoxCollision::getMax()
{
	
	printf("getMax address %x\n", box.mMax);

	return *box.mMax;
}

//最小値を取得
glm::vec2 BoxCollision::getMin()
{
	printf("getMin address %x\n", box.mMin);

	return *box.mMin;
}




// #################################### 設定　関係

//最大値を設定
void BoxCollision::setMax(glm::vec2 *max)
{
	box.mMax = max;
	printf("setMax address %x\n", box.mMax);

}

//最小値を設定
void BoxCollision::setMin(glm::vec2 *min)
{
	box.mMin = min;
	printf("setMin address %x\n",box.mMin);
}

//最大値の値を設定
void BoxCollision::setMaxValue(glm::vec2& max)
{
	*box.mMax = max;
}

//最小値の値を設定
void BoxCollision::setMinValue(glm::vec2& min)
{
	*box.mMin = min;

}



//デストラクタ
BoxCollision::~BoxCollision()
{

}

/*##############################################################################################################################################*/
