#ifndef ___CLASS_MY_PHYSICS
#define ___CLASS_MY_PHYSICS

//#include<Vector3.h>
#include<BasicObject.h>

/*
	物理演算を行うクラス
	上向き、右向き、手前向きを正とする
*/
class MyPhysics: virtual protected BasicObject {
protected:
	Vector3 _pos;	//位置
	Vector3 _pos0;	//初期位置
	Vector3 _v;		//速度
	Vector3 _v0;	//初速度
	Vector3 _a;		//加速度
	Vector3 _t = Vector3(0, 0, 0);	//時刻

public:
	static const double _g; //重力加速度
	static const Vector3 GRAVITY; //重力のみが働く

	//自分のクラスメンバの初期化のみを担う
	//@param pos0 初期座標
	//@param v0 初速度
	//@param a 加速度
	MyPhysics(Vector3 pos0, Vector3 v0, Vector3 a);
	MyPhysics();

	//位置と速度の計算を行う
	void update(double deltaTime);
};

#endif
