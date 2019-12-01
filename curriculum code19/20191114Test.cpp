#include <iostream>
using namespace std;

/*
// C/C++
bool Test1()
{
	// �ɹ�����true��ʧ�ܷ���false
	return false;
}

void Test2()
{
	// ..

	// ����˴������Ƿ����
	throw 1;
}


// �������ԭ��ָ̬��(T*)������Դ�����������Դй©�ķ��վͱȽϴ�

void TestFunc()
{
	int* p = new int[10];
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		delete[] p;
		return;
	}

	// ...
	if (!Test1())
	{
		delete[] p;
		fclose(pf);
		return;
	}

	try
	{
		Test2();
	}
	catch (...)
	{
		delete[] p;
		fclose(pf);
		throw;
	}

	// ...

	delete[] p;
	fclose(pf);
}
*/

// �ܷ��ó������Ҹ�֪������������ʱ�Զ��ͷ���Դ

// RAII---��Դ��ȡ����ʼ��
//  �ڹ��캯���з���Դ
//  �������������ͷ���Դ


#if 0
// ����ָ��ļ�ģ��ʵ��
template<class T>
class SmartPtr
{
public:
	// RAII: ����--->�û����ÿ���ʲô�Ǹ��ͷ���Դ
	//              ���ͷ���Դ��ʵ�ʽ���������
	SmartPtr(T* ptr = nullptr)
		: _ptr(ptr)
	{
		cout << "SmartPtr(T*)" << endl;
	}

	~SmartPtr()
	{
		cout << "~SmartPtr()" << endl;

		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	// �ø���Ķ���߱�ָ��������Ϊ
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

struct A
{
	int a;
	int b;
	int c;
};

void TestSmartPtr()
{
	SmartPtr<int> sp1(new int);
	*sp1 = 10;
	// sp1

	SmartPtr<A> sp2(new A);
	sp2->a = 1;
	sp2->b = 2;
	sp2->c = 3;
}

int main()
{
	TestSmartPtr();
	return 0;
}
#endif

#if 0
// ȱ��: ǳ����
// ǰ��String-->����ǳ��������--->���
// ���ǵ�Ŀ�������Ե����飬�����ǰ���������
// ���ܲ�������ķ�ʽ���н��
template<class T>
class SmartPtr
{
public:
	// RAII: ����--->�û����ÿ���ʲô�Ǹ��ͷ���Դ
	//              ���ͷ���Դ��ʵ�ʽ���������
	SmartPtr(T* ptr = nullptr)
		: _ptr(ptr)
	{
		cout << "SmartPtr(T*)" << endl;
	}

	~SmartPtr()
	{
		cout << "~SmartPtr()" << endl;

		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	// �ø���Ķ���߱�ָ��������Ϊ
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

void TestSmartPtr()
{
	int a = 10;
	int* pa = &a;
	int* pb(pa);

	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2(sp1);  // ʹ��sp1��������sp2
}


int main()
{
	TestSmartPtr();
	return 0;
}
#endif

// ���в�ͬ���͵�����ָ�룺
// RAII: ��Դ�����Զ��ͷ�
// ��������ָ�����Ƶ���Ϊ��operator*()/operator->()
// ǳ�����Ľ����ʽ


#if 0
// c++98 ---- 
// auto_ptr
// ���ǳ������ʽ����Դת��--->��ǰ����
namespace ht
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~auto_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// ���ǳ����
		auto_ptr(auto_ptr<T>& ap)
			: _ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		// ap3 = ap2;
		auto_ptr<T>& operator=(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				// �����ǰ���������Դ�����ͷ�
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;  // ��Դת��
				ap._ptr = nullptr;  // ap����Դ�Ͽ���ϵ
			}

			return *this;
		}
	private:
		T* _ptr;
	};
}
#endif

#if 0
// ����bool _owner: ����ͷŶ���Դ���ͷŵ�Ȩ��
// �Ľ�֮���auto_ptr��ʵ��ԭ��:
// RAII + operator*()/operator->() + ���ǳ��������Դ����Ȩ��(����Դ�ͷŵ�Ȩ��)ת��
namespace ht
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _owner(false)
		{
			if (_ptr)
				_owner = true;
		}

