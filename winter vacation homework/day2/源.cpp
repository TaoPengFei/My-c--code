//����һ������ nums ��һ��ֵ val ������Ҫԭ���Ƴ�������ֵ���� val ��Ԫ�أ������Ƴ���������³��ȡ�
//��Ҫʹ�ö��������ռ䣬�������ԭ���޸��������鲢��ʹ�� O(1) ����ռ�����������

class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		auto it = nums.begin();
		while (it != nums.end())
		{
			if (*it == val)
			{
				it = nums.erase(it);
			}
			else
				++it;
		}
		return nums.size();
	}
};

//����һ�����������һ��Ŀ��ֵ�����������ҵ�Ŀ��ֵ�������������������Ŀ��ֵ�������������У�������
//���ᱻ��˳������λ��, ����Լ������������ظ�Ԫ��.

class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int i = 0;
		for (i = 0; i<nums.size(); i++)
		{
			if (nums[i] >= target)
				return i;
		}
		return i;
	}
};