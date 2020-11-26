#include<PreCompileHeader.h> //�����܂ł��v���R���p�C���σw�b�_�t�@�C���Ƃ���

#include<thread> //���񏈗��֘A
#include<Application.h> //�Q�[���I�u�W�F�N�g�̑�����s��
#include"GameObjectList.h" //�Q�[���I�u�W�F�N�g��ۊ�

#pragma comment(lib, "glut32.lib")

using namespace std;

namespace {
	const double DELTA1 = 5.0; //���ԊԊu(ms)
	const int WINDOW_WIDTH = 720;
	const int WINDOW_HEIGHT = 720;

	//�F�̗p��(R, G, B)
	float white[] = { 1, 1, 1 };
	float black[] = { 0, 0, 0 };

	//�����̈ʒu(x, y, z)�A�������[�h(0 or 1)
	float light[][4] = {
		{+0, +0.7, +5, 1},
	};

	//�}�E�X��ON,OFF(OFF = false)
	bool call = false;
	int startX = 0, startY = 0, endX = 0, endY = 0;

	//�A�v���P�[�V����������
	Application& app = Application::instance();
}

//�`��
void display();
//�L�[���͎�t
void KeyboardHandler(unsigned char _setti, int x, int y);
//�}�E�X�̃|�C���^���W�𓾂�
void mouseON(int x, int y);
void mouseOFF(int x, int y);
//�^�C�}�[
void IncTime(int timer);
//������`��
void drawStr(string str, int x, int y);
//�K���l��Ԃ�
float* Multiply(float* color, float val);

int main(int argc, char** argv) {
	//�Q�[���I�u�W�F�N�g�̋L��
	app._balls.assign(balls, balls + _countof(balls));
	app._squares.assign(squares, squares + _countof(squares));
	app._pointAreas.assign(pointAreas, pointAreas + _countof(pointAreas));

	//��������openGL�̏�����
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("MyPhysics");

	glClearColor(0.5, 0.5, 0.5, 1.0);

	glMatrixMode(GL_PROJECTION);  //�r���[�v���W�F�N�V����
	glLoadIdentity(); //�P�ʍs��
	gluPerspective(45, 1.0, 1.0, 30.0); //FOV�F������p�x�A�A�X�y�N�g��A�O�ʁA���
	gluLookAt(0, 5, 0, 0, 4, -3, 0, 1, 0); //�ڂ̈ʒu�A����Ƃ���A��x�N�g��

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); //�B�ʏ������[�h

	//�������烁�C������
	glutDisplayFunc(display);

	glutTimerFunc(DELTA1, IncTime, 1);
	glutKeyboardFunc(KeyboardHandler);
	glutPassiveMotionFunc(mouseOFF);
	glutMotionFunc(mouseON);
	glutMainLoop();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); //�`�悷��Ƃ��̃x�[�X�̐F

	ostringstream os;
	os << "Point:" << app._pointSum;
	drawStr(os.str(), 10, 30); //�|�C���g�̕`��

	drawStr("Space key: End The Game", 10, 50);
	drawStr("Other key: Reset Ball", 10, 70);
	drawStr("Mouse: Shoot The Ball", 10, 90);

	glMatrixMode(GL_MODELVIEW); //�A�t�B���ϊ��s�񃂁[�h
	glLoadIdentity(); //�P�ʍs��

	glTranslatef(0, 0, -10);

	//�����̐ݒ�
	glLightfv(GL_LIGHT0, GL_POSITION, light[0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Multiply(white, 1.0));
	glLightfv(GL_LIGHT0, GL_SPECULAR, Multiply(white, 1.0));
	glLightfv(GL_LIGHT0, GL_AMBIENT, Multiply(white, 1.0));

	glShadeModel(GL_SMOOTH);
	for (MyBall& ball : app._balls)
		ball.draw();

	glShadeModel(GL_FLAT);
	for (MySquare& square : app._squares)
		square.draw();

	for (MyPointArea& pointArea : app._pointAreas)
		pointArea.draw();

	glFlush();
}

void mouseOFF(int x, int y) {
	if (!call) return;
	call = false;
	startX = x - WINDOW_WIDTH / 2;
	startY = y - WINDOW_HEIGHT / 2;
	app.shoot(startX - endX, startY - endY);
}

void mouseON(int x, int y) {
	if (call) return;
	call = true;
	endX = x - WINDOW_WIDTH / 2;
	endY = y - WINDOW_HEIGHT / 2;
}

void KeyboardHandler(unsigned char _key, int x, int y) {
	switch (_key) {
	case ' ': 
		exit(0); 
		break;
	default:
		app.resetBall();
		break;
	}
}

void IncTime(int timer) {

	if (timer != 1) return;

	app.update(DELTA1);

	glutTimerFunc(DELTA1, IncTime, 1);
	glutPostRedisplay();
}

void drawStr(string str, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// ��ʏ�Ƀe�L�X�g�`��
	glRasterPos2f(x, y);
	int size = (int)str.size();
	for (int i = 0; i < size; ++i) {
		char ic = str[i];
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

float new_color[4];
float* Multiply(float* color, float val) {
	for (int i = 0; i < 3; ++i)
		new_color[i] = color[i] * val;
	return new_color;
}