		~auto_ptr()
		{
			if (_ptr && _owner)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// ���ǳ����
		auto_ptr(const auto_ptr<T>& ap)
			: _ptr(ap._ptr)
			, _owner(ap._owner)
		{
			ap._owner = false;
		}

		// ap3 = ap2;
		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				// �����ǰ���������Դ�����ͷ�
				if (_ptr && _owner)
					delete _ptr;

				_ptr = ap._ptr;  // ��Դת��
				_owner = ap._owner;
				ap._owner = false;  // ap�����ͷ�Ȩ��--->ת�Ƹ�this
			}

			return *this;
		}
	private:
		T* _ptr;
		mutable bool _owner;
	};
}


void TestAutoPtr1()
{
	int a = 10;
	int* pa = &a;
	int* pb = pa;

	*pa = 100;
	*pb = 200;

	ht::auto_ptr<int> ap1(new int);
	ht::auto_ptr<int> ap2(ap1);

	// ��Դת�Ƶ�ȱ�ݣ� ap1�Ѻ���Դ�Ͽ���ϵ�������ٲ�����Դ
	*ap2 = 200;
	*ap1 = 100;

	ht::auto_ptr<int> ap3(new int);
	ap3 = ap2;
}

// ��_owner�汾��auto_ptrȱ�ݣ����ܻ����Ұָ��--�����´������
void TestAutoPtr2()
{
	ht::auto_ptr<int> ap1(new int);

	if (true)
	{
		ht::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}

	// ap1��Ұָ��
	*ap1 = 10;
}

int main()
{
	// TestAutoPtr1();

	TestAutoPtr2();
	return 0;
}

#endif


#if 0

// ���飺ʲô����¶���Ҫʹ��auto_ptr

#include <memory>


int main()
{
	auto_ptr<int> ap1(new int);
	auto_ptr<int> ap2(ap1);
	return 0;
}
#endif

// C++11: auto_ptr--->��������Դת��ʵ�ֵ�
// �ṩ�����׵�����ָ��

// ����ָ��ԭ��RAII(�Զ��ͷ���Դ) + operator*()/operator->()(����ָ��������Ϊ) + �ṩ���ǳ������ʽ

// ǳ��������ԭ��Ĭ�Ͽ������캯�� �� Ĭ�ϵĸ�ֵ���������

// unique_ptr

#if 0
#include <memory>

int main()
{
	unique_ptr<int> up1(new int);
	//unique_ptr<int> up2(up1);

	unique_ptr<int> up3(new int);
	// up3 = up1;

	return 0;
}
#endif


#if 0
// ���ǳ������ʽ����Դ��ռ(ֻ��һ������ʹ�ã����ܹ���)--->ʵ�֣���ֹ���ÿ�������͸�ֵ���������
namespace ht
{
	template<class T>
	class unique_ptr
	{
	public:
		// RAII
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				delete _ptr; // �ͷ���Դ�ķ�ʽ�̶����ˣ�ֻ�ܹ���new����Դ�����ܴ����������͵���Դ
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// ���ǳ��������ֹ���ÿ������캯���͸�ֵ���������

		// C++98:
		/*
	private:  // ���������Ȩ��һ��Ҫ���ó�private��ԭ��Ϊ�˷�ֹ�û��Լ������ⶨ��
		unique_ptr(const unique_ptr<T>& up);
		unique_ptr<T>& operator=(const unique_ptr<T>&);
		*/

		// C++11 ��ֹ���ÿ�������͸�ֵ���������
		unique_ptr(const unique_ptr<T>&) = delete;  // 1. �ͷ�new�Ŀռ�  2.Ĭ�ϳ�Ա���� = delete �� ���߱�������ɾ����Ĭ�ϳ�Ա����
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
	private:
		T* _ptr;
	};

	// �û����ⲿʵ��
// 	template<class T>
// 	unique_ptr<T>::unique_ptr(const unique_ptr<T>& up)
// 	{}
}




void TestUniquePtr()
{
	ht::unique_ptr<int> up1(new int);
	ht::unique_ptr<int> up2(up1);

	ht::unique_ptr<int> up3(new int);
	//up3 = up1;
}
#endif

#if 0
#include <memory>
#include <malloc.h>

int main()
{
	unique_ptr<int> up1(new int);
	unique_ptr<int> up2((int*)malloc(sizeof(int)));
	return 0;
}
#endif


#if 0
template<class T>
class DFDef
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

template<class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = nullptr;
		}
	}
};


class FClose
{
public:
	void operator()(FILE*& p)
	{
		if (p)
		{
			fclose(p);
			p = nullptr;
		}
	}
};

