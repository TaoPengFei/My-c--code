#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>
using namespace std;

//����һ����������ɵķǿ���������ʾ�ķǸ��������ڸ����Ļ����ϼ�һ�����λ���ִ�����������λ�� ��
//����ÿ��Ԫ��ֻ�洢�������֡�
class Solution {
public:
	vector<int> plusOne(vector<int>& digits) {
		int index = digits.size() - 1;
		int jw=1;
		while (jw)
		{
			jw = 0;

			digits[index]++;
			if (digits[0]>9)
			{
				digits.resize(digits.size() + 1);
				for (int i = digits.size()-1; i > 1; i--)
				{
					digits[i] = digits[i - 1];
				}
				digits[1] = digits[0] & 1;
				digits[0] /= 10;
				break;
			}
			if (digits[index]>9)
			{
				jw = digits[index]/10;
				digits[index] &= 1;
				index--;
			}
		}
		return digits;
	}
};

//����һ���ǿ����飬���ش������е������������������ڣ��򷵻���������������Ҫ���㷨ʱ�临�Ӷȱ�����O(n)
class Solution {
public:
	int thirdMax(vector<int>& nums) {
		if (nums.size() == 1)
		{
			return nums[0];
		}
		sort(nums.begin(), nums.end());
		int count = 1;
		for (int i = nums.size() - 2; i >= 0; i--)
		{
			if (nums[i] == nums[i + 1])
				continue;
			count++;
			if (count == 3)
				return nums[i];
		}
		return nums[nums.size() - 1];
	}
};



int main()
{
	vector<int> v = {9,9,9,9};
	Solution s;
	vector<int> v1=s.plusOne(v);
	return 0;
}


