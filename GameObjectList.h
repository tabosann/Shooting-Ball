#ifndef ___GAME_OBJECT_LIST_H
#define ___GAME_OBJECT_LIST_H

#include<MyBall.h>
#include<MySquare.h>
#include<MyPointArea.h>

namespace { //素材の色
	float red[3][3] = {
		{0.5, 0, 0}, //ディフューズ
		{0.5, 0, 0}, //スペキュラ
		{0.2, 0, 0}  //アンビエント
	};

	float green[3][3] = {
		{0, 0.5, 0},
		{0, 0.5, 0},
		{0, 0.2, 0}	
	};
}

//ゲームオブジェクト一覧
MyBall balls[] = {
	MyBall(
		1.0, 0.75,
		Vector3(0, 0.5, 2.5), Vector3(0, 0, 0), Vector3(0, -9.8, 0),
		0.2
	)
};

MySquare squares[] = {
	MySquare( //右奥柱
		Vector3(0.5, 3.8, 0.5), 1.0, 0.75,
		Vector3(2.5 - 0.25, 2, -7 + 0.25), Vector3(0, 0, 0), Vector3(0, 0, 0)
	),
	MySquare( //左奥柱
		Vector3(0.5, 3.8, 0.5), 1.0, 0.75,
		Vector3(-2.5 + 0.25, 2, -7 + 0.25), Vector3(0, 0, 0), Vector3(0, 0, 0)
	),
	MySquare( //中柱(後)
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(-2, 0.7, -5), Vector3(2, 0, 0), Vector3(0, 0, 0),
		green, MOVEMENT::MOVEMENT_X
	),
	MySquare( //中柱(中)
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(-4, 0.7, -2), Vector3(4, 0, 0), Vector3(0, 0, 0),
		green, MOVEMENT::MOVEMENT_X
	),
	MySquare( //中柱(前)
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(2, 0.7, 1), Vector3(-2, 0, 0), Vector3(0, 0, 0),
		green, MOVEMENT::MOVEMENT_X
	),
	MySquare( //床
		Vector3(5, 0.2, 10), 1.0, 0.75,
		Vector3(0, 0, -2), Vector3(0, 0, 0), Vector3(0, 0, 0)
	)
};

MyPointArea pointAreas[] = {
	MyPointArea(
		Vector3(0.5, 1, 0.5), 1.0, 1.0,
		Vector3(0, 0.5, -7 + 0.25), 100, 
		red
	)
};

#endif
