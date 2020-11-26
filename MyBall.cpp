#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする
#include<MyBall.h>

#pragma comment(lib, "glut32.lib")

MyBall::MyBall(
	double m, double e, 
	Vector3 pos0, Vector3 v0, Vector3 a, 
	double r, float color[3][3]
)
	:BasicObject(Vector3(2 * r, 2 * r, 2 * r), m, e), MyPhysics(pos0, v0, a), _r(r)
{
	if (color == _color) return;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			_color[i][j] = color[i][j];
}

MyBall::MyBall(
	double m, double e,
	Vector3 pos0, Vector3 v0, Vector3 a,
	double r
)
	:MyBall(m, e, pos0, v0, a, r, _color)
{}

MyBall::MyBall()
	:MyBall(
		1.0, 0.75,
		Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, MyPhysics::_g, 0),
		0.5
	)
{}

inline void
MyBall::update(double deltaTime) {
	MyPhysics::update(deltaTime);
	_pos._y = _pos0._y + _v0._y * _t._y + 0.5 * _a._y * _t._y * _t._y * _key._y;
}

inline void 
MyBall::draw() const {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _color[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _color[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _color[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);

	glPushMatrix();
	glTranslatef(_pos._x, _pos._y, _pos._z);
	glutSolidSphere(_r, 30, 30);
	glPopMatrix();
}
