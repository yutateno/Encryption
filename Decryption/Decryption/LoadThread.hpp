#pragma once
#include "MediaLoad.hpp"

// 非同期を行う
class LoadThread : public MediaLoad
{
private:
	std::vector<std::thread>ths;		// 非同期を行うだけ
	int fileName[30];

	void MyNextLoad(std::string path, int& file, ELOADFILE type);		// 非同期を行うメソッド

public:
	LoadThread() {};
	~LoadThread() {};

	void Run(int max, std::string* path, ELOADFILE* type);		// 行う

	bool Stop();		// 終了を調べる

	int GetFile(int number);		// ロードしたものを渡す
};