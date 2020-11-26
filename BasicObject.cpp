#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする
#include<BasicObject.h>

BasicObject::BasicObject(const Vector3& size, double m, double e)
	:_size(size), _m(m), _e(e)
{}

BasicObject::BasicObject()
	: BasicObject(Vector3(1, 1, 1), 1.0, 0.75)
{}
