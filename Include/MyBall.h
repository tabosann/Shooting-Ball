#ifndef ___CLASS_MY_BALL
#define ___CLASS_MY_BALL

//#include<Vector3.h>
//#include<BasicObject.h>
#include<MyPhysics.h>
#include<Application.h>

class MyBall: protected MyPhysics {
	double _r; //ボールの半径
	float _color[3][3] = {
		{0.5, 0.5, 0.5},
		{0.5, 0.5, 0.5},
		{0.2, 0.2, 0.2},
	}; //素材の色
	Vector3 _key = Vector3(1, 1, 1);

public:
	//@param m 物体の質量
	//@param e 反発係数
	//@param pos0 初期座標
	//@param v0 初速度
	//@param a 加速度
	//@param r 球体の半径
	//@param color[3][3] 素材の色
	MyBall(
		double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		double r, float color[3][3]
	);
	//@param m 物体の質量
	//@param e 反発係数
	//@param pos0 初期座標
	//@param v0 初速度
	//@param a 加速度
	//@param r 球体の半径
	MyBall(
		double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		double r
	);
	MyBall();

	friend void Application::calCollision(MyBall* ball, MySquare* square);
	friend void Application::calCollision(MyBall* ball, MyPointArea* pointArea);
	friend void Application::shoot(int x, int y);
	
	//物体運動を計算
	void update(double deltaTime);
	//物体（球体）の描画
	void draw() const;
};

#endif
