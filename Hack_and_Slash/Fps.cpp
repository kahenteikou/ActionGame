#include "Fps.hpp"

int Fps::count = 0;
int Fps::startCount = 0;

//�R���X�g���N�^
Fps::Fps() {
	startTime = 0;
	count = 0;
	fps = 0;
}

//�X�V
bool Fps::Update() {
	startCount++;
	if (count == 0) { //1�t���[���ڂȂ玞�����L��
		startTime = GetNowCount();
	}
	if (count == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		fps = 1000.f / ((t - startTime) / (float)N);
		count = 0;
		startTime = t;
	}
	count++;
	return true;
}

//���݂̃t���[�����擾
int Fps::getFrame() {
	return count;
}

//�o�߃t���[�����擾
int Fps::getElapsed()
{
	return startCount;
}



//�ҋ@
void Fps::Wait() {
	int tookTime = GetNowCount() - startTime;	//������������
	int waitTime = count * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {

		Sleep(waitTime);	//�ҋ@
	}

	//�o�߃t���[��
	if (startCount > 60000) {
		startCount = 0;
	}
}