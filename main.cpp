#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする

#include<thread> //並列処理関連
#include<Application.h> //ゲームオブジェクトの操作を行う
#include"GameObjectList.h" //ゲームオブジェクトを保管

#pragma comment(lib, "glut32.lib")

using namespace std;

namespace {
	const double DELTA1 = 5.0; //時間間隔(ms)
	const int WINDOW_WIDTH = 720;
	const int WINDOW_HEIGHT = 720;

	//色の用意(R, G, B)
	float white[] = { 1, 1, 1 };
	float black[] = { 0, 0, 0 };

	//光源の位置(x, y, z)、光源モード(0 or 1)
	float light[][4] = {
		{+0, +0.7, +5, 1},
	};

	//マウスのON,OFF(OFF = false)
	bool call = false;
	int startX = 0, startY = 0, endX = 0, endY = 0;

	//アプリケーションを扱う
	Application& app = Application::instance();
}

//描画
void display();
//キー入力受付
void KeyboardHandler(unsigned char _setti, int x, int y);
//マウスのポインタ座標を得る
void mouseON(int x, int y);
void mouseOFF(int x, int y);
//タイマー
void IncTime(int timer);
//文字列描画
void drawStr(string str, int x, int y);
//階調値を返す
float* Multiply(float* color, float val);

int main(int argc, char** argv) {
	//ゲームオブジェクトの記憶
	app._balls.assign(balls, balls + _countof(balls));
	app._squares.assign(squares, squares + _countof(squares));
	app._pointAreas.assign(pointAreas, pointAreas + _countof(pointAreas));

	//ここからopenGLの初期化
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("MyPhysics");

	glClearColor(0.5, 0.5, 0.5, 1.0);

	glMatrixMode(GL_PROJECTION);  //ビュープロジェクション
	glLoadIdentity(); //単位行列
	gluPerspective(45, 1.0, 1.0, 30.0); //FOV：見える角度、アスペクト比、前面、後面
	gluLookAt(0, 5, 0, 0, 4, -3, 0, 1, 0); //目の位置、見るところ、上ベクトル

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); //隠面消去モード

	//ここからメイン処理
	glutDisplayFunc(display);

	glutTimerFunc(DELTA1, IncTime, 1);
	glutKeyboardFunc(KeyboardHandler);
	glutPassiveMotionFunc(mouseOFF);
	glutMotionFunc(mouseON);
	glutMainLoop();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); //描画するときのベースの色

	ostringstream os;
	os << "Point:" << app._pointSum;
	drawStr(os.str(), 10, 30); //ポイントの描画

	drawStr("Space key: End The Game", 10, 50);
	drawStr("Other key: Reset Ball", 10, 70);
	drawStr("Mouse: Shoot The Ball", 10, 90);

	glMatrixMode(GL_MODELVIEW); //アフィン変換行列モード
	glLoadIdentity(); //単位行列

	glTranslatef(0, 0, -10);

	//光源の設定
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

	// 画面上にテキスト描画
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
