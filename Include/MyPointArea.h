#ifndef ___CLASS_MY_NO_COL_OBJECT
#define ___CLASS_MY_NO_COL_OBJECT

#include<BasicObject.h>
#include<Application.h>

class MyPointArea : protected BasicObject {
	Vector3 _pos;
	int _point; //�l���ł���|�C���g
	float _color[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

public:
	//@param size ���̂̃T�C�Y
	//@param m ���̂̎���
	//@param e �����W��
	//@param pos ���̂̈ʒu
	//@param color[3][3] �f�ނ̐F
	MyPointArea(
		Vector3 size, double m, double e,
		Vector3 pos, int point, float color[3][3]
	);
	//@param size ���̂̃T�C�Y
	//@param m ���̂̎���
	//@param e �����W��
	//@param pos ���̂̈ʒu
	MyPointArea(
		Vector3 size, double m, double e,
		Vector3 pos, int point
	);
	MyPointArea();

	friend void Application::calCollision(MyBall* ball, MyPointArea* pointArea);

	//���̂̈ʒu�X�V
	void update(double deltaTime);
	//���̂̕`��
	void draw() const;
};

#endif