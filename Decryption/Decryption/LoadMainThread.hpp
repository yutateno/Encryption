#pragma once
#include "MediaLoad.hpp"

// ロード画面的なもののための非同期
class LoadMainThread
{
private:
	int draw;		// ロード画面的な

public:
	LoadMainThread();
	~LoadMainThread();

	void Process(int num);		// 非同期で行うメソッド
};

