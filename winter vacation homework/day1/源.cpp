#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//ʵ�ֺ��� ToLowerCase() ���ú�������һ���ַ������� str ���������ַ����еĴ�д��ĸת����Сд��ĸ��
//֮�󷵻��µ��ַ���

#if 0
class Solution {
public:
	string toLowerCase(string str) {
		int i = 0;
		while (str[i] != '\0')
		{
			if (str[i] >= 'A'&&str[i] <= 'Z')
			{
				str[i] += 'a' - 'A';
			}
			++i;
		}
		return str;
	}
};
#endif
//����һ�����飬�������е�Ԫ�������ƶ� k ��λ�ã����� k �ǷǸ���
#if 0
class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		for (int i = 0; i<k; i++)
		{
			nums.insert(nums.begin(), nums.back());
			nums.erase(nums.end() - 1);
		}
	}
};
#endif