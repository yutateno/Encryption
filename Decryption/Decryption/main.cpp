#include "Draw.hpp"
#include "LoadThread.hpp"
#include "LoadMainThread.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);				// �E�B���h�E�ɂ���
	SetGraphMode(640, 480, 32);			// ��ʃT�C�Y�����߂�

	DxLib_Init();						// ����������

	SetDrawScreen(DX_SCREEN_BACK);		// ���`��

	setlocale(LC_ALL, "japanese");		// ���P�[���ݒ�
	
	LoadThread* loadThread = new LoadThread();					// �񓯊��ōs�����[�h����
	LoadMainThread* loadMainThread = new LoadMainThread();		// �񓯊��Ń��C���ōs�����[�h��ʂ̂悤�Ȃ��̂̏���

	Draw* draw = NULL;			// ���[�h��Ƀ��[�h�����t�@�C����n����

	const int max = 10;		// ���[�h�����

	std::string str[max];		// ���[�h����t�@�C���̖��O
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

	ELOADFILE type[max];		// ���[�h����t�@�C���̌`��
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

	int flag = 0;			// �V�[���ړ����ȗ��I�ɍs�����߂̕ϐ�
	bool threadEndFlag = false;

	//Draw* draw = new Draw();

	// �{��
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		if (flag == 0)		// ���[�h���s��
		{
			loadThread->Run(max, str, type);
			loadMainThread->Run();

			threadEndFlag = loadThread->Stop();
			loadMainThread->SetThreadEndFlag(threadEndFlag);
			flag = loadMainThread->Stop();
		}
		else if (flag == 1)		// ���[�h����V�[�����ڂ�ς��
		{
			draw = new Draw(loadThread->GetFile(0), loadThread->GetFile(1), loadThread->GetFile(2), loadThread->GetFile(3), loadThread->GetFile(4), loadThread->GetFile(5), loadThread->GetFile(6), loadThread->GetFile(7), loadThread->GetFile(8), loadThread->GetFile(9));
			delete loadThread;
			delete loadMainThread;

			flag = 2;
		}
		else		// ���[�h��̃V�[������
		{
			draw->Process();
		}
		//draw->Process();
	}

	delete draw;

	DxLib_End();
	return 0;
}