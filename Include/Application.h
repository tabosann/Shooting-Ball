#ifndef ___CLASS_APPLICATION
#define ___CLASS_APPLICATION

#include<vector>

class MyBall;
class MySquare;
class MyPointArea;
class Application {
	//シングルトン
	Application();
	Application(const Application&);
	Application& operator=(const Application&);

public:
	//シングルトン
	//実体は一つだけに限定する
	static Application& instance();

	//オブジェクト配列を受け取る
	std::vector<MyBall> _balls;
	std::vector<MySquare> _squares;
	std::vector<MyPointArea> _pointAreas;
	int _pointSum = 0; //獲得した合計ポイント

	//ボールと壁の衝突演算
	void calCollision(MyBall* ball, MySquare* square);
	//ボールとポイント獲得エリアの衝突演算
	//ここでポイントの計算を行う
	void calCollision(MyBall* ball, MyPointArea* pointArea);

	//異なるオブジェクト間の衝突演算
	void update(double deltaTime);

	//ボールをショットする
	void shoot(int x, int y);

	//ボールを生成する
	void resetBall();
};

#endif