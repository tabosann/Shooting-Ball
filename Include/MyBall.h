#ifndef ___CLASS_MY_BALL
#define ___CLASS_MY_BALL

//#include<Vector3.h>
//#include<BasicObject.h>
#include<MyPhysics.h>
#include<Application.h>

class MyBall: protected MyPhysics {
	double _r; //�{�[���̔��a
	float _color[3][3] = {
		{0.5, 0.5, 0.5},
		{0.5, 0.5, 0.5},
		{0.2, 0.2, 0.2},
	}; //�f�ނ̐F
	Vector3 _key = Vector3(1, 1, 1);

public:
	//@param m ���̂̎���
	//@param e �����W��
	//@param pos0 �������W
	//@param v0 �����x
	//@param a �����x
	//@param r ���̂̔��a
	//@param color[3][3] �f�ނ̐F
	MyBall(
		double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		double r, float color[3][3]
	);
	//@param m ���̂̎���
	//@param e �����W��
	//@param pos0 �������W
	//@param v0 �����x
	//@param a �����x
	//@param r ���̂̔��a
	MyBall(
		double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		double r
	);
	MyBall();

	friend void Application::calCollision(MyBall* ball, MySquare* square);
	friend void Application::calCollision(MyBall* ball, MyPointArea* pointArea);
	friend void Application::shoot(int x, int y);
	
	//���̉^�����v�Z
	void update(double deltaTime);
	//���́i���́j�̕`��
	void draw() const;
};

#endif
