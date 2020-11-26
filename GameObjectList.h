#ifndef ___GAME_OBJECT_LIST_H
#define ___GAME_OBJECT_LIST_H

#include<MyBall.h>
#include<MySquare.h>
#include<MyPointArea.h>

namespace { //�f�ނ̐F
	float red[3][3] = {
		{0.5, 0, 0}, //�f�B�t���[�Y
		{0.5, 0, 0}, //�X�y�L����
		{0.2, 0, 0}  //�A���r�G���g
	};

	float green[3][3] = {
		{0, 0.5, 0},
		{0, 0.5, 0},
		{0, 0.2, 0}	
	};
}

//�Q�[���I�u�W�F�N�g�ꗗ
MyBall balls[] = {
	MyBall(
		1.0, 0.75,
		Vector3(0, 0.5, 2.5), Vector3(0, 0, 0), Vector3(0, -9.8, 0),
		0.2
	)
};

MySquare squares[] = {
	MySquare( //�E����
		Vector3(0.5, 3.8, 0.5), 1.0, 0.75,
		Vector3(2.5 - 0.25, 2, -7 + 0.25), Vector3(0, 0, 0), Vector3(0, 0, 0)
	),
	MySquare( //������
		Vector3(0.5, 3.8, 0.5), 1.0, 0.75,
		Vector3(-2.5 + 0.25, 2, -7 + 0.25), Vector3(0, 0, 0), Vector3(0, 0, 0)
	),
	MySquare( //����(��)
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(-2, 0.7, -5), Vector3(2, 0, 0), Vector3(0, 0, 0),
		green, MOVEMENT::MOVEMENT_X
	),
	MySquare( //����(��)
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(-4, 0.7, -2), Vector3(4, 0, 0), Vector3(0, 0, 0),
		green, MOVEMENT::MOVEMENT_X
	),
	MySquare( //����(�O)
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(2, 0.7, 1), Vector3(-2, 0, 0), Vector3(0, 0, 0),
		green, MOVEMENT::MOVEMENT_X
	),
	MySquare( //��
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
