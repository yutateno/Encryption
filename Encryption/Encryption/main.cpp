//インクルード
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//typedef宣言
typedef unsigned char BYTE;
typedef unsigned int UINT;

//ファイルサイズを返す
UINT file_size(ifstream &fin);

//メイン関数
int main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "ファイルをドラッグドロップしてください" << endl;
		getchar();
		return -1;
	}

	string path = argv[1];//入力ファイルパス
	vector<BYTE> data;  //ファイルデータ
	UINT size;          //ファイルサイズ
	int rad = 0x2546;

	{//ファイルの読み込み
		setlocale(LC_ALL, "japanese");//ロケール設定

		ifstream fin(path.c_str(), ios::binary);//ファイルオープン

		if (fin.fail()) {
			return -1; //ファイル読み込みエラー
		}

		size = file_size(fin);//ファイルサイズ取得
		data.resize(size);//メモリ確保
		fin.read((char*)&data[0], size);//読み込み

		fin.close();
	}

	{//暗号化
		for (UINT i = 0; i < size; i += 5) {//全データループ
			data[i] = (data[i] ^ rad);//排他的論理和を取る
		}
	}

	{//保存
		string outstr = path;
		outstr.erase(outstr.end() - 2, outstr.end());
		outstr.append("yn");
		ofstream fout(outstr.c_str(), ios::binary);
		fout.write((char*)&data[0], size);
		fout.close();
	}

	printf("暗号化完了");
	getchar();

	return 0;

}

//ファイルサイズを返す
UINT file_size(ifstream &fin) {
	UINT pos = fin.tellg();//現在位置保存

	UINT size = fin.seekg(0, ios::end).tellg();//最後にシークして位置取得→サイズ

	fin.seekg(pos);//元の位置に戻す

	return size;//サイズを返す
}