#pragma once
#include "MediaLoad.hpp"

// ���[�h��ʓI�Ȃ��̂̂��߂̔񓯊�
class LoadMainThread
{
private:
	int draw;		// ���[�h��ʓI��

public:
	LoadMainThread();
	~LoadMainThread();

	void Process(int num);		// �񓯊��ōs�����\�b�h
};