namespace ht
{
	template<class T, class DF = DFDef<T>>
	class unique_ptr
	{
	public:
		// RAII
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				//delete _ptr; // �ͷ���Դ�ķ�ʽ�̶����ˣ�ֻ�ܹ���new����Դ�����ܴ����������͵���Դ
				//DF()(_ptr);
				DF df;
				df(_ptr);
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		unique_ptr(const unique_ptr<T>&) = delete;  // 1. �ͷ�new�Ŀռ�  2.Ĭ�ϳ�Ա���� = delete �� ���߱�������ɾ����Ĭ�ϳ�Ա����
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

	private:
		T* _ptr;
	};
}

void TestUniquePtr()
{
	ht::unique_ptr<int> up1(new int);
	ht::unique_ptr<int, Free<int>> up2((int*)malloc(sizeof(int)));
	ht::unique_ptr<FILE, FClose> up3(fopen("1.txt", "w"));
}

int main()
{
	TestUniquePtr();
	return 0;
}
#endif

#if 0
// 1 
// 2
namespace ht
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
		{
			if (_ptr)
				_pCount = new int(1);
		}

		~shared_ptr()
		{
			if (_ptr && 0 == --*_pCount)
			{
				delete _ptr;
				delete _pCount;
			}
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++*_pCount;
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 1. �����Դ�Ͽ���ϵ
				// this���ڲ������Լ�����Դ��Ҫ��sp��������Դ
				if (_ptr && 0 == --*_pCount)
				{
					// ��ǰ���������һ��ʹ����Դ�Ķ���
					delete _ptr;
					delete _pCount;
				}

				// 2. ��sp������Դ������
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					++*_pCount;

			}

			return *this;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		T* _ptr;
		int* _pCount;
	};
}


void TestShradPtr()
{
	ht::shared_ptr<int> sp1(new int);
	cout << sp1.use_count() << endl;

	ht::shared_ptr<int> sp2(sp1);
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;


	ht::shared_ptr<int> sp3(new int);
	cout << sp3.use_count() << endl;

	ht::shared_ptr<int> sp4(sp3);
	cout << sp3.use_count() << endl;
	cout << sp4.use_count() << endl;

	sp3 = sp2;
	cout << sp2.use_count() << endl;
	cout << sp3.use_count() << endl;

	sp4 = sp2;
	cout << sp2.use_count() << endl;
	cout << sp4.use_count() << endl;
}


int main()
{
	TestShradPtr();
	return 0;
}
#endif


#if 0
// ����ɾ���������û����Կ�����Դ������ͷŲ���
// �����̰߳�ȫ��

// ���̣���˾
// �̣߳�Ա��
#include <mutex>

template<class T>
class DFDef
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
};

namespace ht
{
	template<class T, class DF = DFDef<T>>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
			, _pMutex(nullptr)
		{
			if (_ptr)
			{
				_pCount = new int(1);
				_pMutex = new mutex;
			}
				
		}

		~shared_ptr()
		{
			Release();
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			AddRef();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 1. �����Դ�Ͽ���ϵ
				// this���ڲ������Լ�����Դ��Ҫ��sp��������Դ
				Release();

				// 2. ��sp������Դ������
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					AddRef();
			}

			return *this;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void AddRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // ����
				++*_pCount;
				_pMutex->unlock();// ����
			}
		}

		int SubRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // ����
				--*_pCount;
				_pMutex->unlock();// ����
			}

			return *_pCount;
		}

		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				// ��ǰ���������һ��ʹ����Դ�Ķ���
				DF()(_ptr);
				delete _pCount;
			}
		}

	private:
		T* _ptr;
		int* _pCount;
		mutex* _pMutex;
	};
}

struct Date
{
	Date()
	{
		_year = _month = _day = 0;
	}

	int _year;
	int _month;
	int _day;
};

// 1. shared_ptr�����ü����Ƿ�ȫ---mutex
// 2. shared_ptr��������û������Ƿ����̰߳�ȫ
void SharePtrFunc(ht::shared_ptr<Date>& sp, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		ht::shared_ptr<Date> copy(sp);

		copy->_year++;
		copy->_month++;
		copy->_day++;
	}
}

#include <thread>

int main()
{
	ht::shared_ptr<Date> sp(new Date);

	thread t1(SharePtrFunc, sp, 100000);
	thread t2(SharePtrFunc, sp, 100000);

	t1.join();
	t2.join();
	return 0;
}
#endif


#if 0
#include <memory>

// struct ListNode
// {
// 	ListNode* _pPre;
// 	ListNode* _pNext;
// 	int _data;
// };

