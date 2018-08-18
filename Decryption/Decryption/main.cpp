//インクルード
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

//typedef宣言
typedef unsigned char BYTE;
typedef unsigned int UINT;

std::mutex mtx;

//ファイルサイズを返す
UINT file_size(ifstream &fin);

void MyLoadGraph(string path, int& name);

void Main_Thread(int draw);

bool flag = false;
int endNum = 0;
int max = 6;

//メイン関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);					// ウィンドウにする
	SetGraphMode(640, 480, 32);			// 画面サイズを決める

	DxLib_Init();						// 初期化処理

	SetDrawScreen(DX_SCREEN_BACK);		// 裏描画

	setlocale(LC_ALL, "japanese");//ロケール設定

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

	// 本編
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


// ファイルサイズを調べる
UINT file_size(ifstream &fin) {
	UINT pos = fin.tellg();//現在位置保存

	UINT size = fin.seekg(0, ios::end).tellg();//最後にシークして位置取得→サイズ

	fin.seekg(pos);//元の位置に戻す

	return size;//サイズを返す
}

// ファイルの読み込み
void MyLoadGraph(string path, int& name)
{
	std::lock_guard<std::mutex> lock(mtx);

	vector<BYTE> data;  //ファイルデータ
	UINT size;          //ファイルサイズ
	int rad = 0x3434;
	string outstr;

	{//ファイルの読み込み

		ifstream fin(path.c_str(), ios::binary);//ファイルオープン
		
		size = file_size(fin);//ファイルサイズ取得
		data.resize(size);//メモリ確保
		fin.read((char*)&data[0], size);//読み込み

		fin.close();
	}

	{//解読
		for (UINT i = 0; i < size; i++) {//全データループ
			data[i] = (data[i] ^ rad);
			if (i % 3 == 0)
			{
				data[i] = (data[i] ^ rad);
			}
			data[i] = ~data[i];
			data[i] = (data[i] ^ rad);//排他的論理和を取る
		}
	}

	{//保存
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

// ロード画面の部分
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