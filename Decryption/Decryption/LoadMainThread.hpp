#pragma once
#include "MediaLoad.hpp"

// ���[�h��ʓI�Ȃ��̂̂��߂̔񓯊�
class LoadMainThread
{
private:
	int draw;		// ���[�h��ʓI��
	std::thread main_thre;		// ���[�h��ʓI�Ȃ��̂��s���񓯊�
	bool flag;				// ���[�h���I��������ǂ���

public:
	LoadMainThread();
	~LoadMainThread();

	void Process();		// �񓯊��ōs�����\�b�h

	void Run();		// �s��

	bool Stop();		// �I���𒲂ׂ�

	void SetThreadEndFlag(bool flag);		// �񓯊��̏I�����m�F����
};

