#pragma once
#include "HuffmanTree.hpp"
#include <string>
#include <vector>
using namespace std;

//�ַ��Ľṹ�弯��
struct CharInfo
{
	//�洢һ���ַ�,�з��ŵ�char�����Χ��-128~127
	//�����������ֵ�ʱ�򣬺��ֵı�����ܴ���127��һ������127���Ǹ����ˣ��Ժ���Ҫ�ô˱������±꣬�ͻ������,������Ҫʹ���޷�������
	unsigned char _ch;
	unsigned long long _count;//long long��ֹ�����ַ��Ĵ���̫��
	string _strCode;//���ַ����ַ�������
	CharInfo(unsigned long long count = 0)
		:_count(count)
	{}
	//��������
	CharInfo operator+(const CharInfo& c)
	{
		return CharInfo(_count + c._count);
	}
	bool operator>(const CharInfo& c)
	{
		return _count > c._count;
	}
	bool operator!=(const CharInfo& c)const
	{
		return _count != c._count;
	}
};

class FileCompress
{
	friend class GZIP;
public:
	FileCompress();//���캯��
	void CompressFile(const string& strFilePath);//�ļ�ѹ������
	void UNCompressFile(const string& strFilePath);//�ļ���ѹ������
	void Getline(FILE* pf, string& strContent);
private:
	void GetHuffmanCode(HTNode<CharInfo>* pRoot);//Huffman����
	void WriteHeadInfo(FILE* pf,const string& strFileName);//��ѹ����Ҫԭ�����ļ���Ϣ[�ļ���׺���ַ��������ַ������Ӧ�Ĵ�����ѹ���ļ�]
	
private:
	vector<CharInfo> _CharInfo;//256���ַ��ṹ������
};