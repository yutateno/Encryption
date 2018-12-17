#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned char BYTE;
typedef unsigned int UINT;

// ファイルサイズを返す
UINT file_size(ifstream &fin);


int main(int argc, char *argv[])
{
	// ドラッグアンドドロップでない起動の時
	if (argc < 2)
	{
		cerr << "ファイルをドラッグドロップしてください" << endl;
		int charTemp = getchar();
		return -1;
	}

	// 入力ファイルパス
	string path = argv[1];

	// ファイルデータ
	vector<BYTE> data;

	// ファイルサイズ
	UINT size;

	// 暗号キー
	int rad = 0x2546;

	// ロケール設定
	setlocale(LC_ALL, "japanese");


	/// ファイルの読み込み---------------------------------

	// ファイルオープン
	ifstream fin(path.c_str(), ios::binary);

	if (fin.fail()) return -1; // ファイル読み込みエラー

	// ファイルサイズ取得
	size = file_size(fin);

	// メモリ確保
	data.resize(size);

	// 読み込み
	fin.read((char*)&data[0], size);

	// ファイルクローズ
	fin.close();
	

	/// 暗号化--------------------------------------------------

	// 全データループ
	for (UINT i = 0; i < size; i += 5)
	{
		data[i] = (data[i] ^ rad);	// 排他的論理和を取る
	}
	
	/// 保存------------------------------------------------------

	// ファイルパスの仮置き
	string outstr = path;

	outstr.erase(outstr.end() - 2, outstr.end());	// 拡張子の後ろ2つを変更するため削除
	outstr.append("yn");							// 自分用に拡張子を作成
	ofstream fout(outstr.c_str(), ios::binary);		// バイナリデータとして書き込むよう設定
	fout.write((char*)&data[0], size);				// 書き込み
	fout.close();									// ファイルをクローズ
	
	printf("暗号化完了");			// 確認用表示
	int charTemp = getchar();						// 入力待ち

	return 0;

}

// ファイルサイズを返す
UINT file_size(ifstream &fin)
{
	UINT pos = fin.tellg();		// 現在位置保存

	UINT size = fin.seekg(0, ios::end).tellg();		// 最後にシークして位置取得→サイズ

	fin.seekg(pos);		// 元の位置に戻す

	return size;	// サイズを返す
}