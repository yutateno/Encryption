#pragma once
#include "MediaLoad.hpp"

// ロード画面的なもののための非同期
class LoadMainThread
{
private:
	int draw;		// ロード画面的な
	std::thread main_thre;		// ロード画面的なものを行う非同期
	bool flag;				// ロードが終わったかどうか

public:
	LoadMainThread();
	~LoadMainThread();

	void Process();		// 非同期で行うメソッド

	void Run();		// 行う

	bool Stop();		// 終了を調べる

	void SetThreadEndFlag(bool flag);		// 非同期の終了を確認する
};

