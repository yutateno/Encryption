#pragma once
#include "MediaLoad.hpp"

// �񓯊����s��
class LoadThread : public MediaLoad
{
private:
	std::vector<std::thread>ths;		// �񓯊����s������
	int fileName[30];

	void MyNextLoad(std::string path, int& file, ELOADFILE type);		// �񓯊����s�����\�b�h

public:
	LoadThread() {};
	~LoadThread() {};

	void Run(int max, std::string* path, ELOADFILE* type);		// �s��

	bool Stop();		// �I���𒲂ׂ�

	int GetFile(int number);		// ���[�h�������̂�n��
};