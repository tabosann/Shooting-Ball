#include<PreCompileHeader.h> //ここまでをプリコンパイル済ヘッダファイルとする
#include<Application.h>
#include<MyBall.h>
#include<MySquare.h>
#include<MyPointArea.h>
#include<thread> //並列処理
#include<mutex> //危険領域管理

using namespace std;

namespace {
	bool calPointAlready = false;
	bool callShootFuncAlready = false;
}

Application::Application() {
	
}

Application&
Application::instance() {
	static Application app;
	return app;
}

void
Application::calCollision(MyBall* ball, MySquare* square) {
	Vector3 div = ball->_pos - square->_pos;
	div = Vector3(fabs(div._x), fabs(div._y), fabs(div._z)); //ボールと直方体との距離

	Vector3 hitPos; //接触点
	thread tx, ty, tz; //並列処理

	/*
		(1)
		領域による簡単な接触判定を図る（第一の判定）
		a)物体と接触しているかどうかを、ボールを基準にして領域で判定
		b)接触判定があれば、どの点で接触したかを各成分で計算する
		  --接触点が物体の描画範囲内からはみ出ないように整えることで実現
	*/
	if (
		div._x <= square->_size._x / 2 + ball->_size._x / 2 &&
		div._y <= square->_size._y / 2 + ball->_size._y / 2 &&
		div._z <= square->_size._z / 2 + ball->_size._z / 2
		) {

		tx = thread(
			[&hitPos, &ball, &square]() {
				hitPos._x = ball->_pos._x; //ボールを基準に
				//ボールが正の方向に描画範囲外であれば、最も近い端に合わせる
				if (hitPos._x >= square->_pos._x + square->_size._x / 2)
					hitPos._x = square->_pos._x + square->_size._x / 2;
				//ボールが負の方向に描画範囲外であれば、最も近い端に合わせる
				else if (hitPos._x <= square->_pos._x - square->_size._x / 2)
					hitPos._x = square->_pos._x - square->_size._x / 2;
			}
		);
		
		//以降、同様にして計算

		ty = thread(
			[&hitPos, &ball, &square]() {
				hitPos._y = ball->_pos._y;
				if (hitPos._y >= square->_pos._y + square->_size._y / 2)
					hitPos._y = square->_pos._y + square->_size._y / 2;
				else if (hitPos._y <= square->_pos._y - square->_size._y / 2)
					hitPos._y = square->_pos._y - square->_size._y / 2;
			}
		);

		tz = thread(
			[&hitPos, &ball, &square]() {
				hitPos._z = ball->_pos._z;
				if (hitPos._z >= square->_pos._z + square->_size._z / 2)
					hitPos._z = square->_pos._z + square->_size._z / 2;
				else if (hitPos._z <= square->_pos._z - square->_size._z / 2)
					hitPos._z = square->_pos._z - square->_size._z / 2;
			}
		);

		tx.join();
		ty.join();
		tz.join();
	}
	else {
		return; //接触判定なし
	}

	/*
		(2)
		接触点を求めたら、それを使ってバウンド方向ベクトルを
		求め、接触判定を厳格化する(第二の判定)
	*/

	div = ball->_pos - hitPos; //接触点からボールの中心への方向ベクトル

	//ボールの中心と接触点との距離が、ボールの半径と一致しなければ
	//接触していないことになるので、落下運動を許可する
	if (div.magnitude() > ball->_r) {
		ball->_key._y = 1; //加速度計算を行う
		return;
	}

	/*
		(3)
		2つの判定を乗り越えたら、バウンド方向ベクトルを正規化し、各成分の反発比率を求める
		そして、その結果と反発係数を考慮しながら、バウンド後の速度を求める
	*/

	div = div.normalize();
	Vector3 speed = ball->_v - square->_v; //壁とボールの相対速度(壁から見たボールの速度)

	//以下、各成分の反発方向と速度の積が負であれば反発処理を施す
	tx = thread(
		[&div, &speed, &ball, &square]() {
			if (div._x * speed._x < 0) {
				ball->_t._x = 0;
				ball->_a._x = -1 * ball->_a._x;
				ball->_v0._x = -1 * speed._x * ball->_e * fabs(div._x);
				//バウンド後のボール速度が壁と同じ方向かつ、ボールの速さが壁の速さよりも小さければ
				//壁に押される形でボールを移動させる
				if (-fabs(square->_v0._x) <= -fabs(ball->_v0._x) || 
					fabs(ball->_v0._x) <= fabs(square->_v0._x)
					) {
					ball->_v0._x = square->_v0._x;
				}
				ball->_pos0._x = ball->_pos._x;
			}
		}
	);

	ty = thread(
		[&div, &speed, &ball, &square]() {
			if (div._y * speed._y < 0) {
				ball->_t._y = 0;
				ball->_v0._y = -1 * speed._y * ball->_e * fabs(div._y);
				if (fabs(ball->_v0._y) < 0.1) ball->_v0._y = 0;

				if (-fabs(square->_v0._y) <= -fabs(ball->_v0._y) || 
					fabs(ball->_v0._y) <= fabs(square->_v0._y)
					) {
					ball->_key._y = 0; //加速度計算を省く
					ball->_v0._y = square->_v0._y;
				}
				ball->_pos0._y = ball->_pos._y;
			}
		}
	);

	tz = thread(
		[&div, &speed, &ball, &square]() {
			if (div._z * speed._z < 0) {
				ball->_t._z = 0;
				ball->_a._z = -1 * ball->_a._z;
				ball->_v0._z = -1 * speed._z * ball->_e * fabs(div._z);
				if (-fabs(square->_v0._z) <= -fabs(ball->_v0._z) || 
					fabs(ball->_v0._z) <= fabs(square->_v0._z)
					) {
					ball->_v0._z = square->_v0._z;
				}
				ball->_pos0._z = ball->_pos._z;
			}
		}
	);

	tx.join();
	ty.join();
	tz.join();
}

