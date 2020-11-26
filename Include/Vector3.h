#ifndef ___CLASS_VECTOR3
#define ___CLASS_VECTOR3

#include<sstream> //operator<<()�̒�`

class Vector3 {
public:
	double _x, _y, _z;

	static const Vector3 ZERO;
	static const Vector3 IDENTITY;

	Vector3(double x, double y, double z);
	Vector3();
	Vector3(const Vector3& v);

	//������Z�q
	Vector3& operator = (const Vector3& v);

	//���Z
	friend Vector3 operator + (const Vector3& v1, const Vector3& v2);
	Vector3& operator += (const Vector3& v);

	//���Z
	friend Vector3 operator - (const Vector3& v1, const Vector3& v2);
	Vector3& operator -= (const Vector3& v);

	//��Z
	friend Vector3 operator * (double val, const Vector3& vec);
	Vector3 operator * (double val) const;
	Vector3& operator *= (double val);

	//���Z
	Vector3 operator / (double val) const;
	Vector3& operator /= (double val);

	//��Βl
	double magnitude() const;
	//���K��
	Vector3 normalize() const;
	//����
	static double dot(const Vector3& v1, const Vector3& v2);
	//�O��(�E��n)
	static Vector3 cross(const Vector3& src, const Vector3 dst);
};

inline std::ostream& operator << (std::ostream& os, const Vector3& v) {
	return os << '('
		<< v._x << ", "
		<< v._y << ", "
		<< v._z << ')';
}

#endif
