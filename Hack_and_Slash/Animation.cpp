#include "Animation.hpp"
#include "Fps.hpp"

//�R���X�g���N�^
Animation::Animation(int c)
{
	clip = 0;		//���݂̔ԍ�
	maxClip = c;	//�ԍ��̐�
	nextFrame = 1;	//���̔ԍ��ɂȂ�t���[����
	first = false;	//�t���[�����Čv�Z���邩�ǂ����H
	isAnim = false;	//��񂾂��Đ��������ǂ����H
}


//�f�X�g���N�^
Animation::~Animation()
{

}

//�A�j���[�V���������[�v�Đ�
int Animation::getClip_loop(int speed)
{
	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//���̃N���b�v�̃t���[�����v�Z
		first = true;

//		return Clip;
	}
	
	
	if (Fps::getElapsed() == nextFrame) {

		clip++;

		//�ő�N���b�v�𒴂�����
		if (clip > maxClip) 
		{
			clip = 0;
		}

		first = false;
		return clip;
	}
	else 
	{
		return clip;
	}

}

//1�񂾂��擾
bool Animation::getClip(int& num, int speed)
{

	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//���̃N���b�v�̃t���[�����v�Z
		first = true;
	}


	if (Fps::getElapsed() >= nextFrame) {

		clip++;

		//�ő�N���b�v�𒴂�����
		if (clip > maxClip)
		{
			clip = 0;

			isAnim = true;
			first = false;
			return isAnim;
		}

		//printf("��������������\n");

		first = false;

		num = clip;
		return isAnim;
	}
	else
	{
		//printf("����������\n");
		num = clip;
		return isAnim;
	}

}