void 
Application::calCollision(MyBall* ball, MyPointArea* pointArea) {
	//ポイント計算はワンショットにつき一度まで
	if (calPointAlready) return;

	Vector3 div = ball->_pos - pointArea->_pos;
	div = Vector3(fabs(div._x), fabs(div._y), fabs(div._z));
	if (
		div._x < pointArea->_size._x / 2 &&
		div._y < pointArea->_size._y / 2 &&
		div._z < pointArea->_size._z / 2
		) {
		calPointAlready = true;
		_pointSum += pointArea->_point;
	}
}

void
Application::update(double deltaTime) {
	vector<thread> threads; //並列処理配列

	for (auto& ball: _balls) {
		threads.emplace_back(
			[&ball, deltaTime]() {
				ball.update(deltaTime);
			}
		);
	}

	for (auto& square : _squares) {
		threads.emplace_back(
			[&square, deltaTime]() {
				square.update(deltaTime);
			}
		);
	}

	for (auto& pointArea : _pointAreas) {
		threads.emplace_back(
			[&pointArea, deltaTime]() {
				pointArea.update(deltaTime);
			}
		);
	}

	for (auto& ball : _balls) {
		for (auto& square : _squares) {
			threads.emplace_back(
				[&square, &ball, this]() {
					calCollision(&ball, &square);
				}
			);
		}
	}

	for (auto& ball : _balls) {
		for (auto& pointArea : _pointAreas) {
			threads.emplace_back(
				[&pointArea, &ball, this]() {
					calCollision(&ball, &pointArea);
				}
			);
		}
	}

	for (auto& t : threads) t.join(); //同期
}

void 
Application::shoot(int x, int y) {
	//ボールをシュートするにはボールの生成を行ってから
	if (callShootFuncAlready) return;
	callShootFuncAlready = true;

	Vector3 speed(x, 0, y);
	speed /= 100;
	_balls[0]._t = Vector3::ZERO;
	_balls[0]._v0 = speed;
}

void
Application::resetBall() {
	MyBall balls[] = {
		MyBall(
			1.0, 0.75,
			Vector3(0, 0.5, 2.5), Vector3(0, 0, 0), MyPhysics::GRAVITY,
			0.2
		)
	};

	calPointAlready = false;
	callShootFuncAlready = false;
	_balls.assign(balls, balls + _countof(balls));
}
