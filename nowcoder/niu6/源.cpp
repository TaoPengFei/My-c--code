#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
//#include <vector>
#include <string>

#if 0
//����С����һ��W*H��������ӣ�������б��Ϊ0~H-1��������б��Ϊ0~W-1��ÿ������������Է�һ�鵰�⣬�������鵰���ŷ����þ��벻�ܵ���2
int main()
{
	int w, h;
	int count = 0;
	while (cin >> w >> h)
	{
		vector<vector<int>> a;
		a.resize(w);
		for (auto& e : a)
		{
			e.resize(h, 1);
		}
		for (int i = 0; i<w; i++)
		{
			for (int j = 0; j<h; j++)
			{
				if (a[i][j] == 1)
				{
					++count;

					if (i + 2<w)
						a[i + 2][j] = 0;
					if (j + 2<h)
						a[i][j + 2] = 0;
				}
             }
         }
         cout<<count;
     }
     return 0;                                                                                                     
 }
#endif

//���ַ���ת��Ϊ����
#if 1
class Solution
{
public:
	int StrToInt(string str)
	{
		if (str.empty())
			return 0;
		int flag = 1;
		int sum=0;

		if (str[0] == '-')
		{
			flag = -1;
		}
		else if (str[0] == '+')
		{
			flag = 1;
		}
		for (int i=0; i < str.length(); i++)
		{
			if (str[i] <= '9'&&str[i] >= '0')
			{
				sum = sum * 10 + str[i] - '0';
			}
			else
			{
				sum = 0;
				break;
			}
				
		}
		cout << flag*sum;
	}
};
#endif

int main()
{
	Solution s;
	string str = "1234";
	s.StrToInt(str);
	return 0;
}