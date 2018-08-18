//�C���N���[�h
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

//typedef�錾
typedef unsigned char BYTE;
typedef unsigned int UINT;

std::mutex mtx;

//�t�@�C���T�C�Y��Ԃ�
UINT file_size(ifstream &fin);

void MyLoadGraph(string path, int& name);

void Main_Thread(int draw);

bool flag = false;
int endNum = 0;
int max = 6;

//���C���֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);					// �E�B���h�E�ɂ���
	SetGraphMode(640, 480, 32);			// ��ʃT�C�Y�����߂�

	DxLib_Init();						// ����������

	SetDrawScreen(DX_SCREEN_BACK);		// ���`��

	setlocale(LC_ALL, "japanese");//���P�[���ݒ�

	int drawFile[6];

	int draw = LoadGraph("Media.jpg");

	std::vector<std::thread>ths(6);
	std::thread main_thre;

	ths[0] = std::thread(MyLoadGraph, "1.jyn", std::ref(drawFile[0]));
	ths[1] = std::thread(MyLoadGraph, "2.jyn", std::ref(drawFile[1]));
	ths[2] = std::thread(MyLoadGraph, "3.jyn", std::ref(drawFile[2]));
	ths[3] = std::thread(MyLoadGraph, "4.jyn", std::ref(drawFile[3]));
	ths[4] = std::thread(MyLoadGraph, "5.jyn", std::ref(drawFile[4]));
	ths[5] = std::thread(MyLoadGraph, "6.jyn", std::ref(drawFile[5]));
	main_thre = std::thread(Main_Thread, draw);

	// �{��
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		if (!flag)
		{
			for (auto &th : ths)
			{
				th.join();
			}
			main_thre.join();
		}
		DrawGraph(0, 0, drawFile[0], false);
		DrawGraph(320, 0, drawFile[1], false);
	}

	DxLib_End();
	return 0;
}


// �t�@�C���T�C�Y�𒲂ׂ�
UINT file_size(ifstream &fin) {
	UINT pos = fin.tellg();//���݈ʒu�ۑ�

	UINT size = fin.seekg(0, ios::end).tellg();//�Ō�ɃV�[�N���Ĉʒu�擾���T�C�Y

	fin.seekg(pos);//���̈ʒu�ɖ߂�

	return size;//�T�C�Y��Ԃ�
}

// �t�@�C���̓ǂݍ���
void MyLoadGraph(string path, int& name)
{
	std::lock_guard<std::mutex> lock(mtx);

	vector<BYTE> data;  //�t�@�C���f�[�^
	UINT size;          //�t�@�C���T�C�Y
	int rad = 0x3434;
	string outstr;

	{//�t�@�C���̓ǂݍ���

		ifstream fin(path.c_str(), ios::binary);//�t�@�C���I�[�v��
		
		size = file_size(fin);//�t�@�C���T�C�Y�擾
		data.resize(size);//�������m��
		fin.read((char*)&data[0], size);//�ǂݍ���

		fin.close();
	}

	{//���
		for (UINT i = 0; i < size; i++) {//�S�f�[�^���[�v
			data[i] = (data[i] ^ rad);
			if (i % 3 == 0)
			{
				data[i] = (data[i] ^ rad);
			}
			data[i] = ~data[i];
			data[i] = (data[i] ^ rad);//�r���I�_���a�����
		}
	}

	{//�ۑ�
		outstr = path;
		outstr.append("del");
		ofstream fout(outstr.c_str(), ios::binary);
		fout.write((char*)&data[0], size);
		fout.close();
	}

	name = LoadGraph(outstr.c_str());

	std::remove(outstr.c_str());

	endNum++;
}

// ���[�h��ʂ̕���
void Main_Thread(int draw)
{
	int test = 0;
	do
	{
		test++;
		ClearDrawScreen();
		DrawGraph(test, 0, draw, false);
		ScreenFlip();
	} while (endNum < max);
	flag = true;
}