struct ListNode
{
	ListNode(int data = 0)
	: pre(nullptr)
	, next(nullptr)
	, _data(data)
	{
		cout << "ListNode(int):" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode():" << this << endl;
	}

	shared_ptr<ListNode> pre;
	shared_ptr<ListNode> next;
	int _data;
};

void TestListNode()
{
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->pre = sp1;

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}

int main()
{
	TestListNode();
	return 0;
}
#endif

#if 0
#include <memory>

// struct ListNode
// {
// 	ListNode* _pPre;
// 	ListNode* _pNext;
// 	int _data;
// };

struct ListNode
{
	ListNode(int data = 0)
// 	: pre(nullptr)
// 	, next(nullptr)
	: _data(data)
	{
		cout << "ListNode(int):" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode():" << this << endl;
	}

	//shared_ptr<ListNode> pre;
	//shared_ptr<ListNode> next;

	weak_ptr<ListNode> pre;
	weak_ptr<ListNode> next;

	int _data;
};

void TestListNode()
{
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->pre = sp1;

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}

int main()
{
	// weak_ptr<int> sp1;  // ���Ա���ɹ�
	//weak_ptr<int> sp2(new int);   // ����ʧ��--ԭ��weak_ptr���ܶ���������Դ
	TestListNode();
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10;
	double d = 12.34;
	a = d;   // ��ʽ����ת��

	int* pa = &a;

	pa = (int*)&d; // ��ʽ����ת��
	cout << &d << endl;
	cout << pa << endl;

	const int c = 10;
	int* pc = (int*)&c;   // const int* 
	return 0;
}
#endif

#if 0
class B
{
public:
	int _b;
};

class D : public B
{
public:
	int _d;
};

int main()
{
	B b;
	D d;

	D* pd = (D*)&b;
	pd->_d = 10;
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10;
	double d = 12.34;

	a = static_cast<int>(d);  // ��ʽ����ת��

	int* pa = reinterpret_cast<int*>(&d);

	const int c = 10;
	int* pc = const_cast<int*>(&c);  // const int*
	return 0;
}
#endif

#if 0
class A
{
public:
	virtual void f(){}
};


class B : public A
{};


// �ӻ���--->����--->����ת��--->����ȫ��
// ������--->����--->����ת��--->��ȫ
void fun(A* pa)
{
	// dynamic_cast���ȼ���Ƿ���ת���ɹ����ܳɹ���ת���������򷵻�
	B* pb1 = static_cast<B*>(pa);
	B* pb2 = dynamic_cast<B*>(pa);
	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}


int main()
{
	A a;
	B b;
	fun(&a);
	fun(&b);

	return 0;
}
#endif

#include <iostream>
using namespace std;
#include <mutex>

template<class T>
class DFDef
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
};

namespace ht
{
	template<class T, class DF = DFDef<T>>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
			, _pMutex(nullptr)
		{
			if (_ptr)
			{
				_pCount = new int(1);
				_pMutex = new mutex;
			}

		}

		~shared_ptr()
		{
			Release();
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			AddRef();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 1. �����Դ�Ͽ���ϵ
				// this���ڲ������Լ�����Դ��Ҫ��sp��������Դ
				Release();

				// 2. ��sp������Դ������
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					AddRef();
			}

			return *this;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void AddRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // ����
				++*_pCount;
				_pMutex->unlock();// ����
			}
		}

		int SubRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // ����
				--*_pCount;
				_pMutex->unlock();// ����
			}

			return *_pCount;
		}

		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				// ��ǰ���������һ��ʹ����Դ�Ķ���
				DF()(_ptr);
				delete _pCount;
			}
		}

	private:
		T* _ptr;
		int* _pCount;
		mutex* _pMutex;
	};
}

struct Date
{
	Date()
	{
		_year = _month = _day = 0;
	}

	int _year;
	int _month;
	int _day;
};

// 1. shared_ptr�����ü����Ƿ�ȫ---mutex
// 2. shared_ptr��������û������Ƿ����̰߳�ȫ
void SharePtrFunc(ht::shared_ptr<Date>& sp, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		ht::shared_ptr<Date> copy(sp);

		copy->_year++;
		copy->_month++;
		copy->_day++;
	}
}

#include <thread>

int main()
{
	ht::shared_ptr<Date> sp(new Date);

	thread t1(SharePtrFunc, sp, 100000);
	thread t2(SharePtrFunc, sp, 100000);

	t1.join();
	t2.join();
	return 0;
}
