#include "Draw.hpp"
#include "LoadThread.hpp"
#include "LoadMainThread.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);				// ウィンドウにする
	SetGraphMode(640, 480, 32);			// 画面サイズを決める

	DxLib_Init();						// 初期化処理

	SetDrawScreen(DX_SCREEN_BACK);		// 裏描画

	setlocale(LC_ALL, "japanese");		// ロケール設定
	
	LoadThread* loadThread = new LoadThread();					// 非同期で行うロード処理
	LoadMainThread* loadMainThread = new LoadMainThread();		// 非同期でメインで行うロード画面のようなものの処理

	Draw* draw = NULL;			// ロード後にロードしたファイルを渡す先

	const int max = 10;		// ロードする個数

	std::string str[max];		// ロードするファイルの名前
	str[0] = "1.jyn";
	str[1] = "2.jyn";
	str[2] = "3.jyn";
	str[3] = "4.jyn";
	str[4] = "5.jyn";
	str[5] = "3.jyn";
	str[6] = "1.jyn";
	str[7] = "2.jyn";
	str[8] = "3.jyn";
	str[9] = "6.wyn";

	ELOADFILE type[max];		// ロードするファイルの形式
	type[0] = ELOADFILE::graph;
	type[1] = ELOADFILE::graph;
	type[2] = ELOADFILE::graph;
	type[3] = ELOADFILE::graph;
	type[4] = ELOADFILE::graph;
	type[5] = ELOADFILE::graph;
	type[6] = ELOADFILE::graph;
	type[7] = ELOADFILE::graph;
	type[8] = ELOADFILE::graph;
	type[9] = ELOADFILE::soundmem;

	int flag = 0;			// シーン移動を簡略的に行うための変数
	bool threadEndFlag = false;

	//Draw* draw = new Draw();

	// 本編
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		if (flag == 0)		// ロードを行う
		{
			loadThread->Run(max, str, type);
			loadMainThread->Run();

			threadEndFlag = loadThread->Stop();
			loadMainThread->SetThreadEndFlag(threadEndFlag);
			flag = loadMainThread->Stop();
		}
		else if (flag == 1)		// ロードからシーンを移り変わる
		{
			draw = new Draw(loadThread->GetFile(0), loadThread->GetFile(1), loadThread->GetFile(2), loadThread->GetFile(3), loadThread->GetFile(4), loadThread->GetFile(5), loadThread->GetFile(6), loadThread->GetFile(7), loadThread->GetFile(8), loadThread->GetFile(9));
			delete loadThread;
			delete loadMainThread;

			flag = 2;
		}
		else		// ロード後のシーン処理
		{
			draw->Process();
		}
		//draw->Process();
	}

	delete draw;

	DxLib_End();
	return 0;
}