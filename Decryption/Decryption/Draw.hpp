#pragma once
#include "Basic.hpp"
#include "MediaLoad.hpp"

class Draw : public Basic
{
private:
	int draw1, draw2, draw3, draw4, draw5, draw6, draw7, draw8, draw9, draw10;		// 非同期処理からロードしたファイルを渡す先

public:
	Draw();
	Draw(int draw1, int draw2);
	Draw(std::vector<int> draw);
	~Draw();

	void Process();		// 描画する
};

