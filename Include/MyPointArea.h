#ifndef ___CLASS_MY_NO_COL_OBJECT
#define ___CLASS_MY_NO_COL_OBJECT

#include<BasicObject.h>
#include<Application.h>

class MyPointArea : protected BasicObject {
	Vector3 _pos;
	int _point; //獲得できるポイント
	float _color[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

public:
	//@param size 物体のサイズ
	//@param m 物体の質量
	//@param e 反発係数
	//@param pos 物体の位置
	//@param color[3][3] 素材の色
	MyPointArea(
		Vector3 size, double m, double e,
		Vector3 pos, int point, float color[3][3]
	);
	//@param size 物体のサイズ
	//@param m 物体の質量
	//@param e 反発係数
	//@param pos 物体の位置
	MyPointArea(
		Vector3 size, double m, double e,
		Vector3 pos, int point
	);
	MyPointArea();

	friend void Application::calCollision(MyBall* ball, MyPointArea* pointArea);

	//物体の位置更新
	void update(double deltaTime);
	//物体の描画
	void draw() const;
};

#endif