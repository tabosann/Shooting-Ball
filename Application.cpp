#include<PreCompileHeader.h> //�����܂ł��v���R���p�C���σw�b�_�t�@�C���Ƃ���
#include<Application.h>
#include<MyBall.h>
#include<MySquare.h>
#include<MyPointArea.h>
#include<thread> //���񏈗�
#include<mutex> //�댯�̈�Ǘ�

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
	div = Vector3(fabs(div._x), fabs(div._y), fabs(div._z)); //�{�[���ƒ����̂Ƃ̋���

	Vector3 hitPos; //�ڐG�_
	thread tx, ty, tz; //���񏈗�

	/*
		(1)
		�̈�ɂ��ȒP�ȐڐG�����}��i���̔���j
		a)���̂ƐڐG���Ă��邩�ǂ������A�{�[������ɂ��ė̈�Ŕ���
		b)�ڐG���肪����΁A�ǂ̓_�ŐڐG���������e�����Ōv�Z����
		  --�ڐG�_�����̂̕`��͈͓�����͂ݏo�Ȃ��悤�ɐ����邱�ƂŎ���
	*/
	if (
		div._x <= square->_size._x / 2 + ball->_size._x / 2 &&
		div._y <= square->_size._y / 2 + ball->_size._y / 2 &&
		div._z <= square->_size._z / 2 + ball->_size._z / 2
		) {

		tx = thread(
			[&hitPos, &ball, &square]() {
				hitPos._x = ball->_pos._x; //�{�[�������
				//�{�[�������̕����ɕ`��͈͊O�ł���΁A�ł��߂��[�ɍ��킹��
				if (hitPos._x >= square->_pos._x + square->_size._x / 2)
					hitPos._x = square->_pos._x + square->_size._x / 2;
				//�{�[�������̕����ɕ`��͈͊O�ł���΁A�ł��߂��[�ɍ��킹��
				else if (hitPos._x <= square->_pos._x - square->_size._x / 2)
					hitPos._x = square->_pos._x - square->_size._x / 2;
			}
		);
		
		//�ȍ~�A���l�ɂ��Čv�Z

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
		return; //�ڐG����Ȃ�
	}

	/*
		(2)
		�ڐG�_�����߂���A������g���ăo�E���h�����x�N�g����
		���߁A�ڐG��������i������(���̔���)
	*/

	div = ball->_pos - hitPos; //�ڐG�_����{�[���̒��S�ւ̕����x�N�g��

	//�{�[���̒��S�ƐڐG�_�Ƃ̋������A�{�[���̔��a�ƈ�v���Ȃ����
	//�ڐG���Ă��Ȃ����ƂɂȂ�̂ŁA�����^����������
	if (div.magnitude() > ball->_r) {
		ball->_key._y = 1; //�����x�v�Z���s��
		return;
	}

	/*
		(3)
		2�̔�������z������A�o�E���h�����x�N�g���𐳋K�����A�e�����̔����䗦�����߂�
		�����āA���̌��ʂƔ����W�����l�����Ȃ���A�o�E���h��̑��x�����߂�
	*/

	div = div.normalize();
	Vector3 speed = ball->_v - square->_v; //�ǂƃ{�[���̑��Α��x(�ǂ��猩���{�[���̑��x)

	//�ȉ��A�e�����̔��������Ƒ��x�̐ς����ł���Δ����������{��
	tx = thread(
		[&div, &speed, &ball, &square]() {
			if (div._x * speed._x < 0) {
				ball->_t._x = 0;
				ball->_a._x = -1 * ball->_a._x;
				ball->_v0._x = -1 * speed._x * ball->_e * fabs(div._x);
				//�o�E���h��̃{�[�����x���ǂƓ����������A�{�[���̑������ǂ̑����������������
				//�ǂɉ������`�Ń{�[�����ړ�������
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
					ball->_key._y = 0; //�����x�v�Z���Ȃ�
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
	//�|�C���g�v�Z�̓����V���b�g�ɂ���x�܂�
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
	vector<thread> threads; //���񏈗��z��

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

	for (auto& t : threads) t.join(); //����
}

void 
Application::shoot(int x, int y) {
	//�{�[�����V���[�g����ɂ̓{�[���̐������s���Ă���
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
