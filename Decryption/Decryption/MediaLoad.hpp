#pragma once
#ifndef _ME_MediaLoad_HPP
#define _ME_MediaLoad_HPP

#include "DxLib.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

enum class ELOADFILE { graph, soundmem, mv1model };

class MediaLoad
{
private:
	static const int rad = 0x2546;						// �����L�[
	static unsigned int file_size(std::ifstream &fin);	// �t�@�C���ǂݍ���

public:
	MediaLoad() {};
	~MediaLoad() {};


	static void MyLoad(std::string path, int& file, ELOADFILE type);	// ���f�B�A�̃��[�h���s��
};

#endif // !_ME_MediaLoad_HPP