#define _CRT_SECURE_NO_WARNINGS 1
#include "LZ77.h"
#include "FileCompress.h"
#include <iostream>
#include <assert.h>
using namespace std;

const USH MIN_LOOKAHEAD = MAX_MATCH + MIN_MATCH + 1;//�Ҵ���ʣ����ֽ���
const USH MAX_DIST = WSIZE - MIN_LOOKAHEAD;//���л���������ѹ���ֽڣ��еĿ�ͷ

LZ77::LZ77()
	:_pWin(new UCH[WSIZE*2])
	, _ht(WSIZE)
{}
LZ77::~LZ77()
{
	delete[] _pWin;
	_pWin = nullptr;
}

void LZ77::CompressFile(const std::string& strFilePath)
{
	FILE* fIn = fopen(strFilePath.c_str(),"rb");
	if (nullptr == fIn)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	//��ȡ�ļ���С
	fseek(fIn,0,SEEK_END);
	ULL fileSize = ftell(fIn);
	
	//����ļ�̫С����ѹ��
	if (fileSize <= MIN_MATCH)
	{
		cout << "�ļ�̫С����ѹ��" << endl;
		return;
	}

	//ȷ��ѹ���ļ���
	std::string strfilename(strFilePath.c_str());
	size_t finish = strfilename.rfind('.');
	std::string strUNname(strfilename.substr(0, finish));
	strUNname += ".lzp";

	//��ѹ���ļ��ж�ȡһ�������������ݵ�������
	fseek(fIn,0,SEEK_SET);
	size_t lookAhead = fread(_pWin,1,2*WSIZE,fIn);//��ʾ���л�������ʣ���ӽڵĸ���

	USH hashAddr = 0;
	//����ǰ�����ַ�����ǰ�����ֽڷ����ϣ��
	for (USH i = 0; i < MIN_MATCH - 1; ++i)
		_ht.HashFunc(hashAddr,_pWin[i]);

	//ѹ��
	FILE* fOUT = fopen(strUNname.c_str(), "wb");
	assert(fOUT);

	std::string postFix = strfilename.substr(strfilename.rfind('.'));
	postFix += "\n";
	fwrite(postFix.c_str(),1,postFix.size(),fOUT);

	USH start = 0;
	USH matchHead = 0;
	USH curMatchLength = 0;
	USH curMatchDist = 0;

	//�����йصı���
	UCH chFlag = 0; 
	UCH bitCount = 0;
	bool IsLen = false;
	FILE* fOutF = fopen("3.txt","wb");
	assert(fOutF);

	while (lookAhead)
	{
		//����ǰ�����ַ����뵽��ϣ���У�����ȡƥ������ͷ
		_ht.Insert(matchHead,_pWin[start+2],start,hashAddr);

		curMatchLength = 0;
		curMatchDist = 0;

		//��֤�ڲ��һ��������Ƿ��ҵ�ƥ��--�ƥ��
		if (matchHead)
		{ 
			//˳��ƥ�������ƥ�䣬���մ���<���ȣ�����>��
			curMatchLength = longestMatch(matchHead,curMatchDist,start);
		}
		//��֤�Ƿ��ҵ�ƥ��
		if (curMatchLength < MIN_MATCH)
		{
			//Ϊ��ƥ�䣬��startλ�õ��ַ�д�뵽ѹ���ļ���
			fputc(_pWin[start],fOUT);
			WriteFlag(fOutF, chFlag, bitCount, false);
			++start;
			lookAhead--;
		}
		else
		{
			//�ҵ�ƥ�䣬��<���ȣ�����>��д�뵽ѹ���ļ���
			UCH chLen = curMatchLength-3;
			fputc(chLen, fOUT);//д����
			fwrite(&curMatchDist,sizeof(curMatchDist),1,fOUT);//д����

			WriteFlag(fOutF, chFlag, bitCount, true);//д���

			//�������л�������ʣ���ֽ���
			lookAhead -= curMatchLength;

			//���Ѿ�ƥ����ַ�����������һ�齫����뵽��ϣ����
			--curMatchLength;
			while (curMatchLength)
			{
				start++; 
				_ht.Insert(matchHead,_pWin[start+2],start,hashAddr);
				curMatchLength--;
			}
			++start;//ѭ����start�ټ���һ��
		}
		//������л�������ʣ���ַ��ĸ���
		if (lookAhead <= MIN_LOOKAHEAD)
			FileWindow(fIn,lookAhead,start);
	}
	if (bitCount > 0 && bitCount < 8)
	{
		chFlag <<= (8-bitCount);
		fputc(chFlag,fOutF);
	}
	fclose(fOutF);

	MergeFile(fOUT,fileSize);

	fclose(fIn); 
	fclose(fOUT);
	//��������������Ϣ����ʱ�ļ�ɾ����
}

