#ifndef ___ANIMATION_HPP_
#define ___ANIMATION_HPP_

/*####################################################
* �A�j���[�V����
*
* ����
* �A�j���[�V�����̔ԍ����Ǘ�
######################################################*/
class Animation
{
public:

	Animation(int c);	//�R���X�g���N�^
	~Animation();		//�f�X�g���N�^

	//�A�j���[�V�����ԍ����擾

	int getClip_loop(int speed);		//���[�v�Ŏ擾
	bool getClip(int &num,int speed);	//1�񂾂��擾

private:


	bool first;
	int clip;		//���݂̔ԍ�
	int maxClip;	//�ԍ��̐�
	int nextFrame;	//���̔ԍ��܂ł̃t���[��
	bool isAnim;	//��񂾂��Đ��������ǂ����H
};


#endif
