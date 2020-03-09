#include "FileCompress.h"
#include "LZ77.h"
#include <cstdio>

LZ77 lz;
FileCompress fc;
void FCompress(const std::string& strFilePath)
{
	lz.CompressFile(strFilePath);
	std::string strfilename(strFilePath.c_str());
	size_t finish = strfilename.rfind('.');
	std::string strname(strfilename.substr(0, finish));
	strname += ".lzp";
	fc.CompressFile(strname);

	//ɾ����ʱ�ļ�
	while (remove(strname.c_str()) == 0);
	while (remove("3.txt") == 0);
}

void FUnCompress(const std::string& strFilePath)
{
	fc.UNCompressFile(strFilePath);
	std::string strfilename(strFilePath.c_str());
	size_t finish = strfilename.rfind('.');
	std::string strUNname(strfilename.substr(0, finish));
	strUNname += ".lzp";
	lz.UNComressFile(strUNname);

	//ɾ����ʱ�ļ�
	while (remove(strUNname.c_str()) == 0);
}

int main()
{
	//FCompress("�ڵ����ֱ�.txt");
	//FUnCompress("�ڵ����ֱ�.hzp");
	//FCompress("���ٺ�-������Ϊ1.flac");
	//FUnCompress("���ٺ�-������Ϊ1.hzp");
	FCompress("���ٺ�-������Ϊ.mp4");
	FUnCompress("���ٺ�-������Ϊ.hzp");
	return 0;
}