#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする
#include<MySquare.h>

#pragma comment(lib, "glut32.lib")

#define PI 3.1415

MySquare::MySquare(
	Vector3 size, double m, double e,
	Vector3 pos0, Vector3 v0, Vector3 a, 
	float color[3][3], Movement movement
)
	:BasicObject(size, m, e), MyPhysics(pos0, v0, a), _movement(movement)
{
	if (color == _color) return;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			_color[i][j] = color[i][j];
}

MySquare::MySquare(
	Vector3 size, double m, double e,
	Vector3 pos0, Vector3 v0, Vector3 a,
	Movement movement
)
	:MySquare(size, m, e, pos0, v0, a, _color, movement)
{}

MySquare::MySquare()
	:MySquare(
		Vector3(1, 1, 1), 1.0, 0.75,
		Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, MyPhysics::_g, 0)
	)
{}

void
MySquare::update(double deltaTime) {
	MyPhysics::update(deltaTime);

	switch (_movement) {
	case MOVEMENT_X:
		if (_t._x > 2) {
			_t._x = 0;
			_v0._x *= -1;
			_pos0._x = _pos._x;
		}
		break;
	case MOVEMENT_Y:
		if (_t._y > 2) {
			_t._y = 0;
			_v0._y *= -1;
			_pos0._y = _pos._y;
		}
		break;
	case MOVEMENT_Z:
		if (_t._z > 2) {
			_t._z = 0;
			_v0._z *= -1;
			_pos0._z = _pos._z;
		}
		break;
	}
}

void
MySquare::draw() const {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _color[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _color[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _color[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);

	glPushMatrix();
	glTranslatef(_pos._x, _pos._y, _pos._z);
	glScalef(_size._x / 2, _size._y / 2, _size._z / 2);
	//上面
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(-1, +1, -1);
	glVertex3f(+1, +1, -1);
	glVertex3f(+1, +1, +1);
	glVertex3f(-1, +1, +1);
	glEnd();
	//下面
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(+1, -1, -1);
	glVertex3f(+1, -1, +1);
	glVertex3f(-1, -1, +1);
	glEnd();
	//側面
	glBegin(GL_QUAD_STRIP);
	//正面
	glNormal3f(0, 0, 1);
	glVertex3f(-1, +1, +1);
	glVertex3f(-1, -1, +1);
	glVertex3f(+1, +1, +1);
	glVertex3f(+1, -1, +1);
	//右側面
	glNormal3f(1, 0, 0);
	glVertex3f(+1, +1, -1);
	glVertex3f(+1, -1, -1);
	//後面
	glNormal3f(0, 0, -1);
	glVertex3f(-1, +1, -1);
	glVertex3f(-1, -1, -1);
	//左側面
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, +1, +1);
	glVertex3f(-1, -1, +1);
	glEnd();
	glPopMatrix();
}
