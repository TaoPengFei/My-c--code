#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<string>

class Solution {
public:
	char firstUniqChar(string s)
	{

		// 1. ͳ��ÿ���ַ����ֵĴ���
		int count[256] = { 0 };
		for (auto e : s)
		{
			count[e]++;
		}

		// 2. �ҵ�һ��ֻ����һ�ε��ַ�
		for (size_t i = 0; i < s.size(); ++i)
		{
			if (1 == count[s[i]])
				return s[i];
		}
		return -1;
	}
};

void Testchar()
{
	Solution s;
	cout << s.firstUniqChar("hello world") << endl;
}
int main()
{
	Testchar();
	return 0;
}