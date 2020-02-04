
//����һ���������飬����ҪѰ��һ�������������飬���������������������������ô�������鶼���Ϊ
//��������
class Solution {
public:
	int findUnsortedSubarray(vector<int>& nums) {
		vector<int> v = nums;
		sort(v.begin(), v.end());
		int i = 0, j = nums.size() - 1;
		for (i = 0; i<nums.size(); i++)
		{
			if (nums[i] != v[i])
				break;
		}
		if (i == nums.size())
			return 0;
		for (; j >= 0; j--)
		{
			if (nums[j] != v[j])
				break;
		}
		return j - i + 1;
	}
};

//�����沨����ʾ��������ʽ��ֵ����Ч����������� + , - , * , / ��ÿ��������������������Ҳ������
//��һ���沨�����ʽ
class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack <int> values;
		for (auto& str : tokens)
		{
			if (str == "*" || str == "/" || str == "+" || str == "-")
				resolve(values, str);
			else
				values.push(atoi(str.c_str())); //string to int
		}
		return values.top();
	}
	void resolve(stack <int>& num_stack, string operation)
	{
		int obj1, obj2;
		obj2 = num_stack.top();
		num_stack.pop();
		obj1 = num_stack.top();
		num_stack.pop();
		num_stack.push(calc(obj1, obj2, operation));
	}
	int calc(int obj1, int obj2, string operation)
	{
		switch (operation[0])
		{
		case '+':
			obj1 = obj1 + obj2;
			break;
		case '-':
			obj1 = obj1 - obj2;
			break;
		case '*':
			obj1 = obj1 * obj2;
			break;
		case '/':
			obj1 = obj1 / obj2;
			break;
		}
		return obj1;
	}
};