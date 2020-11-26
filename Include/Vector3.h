#ifndef ___CLASS_VECTOR3
#define ___CLASS_VECTOR3

#include<sstream> //operator<<()‚Ì’è‹`

class Vector3 {
public:
	double _x, _y, _z;

	static const Vector3 ZERO;
	static const Vector3 IDENTITY;

	Vector3(double x, double y, double z);
	Vector3();
	Vector3(const Vector3& v);

	//‘ã“ü‰‰ŽZŽq
	Vector3& operator = (const Vector3& v);

	//‰ÁŽZ
	friend Vector3 operator + (const Vector3& v1, const Vector3& v2);
	Vector3& operator += (const Vector3& v);

	//Œ¸ŽZ
	friend Vector3 operator - (const Vector3& v1, const Vector3& v2);
	Vector3& operator -= (const Vector3& v);

	//æŽZ
	friend Vector3 operator * (double val, const Vector3& vec);
	Vector3 operator * (double val) const;
	Vector3& operator *= (double val);

	//œŽZ
	Vector3 operator / (double val) const;
	Vector3& operator /= (double val);

	//â‘Î’l
	double magnitude() const;
	//³‹K‰»
	Vector3 normalize() const;
	//“àÏ
	static double dot(const Vector3& v1, const Vector3& v2);
	//ŠOÏ(‰EŽèŒn)
	static Vector3 cross(const Vector3& src, const Vector3 dst);
};

inline std::ostream& operator << (std::ostream& os, const Vector3& v) {
	return os << '('
		<< v._x << ", "
		<< v._y << ", "
		<< v._z << ')';
}

#endif
