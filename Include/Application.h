#ifndef ___CLASS_APPLICATION
#define ___CLASS_APPLICATION

#include<vector>

class MyBall;
class MySquare;
class MyPointArea;
class Application {
	//�V���O���g��
	Application();
	Application(const Application&);
	Application& operator=(const Application&);

public:
	//�V���O���g��
	//���͈̂�����Ɍ��肷��
	static Application& instance();

	//�I�u�W�F�N�g�z����󂯎��
	std::vector<MyBall> _balls;
	std::vector<MySquare> _squares;
	std::vector<MyPointArea> _pointAreas;
	int _pointSum = 0; //�l���������v�|�C���g

	//�{�[���ƕǂ̏Փˉ��Z
	void calCollision(MyBall* ball, MySquare* square);
	//�{�[���ƃ|�C���g�l���G���A�̏Փˉ��Z
	//�����Ń|�C���g�̌v�Z���s��
	void calCollision(MyBall* ball, MyPointArea* pointArea);

	//�قȂ�I�u�W�F�N�g�Ԃ̏Փˉ��Z
	void update(double deltaTime);

	//�{�[�����V���b�g����
	void shoot(int x, int y);

	//�{�[���𐶐�����
	void resetBall();
};

#endif