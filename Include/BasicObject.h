#ifndef ___CLASS_BASIC_OBJECT
#define ___CLASS_BASIC_OBJECT

#include<Vector3.h>

/*
	物体が共通して持つ要素を定義するクラス
*/
class BasicObject {
protected:
	Vector3 _size;		//サイズ
	double _m;			//質量
	double _e;			//反発係数

public:
	BasicObject(const Vector3& size, double m, double e);
	BasicObject();
	virtual ~BasicObject() {};

	//フレーム毎の処理
	virtual void update(double deltaTime) = 0;
	//物体の描画
	virtual void draw() const = 0;
};

#endif
