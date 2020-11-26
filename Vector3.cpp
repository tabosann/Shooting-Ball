#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする
#include<Vector3.h>

const Vector3 Vector3::ZERO(0, 0, 0);
const Vector3 Vector3::IDENTITY(1, 1, 1);

Vector3::Vector3(double x, double y = 0, double z = 0)
	:_x(x), _y(y), _z(z)
{}

Vector3::Vector3()
	:Vector3(0, 0, 0)
{}

Vector3::Vector3(const Vector3& v)
	:Vector3(v._x, v._y, v._z)
{}

Vector3& Vector3::operator = (const Vector3& v) {
	_x = v._x;
	_y = v._y;
	_z = v._z;
	return *this;
}

Vector3 operator + (const Vector3& v1, const Vector3& v2) {
	return Vector3(v1._x + v2._x, v1._y + v2._y, v1._z + v2._z);
}

Vector3& Vector3::operator += (const Vector3& v) {
	_x += v._x;
	_y += v._y;
	_z += v._z;
	return *this;
}

Vector3 operator - (const Vector3& v1, const Vector3& v2) {
	return Vector3(v1._x - v2._x, v1._y - v2._y, v1._z - v2._z);
}

Vector3& Vector3::operator -= (const Vector3& v) {
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;
	return *this;
}

Vector3 operator * (double val, const Vector3& vec) {
	return Vector3(val * vec._x, val * vec._y, val * vec._z);
}

Vector3 Vector3::operator * (double val) const {
	return Vector3(_x * val, _y * val, _z * val);
}

Vector3& Vector3::operator *= (double val) {
	_x *= val;
	_y *= val;
	_z *= val;
	return *this;
}

Vector3 Vector3::operator / (double val) const {
	if (val == 0) {
		OutputDebugStringA("警告：0で割ることはできません.");
		assert(0);
	}
	return Vector3(_x / val, _y / val, _z / val);
}

Vector3& Vector3::operator /= (double val) {
	if (val == 0) {
		OutputDebugStringA("警告：0で割ることはできません.");
		assert(0);
	}
	_x /= val;
	_y /= val;
	_z /= val;
	return *this;
}

double Vector3::magnitude() const {
	return sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3 Vector3::normalize() const {
	return *this / magnitude();
}

double Vector3::dot(const Vector3& v1, const Vector3& v2) {
	return v1._x * v2._x + v1._y * v2._y + v1._z * v2._z;
}

Vector3 Vector3::cross(const Vector3& src, const Vector3 dst) {
	return Vector3(
		src._y * dst._z - dst._y * src._z,
		src._z * dst._x - dst._z * src._x,
		src._x * dst._y - dst._x * src._y
	);
}
