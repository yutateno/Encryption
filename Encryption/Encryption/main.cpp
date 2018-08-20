//�C���N���[�h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//typedef�錾
typedef unsigned char BYTE;
typedef unsigned int UINT;

//�t�@�C���T�C�Y��Ԃ�
UINT file_size(ifstream &fin);

//���C���֐�
int main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "�t�@�C�����h���b�O�h���b�v���Ă�������" << endl;
		getchar();
		return -1;
	}

	string path = argv[1];//���̓t�@�C���p�X
	vector<BYTE> data;  //�t�@�C���f�[�^
	UINT size;          //�t�@�C���T�C�Y
	int rad = 0x2546;

	{//�t�@�C���̓ǂݍ���
		setlocale(LC_ALL, "japanese");//���P�[���ݒ�

		ifstream fin(path.c_str(), ios::binary);//�t�@�C���I�[�v��

		if (fin.fail()) {
			return -1; //�t�@�C���ǂݍ��݃G���[
		}

		size = file_size(fin);//�t�@�C���T�C�Y�擾
		data.resize(size);//�������m��
		fin.read((char*)&data[0], size);//�ǂݍ���

		fin.close();
	}

	{//�Í���
		for (UINT i = 0; i < size; i += 5) {//�S�f�[�^���[�v
			data[i] = (data[i] ^ rad);//�r���I�_���a�����
		}
	}

	{//�ۑ�
		string outstr = path;
		outstr.erase(outstr.end() - 2, outstr.end());
		outstr.append("yn");
		ofstream fout(outstr.c_str(), ios::binary);
		fout.write((char*)&data[0], size);
		fout.close();
	}

	printf("�Í�������");
	getchar();

	return 0;

}

//�t�@�C���T�C�Y��Ԃ�
UINT file_size(ifstream &fin) {
	UINT pos = fin.tellg();//���݈ʒu�ۑ�

	UINT size = fin.seekg(0, ios::end).tellg();//�Ō�ɃV�[�N���Ĉʒu�擾���T�C�Y

	fin.seekg(pos);//���̈ʒu�ɖ߂�

	return size;//�T�C�Y��Ԃ�
}