void LZ77::FileWindow(FILE* fIn, size_t& lookAhead, USH& start)
{
	//ѹ���Ѿ����е��Ҵ������л�����ʣ�����ݲ���MIN_LOOKAHEAD
	if (start >= WSIZE)
	{
		//���Ҵ��е����ݰ��Ƶ���
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		memset(_pWin + WSIZE, 0, WSIZE);
		start -= WSIZE;
		//���¹�ϣ��
		_ht.Update();
		//���Ҵ��в���һ��WSIZE���Ĵ�ѹ������
		if (!feof(fIn))
			lookAhead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
	
}

void LZ77::MergeFile(FILE* fOut, ULL fileSize)
{
	//��ѹ�����ݺͱ����Ϣ�ļ��ϲ�
	//��ȡ����ļ����ݣ�Ȼ�󽫽��д�뵽ѹ���ļ���
	FILE* fInF = fopen("3.txt", "rb");
	size_t flagSize = 0;
	UCH* pReadbuff = new UCH[1024];
	while (true)
	{
		size_t rdSize = fread(pReadbuff, 1, 1024, fInF);
		if (0 == rdSize)
			break;
		fwrite(pReadbuff, 1, rdSize, fOut);
		flagSize += rdSize;
	}
	fwrite(&flagSize, sizeof(flagSize), 1, fOut);
	fwrite(&fileSize, sizeof(fileSize), 1, fOut);
	delete[] pReadbuff;
	fclose(fInF);
}

//chFlag�����ֽ��е�ÿ������λ���������ֵ�ǰ�ֽ���ԭ�ַ����ǳ���
//bitCount�����ֽ��еĶ��ٸ�����λ�Ѿ�������
//isCharOrLen��������ֽ���ԭ�ַ����ǳ���
//0��ԭ�ַ�
//1������
void LZ77::WriteFlag(FILE* fOut, UCH& chFlag, UCH& bitCount, bool isCharOrLen)
{
	chFlag <<= 1;
	if (isCharOrLen)
		chFlag |= 1;
	bitCount++;
	if (bitCount == 8)
	{
		//���ñ��д�뵽ѹ���ļ���
		fputc(chFlag,fOut);
		chFlag = 0;
		bitCount = 0;
	}
}

//ƥ�䣺���ڲ��һ������н��еģ����һ������п��ܻ��ҵ����ƥ��
//�������Ҫ�ƥ��
//ע�⣺���ܻ�������״��--�����������������ƥ�����
//   ƥ������MAX_DIST��Χ�ڽ���ƥ��ģ�̫Զ�ľ����򲻽���ƥ��
USH LZ77::longestMatch(USH matchHead, USH& curMatchDist,USH start)
{
	UCH curMatchLen = 0;//һ��ƥ�䳤��
	UCH maxMatchLen = 0;
	UCH maxMatchCount = 255;//��ֹ��״��
	USH curMatchStart = 0;//��ǰƥ���ڲ��һ���������ʼλ��

	//����ƥ��ʱ������̫Զ�����ܳ���MAX_DIST
	USH limit = start > MAX_DIST ? start - MAX_DIST : 0;
	do
	{
		//ƥ�䷶Χ:���л�����
		UCH* pstart = _pWin + start;
		UCH* pend = pstart + MAX_MATCH;
		//���һ�����ƥ�䴮����ʼ
		UCH* pMatchStart = _pWin + matchHead;

		curMatchLen = 0;
		while (pstart < pend&&*pstart == *pMatchStart)
		{
			curMatchLen++;
			pstart++;
			pMatchStart++;
		}

		//һ��ƥ�����
		if (curMatchLen>maxMatchLen)
		{
			maxMatchLen = curMatchLen;
			curMatchStart = matchHead;
		}
	} while((matchHead=_ht.GetNext(matchHead))>limit&&maxMatchCount--);

	curMatchDist = start - curMatchStart;
	return maxMatchLen;
}

//��ѹ��
void LZ77::UNComressFile(const std::string& strFilePath)
{
	//�ж��ļ���׺�Ƿ���ȷ
	std::string postFix = strFilePath.substr(strFilePath.rfind('.'));
	if (".lzp" != postFix)
	{
		cout << "ѹ���ļ���ʽ����" << endl;
		return;
	}

	//��ѹ���ļ��ͱ���ļ�
	FILE* fInD = fopen(strFilePath.c_str(), "rb");
	if (nullptr == fInD)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	//����������ݵ��ļ�ָ��
	FILE* fInF = fopen(strFilePath.c_str(), "rb");
	if (nullptr == fInF)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	//��ȡԴ�ļ���С
	ULL fileSize = 0;
	fseek(fInF,0-sizeof(fileSize),SEEK_END);
	fread(&fileSize,sizeof(fileSize),1,fInF);
	//��ȡ��Ǵ�С
	size_t flagSize = 0;
	fseek(fInF, 0 - sizeof(fileSize)-sizeof(flagSize), SEEK_END);
	fread(&flagSize,sizeof(flagSize),1,fInF);
	//����ȡ�����Ϣ���ļ�ָ���ƶ������������ݵ���ʼλ��
	fseek(fInF,0-sizeof(flagSize)-sizeof(fileSize)-flagSize,SEEK_END);

	FILE* fInFo = fopen(strFilePath.c_str(), "rb");
	if (nullptr == fInFo)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	fseek(fInFo, 0, SEEK_SET);
	postFix = "";
	Getline(fInFo, postFix);

	size_t finish = strFilePath.rfind('.');//�Ӻ���ǰ���ҵ�����±�
	std::string strUNFileName(strFilePath.substr(0, finish));//��ȡ��׺֮ǰ�ļ���
	strUNFileName += "(����)";
	strUNFileName += postFix;//�ļ�������Դ�ļ���׺��

	FILE* fOut = fopen(strUNFileName.c_str(), "wb");
	assert(fOut);

	//������ԭƥ�䴮,��ȡǰ��ƥ���е�����
	FILE* fR = fopen(strUNFileName.c_str(), "rb");

	UCH bitCount = 0;
	UCH chFlag = 0;
	ULL encodeCount = 0;
	int len = postFix.size() + 1;
	while (len--)
	{
		UCH ch = fgetc(fInD);
	}
	while (encodeCount < fileSize)
	{
		if (0 == bitCount)
		{
			chFlag=fgetc(fInF);
			bitCount = 8;
		}
		if (chFlag & 0x80) 
		{
			//���Ⱦ����
			USH matchLen = fgetc(fInD)+3;
			USH matchDist = 0;
			fread(&matchDist,sizeof(matchDist),1,fInD);

			fflush(fOut);//��ջ�����

			encodeCount += matchLen;//�����Ѿ������ֽ����Ĵ�С

			UCH ch;
			fseek(fR,0-matchDist,SEEK_END);
			while (matchLen)
			{
				ch = fgetc(fR);
				fputc(ch,fOut);
				matchLen--;
				fflush(fOut);
			}
		}
		else
		{
			//ԭ�ַ�
			UCH ch = fgetc(fInD);
			fputc(ch,fOut);
			encodeCount += 1;
		}
		chFlag <<= 1;
		bitCount--;
	}
	fclose(fInD);
	fclose(fInF);
	fclose(fOut);
	fclose(fR);
	fclose(fInFo);
}

void LZ77::Getline(FILE* pf, std::string& strContent)
{
	while (!feof(pf))//û�е����ļ���β
	{
		char ch = fgetc(pf);//����ַ��Ķ�ȡ
		if ('\n' == ch)//�������з���˵��һ�ж�����
			break;

		strContent += ch;//���ַ�����������ַ�
	}
}