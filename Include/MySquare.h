#ifndef ___CLASS_MY_SQUARE
#define ___CLASS_MY_SQUARE

//#include<Vector3.h>
//#include<BasicObject.h>
#include<MyPhysics.h>
#include<Application.h>

class MySquare: protected MyPhysics {
	float _color[3][3] = {
		{0, 0, 0.5},
		{0, 0, 0.5},
		{0, 0, 0.2}
	}; //素材の色

public:
	static enum Movement {
		MOVEMENT_X,
		MOVEMENT_Y,
		MOVEMENT_Z,
		MOVEMENT_INVALID
	};
	Movement _movement;

	//@param size 物体の各成分の大きさ
	//@param m 物体の質量
	//@param e 反発係数
	//@param pos0 初期座標
	//@param v0 初速度
	//@param a 加速度
	//@param color[3][3] 素材の色]
	//@param movement 物体が往復する
	MySquare(
		Vector3 size, double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		float color[3][3], Movement movement = MOVEMENT_INVALID
	);
	//@param size 物体の各成分の大きさ
	//@param m 物体の質量
	//@param e 反発係数
	//@param pos0 初期座標
	//@param v0 初速度
	//@param a 加速度
	//@param movement 物体が往復する
	MySquare(
		Vector3 size, double m, double e,
		Vector3 pos0, Vector3 v0, Vector3 a,
		Movement movement = MOVEMENT_INVALID
	);
	MySquare();

	friend void Application::calCollision(MyBall* ball, MySquare* square);

	//物体運動を計算
	void update(double deltaTime);
	//直方体の描画
	void draw() const;
};

using MOVEMENT = MySquare::Movement;

#endif