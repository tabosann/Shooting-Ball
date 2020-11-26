#ifndef ___CLASS_MY_SQUARE
#define ___CLASS_MY_SQUARE

//#include<Vector3.h>
//#include<BasicObject.h>
#include<MyPhysics.h>
#include<Application.h>

class MySquare: protected MyPhysics {
	float _color[3][3] = {
		{0, 0, 0.5},
		{0, 0, 0.5},
		{0, 0, 0.2}
	}; //�f�ނ̐F

public:
	static enum Movement {
		MOVEMENT_X,
		MOVEMENT_Y,
		MOVEMENT_Z,
		MOVEMENT_INVALID
	};
	Movement _movement;

	//@param size ���̂̊e�����̑傫��
	//@param m ���̂̎���
	//@param e �����W��
	//@param pos0 �������W
	//@param v0 �����x
	//@param a �����x
	//@param color[3][3] �f�ނ̐F]
	//@param movement ���̂���������
	MySquare(
		Vector3 size, double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		float color[3][3], Movement movement = MOVEMENT_INVALID
	);
	//@param size ���̂̊e�����̑傫��
	//@param m ���̂̎���
	//@param e �����W��
	//@param pos0 �������W
	//@param v0 �����x
	//@param a �����x
	//@param movement ���̂���������
	MySquare(
		Vector3 size, double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		Movement movement = MOVEMENT_INVALID
	);
	MySquare();

	friend void Application::calCollision(MyBall* ball, MySquare* square);

	//���̉^�����v�Z
	void update(double deltaTime);
	//�����̂̕`��
	void draw() const;
};

using MOVEMENT = MySquare::Movement;

#endif