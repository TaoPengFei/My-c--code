#include "FileCompress.h"

int main()
{
	FileCompress fc;
	fc.CompressFile("1.txt");
	fc.UNCompressFile("1.hzp");
	fc.CompressFile("��̬�滮.docx");
	fc.UNCompressFile("��̬�滮.hzp");
	fc.CompressFile("���ٺ�-������Ϊ.mp4");
	fc.UNCompressFile("���ٺ�-������Ϊ.hzp");
	fc.CompressFile("���ٺ�-������Ϊ.flac");
	fc.UNCompressFile("���ٺ�-������Ϊ.hzp");
	return 0;
}