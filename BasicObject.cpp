#include<PreCompileHeader.h> //�����܂ł��v���R���p�C���σw�b�_�t�@�C���Ƃ���
#include<BasicObject.h>

BasicObject::BasicObject(const Vector3& size, double m, double e)
	:_size(size), _m(m), _e(e)
{}

BasicObject::BasicObject()
	: BasicObject(Vector3(1, 1, 1), 1.0, 0.75)
{}
