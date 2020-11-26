#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする
#include<MyPhysics.h>

const double MyPhysics::_g = -9.8;
const Vector3 MyPhysics::GRAVITY(0, MyPhysics::_g, 0);

MyPhysics::MyPhysics(Vector3 pos0, Vector3 v0, Vector3 a)
	:_pos0(pos0), _v0(v0), _a(a)
{}

MyPhysics::MyPhysics()
	: MyPhysics(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, MyPhysics::_g, 0))
{}

void
MyPhysics::update(double deltaTime) {
	_t += Vector3(deltaTime, deltaTime, deltaTime) * 0.002;

	//速度計算
	_v = Vector3(
		_v0._x + _a._x * _t._x,
		_v0._y + _a._y * _t._y,
		_v0._z + _a._z * _t._z
	);
	//位置計算
	_pos = Vector3(
		_pos0._x + _v0._x * _t._x + 0.5 * _a._x * _t._x * _t._x,
		_pos0._y + _v0._y * _t._y + 0.5 * _a._y * _t._y * _t._y,
		_pos0._z + _v0._z * _t._z + 0.5 * _a._z * _t._z * _t._z
	);
}
