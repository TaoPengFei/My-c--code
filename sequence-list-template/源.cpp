#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

#include <assert.h>

// ˳��� 

// typedef int DataType;

//��̬����˳���
template<class T>
class SeqList
{
public:
	SeqList(size_t capacity = 10)
		: _array(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}

	// β��
	void PushBack(const T& data);
	void PopBack()
	{
		--_size;
	}

	// ����λ�ò����ɾ��
	//void Insert(size_t pos, const T& data);
	//void Erase(size_t pos);

	// ��const���ͳ�Ա�����в����޸ĳ�Ա����
	// ����thisָ��
	size_t size()const
	{
		return _size;
	}

	size_t Capacity()const
	{
		return _capacity;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	T& operator[](size_t index)
	{
		assert(index < _size);
		return _array[index];
	}

	const T& operator[](size_t index)const
	{
		assert(index < _size);
		return _array[index];
	}

private:
	void _CheckCapacity()
	{
		if (_size == _capacity)
		{
			// �����¿ռ�
			T* array = new T[2 * _capacity];

			// ����Ԫ��
			// memcpy(array, _array, _size*sizeof(T));
			for (size_t i = 0; i < _size; ++i)
			{
				array[i] = _array[i];
			}

			// �ͷžɿռ�
			delete[] _array;
			_array = array;
			_capacity *= 2;
		}
	}
private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

template<class T>
void SeqList<T>::PushBack(const T& data)
{
	_CheckCapacity();
	_array[_size++] = data;
}


void TestSeqList()
{
	SeqList<int>  s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	cout << s1.size() << endl;
	cout << s1.Capacity() << endl;

	cout << s1[2] << endl;
	s1[2] = 10;
	cout << s1[2] << endl;

}

int main()
{
	TestSeqList();
	return 0;
}