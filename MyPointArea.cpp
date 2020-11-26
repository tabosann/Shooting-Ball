#include <PreCompileHeader.h> //�����܂ł��v���R���p�C���σw�b�_�t�@�C���ɂ���

#include<MyPointArea.h>

MyPointArea::MyPointArea(
	Vector3 size, double m, double e, 
	Vector3 pos, int point, float color[3][3]
)
	:BasicObject(size, m, e), _pos(pos), _point(point)
{
	if (_color == color) return;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			_color[i][j] = color[i][j];
}

MyPointArea::MyPointArea(
	Vector3 size, double m, double e,
	Vector3 pos, int point
)
	:MyPointArea(size, m, e, pos, point, _color)
{}

MyPointArea::MyPointArea()
	:MyPointArea(Vector3::IDENTITY, 1.0, 0.5, Vector3::ZERO, 10)
{}

void 
MyPointArea::update(double deltaTime) {
	static double t = 0;
	t += deltaTime * 0.005;
	_pos._x = 1.75 * sin(t);
}

void 
MyPointArea::draw() const {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _color[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _color[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _color[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);

	glPushMatrix();
	glTranslatef(_pos._x, _pos._y, _pos._z);
	glScalef(_size._x / 2, _size._y / 2, _size._z / 2);
	//���
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(-1, +1, -1);
	glVertex3f(+1, +1, -1);
	glVertex3f(+1, +1, +1);
	glVertex3f(-1, +1, +1);
	glEnd();
	//����
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(+1, -1, -1);
	glVertex3f(+1, -1, +1);
	glVertex3f(-1, -1, +1);
	glEnd();
	//����
	glBegin(GL_QUAD_STRIP);
	//����
	glNormal3f(0, 0, 1);
	glVertex3f(-1, +1, +1);
	glVertex3f(-1, -1, +1);
	glVertex3f(+1, +1, +1);
	glVertex3f(+1, -1, +1);
	//�E����
	glNormal3f(1, 0, 0);
	glVertex3f(+1, +1, -1);
	glVertex3f(+1, -1, -1);
	//���
	glNormal3f(0, 0, -1);
	glVertex3f(-1, +1, -1);
	glVertex3f(-1, -1, -1);
	//������
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, +1, +1);
	glVertex3f(-1, -1, +1);
	glEnd();
	glPopMatrix();
}
