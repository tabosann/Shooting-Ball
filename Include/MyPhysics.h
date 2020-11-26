#ifndef ___CLASS_MY_PHYSICS
#define ___CLASS_MY_PHYSICS

//#include<Vector3.h>
#include<BasicObject.h>

/*
	�������Z���s���N���X
	������A�E�����A��O�����𐳂Ƃ���
*/
class MyPhysics: virtual protected BasicObject {
protected:
	Vector3 _pos;	//�ʒu
	Vector3 _pos0;	//�����ʒu
	Vector3 _v;		//���x
	Vector3 _v0;	//�����x
	Vector3 _a;		//�����x
	Vector3 _t = Vector3(0, 0, 0);	//����

public:
	static const double _g; //�d�͉����x
	static const Vector3 GRAVITY; //�d�݂͂̂�����

	//�����̃N���X�����o�̏������݂̂�S��
	//@param pos0 �������W
	//@param v0 �����x
	//@param a �����x
	MyPhysics(Vector3 pos0, Vector3 v0, Vector3 a);
	MyPhysics();

	//�ʒu�Ƒ��x�̌v�Z���s��
	void update(double deltaTime);
};

#endif
