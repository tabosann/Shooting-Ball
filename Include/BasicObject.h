#ifndef ___CLASS_BASIC_OBJECT
#define ___CLASS_BASIC_OBJECT

#include<Vector3.h>

/*
	���̂����ʂ��Ď��v�f���`����N���X
*/
class BasicObject {
protected:
	Vector3 _size;		//�T�C�Y
	double _m;			//����
	double _e;			//�����W��

public:
	BasicObject(const Vector3& size, double m, double e);
	BasicObject();
	virtual ~BasicObject() {};

	//�t���[�����̏���
	virtual void update(double deltaTime) = 0;
	//���̂̕`��
	virtual void draw() const = 0;
};

#endif
