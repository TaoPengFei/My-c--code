#include <iostream>
using namespace std;

#include <string>

#if 0
// �麯��һ���ǳ�Ա��������Ա������һ��ȫ����������Ϊ�麯��
// ��֤��������Щ����������Ϊ�麯��
class Base
{
public:
	// ���캯��������Ϊ�麯��
	// һ��������������麯��������Ĺ��캯�����ã�
	// 1. ��ʼ�����еĳ�Ա����---->���û�
	// 2. �����ָ����ڶ����ǰ4���ֽ�---->���������

	// ���裺���캯��������Ϊ�麯������������ + �麯������
	// ���캯���������Ѿ����麯��--->һ�������߱���
	// ��������--->Ҫ���ù��캯��
	// ���캯������---->��Ҫͨ�����--->�Ӷ���ǰ4���ֽ��л�ȡ����ַ-
	// Ҫ�Ӷ���ǰ4���ֽ��������--->�ҹ��캯��--->����Ϳ��Դ�������:�������ָ����ڶ����ǰ4���ֽ���
	virtual Base()
	{}

	//virtual inline void Test1()
	//{}

	// ��̬��Ա����������Ϊ�麯��
	// ԭ�򣺾�̬��Ա����û��thisָ�룬���Բ�ͬͨ���������
	// �����̬��Ա����������Ϊ�麯��������ͨ�������ã�
	// ����̬��Ա����û��thisָ�룬���Բ�ͨ��������ã������޷��ҵ�
	// ��̬��Ա�������޷��ҵ�--->���ܵ���
	//virtual static void Test2()
	//{}
};

void TestVirtual(Base* pb)
{
	// �����Ѿ�����������--->�����������һ��������Ϊ������������
	// �ڱ���׶Σ��Ὣ�ú���չ��
	// ���չ�������Ȳ�Ҫͨ�������ã��Ͳ���ʵ�ֶ�̬
	// ���ۣ���������������Ϊ�麯��
	pb->Test1();
	//pb->Test2();
	//Base::Test2();
}
#endif


#if 0
// ��������---������Ϊ�麯��---->��д��һ������
// ������������漰����̬��Դ����(���磺����Ӷ�������ռ�)�����飺�������������������ó��麯����������ܾͻ�����ڴ�й©)
class Base
{
public:
	Base(int b)
		: _b(b)
	{
		cout << "Base::Base(int)" << endl;
	}

	virtual ~Base()
	{
		cout << "Base::~Base()" << endl;
	}

	int _b;
};

class Derived : public Base
{
public:
	Derived(int b)
		: Base(b)
	{
		_p = new int[10];
	}

	~Derived()
	{
		delete[] _p;
	}
private:
	int* _p;
};

int main()
{
	// ��̬���ͣ���������ʱ������---->�ڱ����ڼ�������
	// ��̬���ͣ�ʵ������(ָ��)������---->������ʱȷ�������Ǹ�����麯��
	Base* pb = new Derived(10);
	delete pb;
	// delete: 1. �������������ͷŶ����е���Դ
	//         2. ����void operator delete(void* p)�ͷŶ���Ŀռ�

	return 0;
}
#endif



#if 0
class B
{
public:
	virtual void Test()
	{}
};

int g_a = 10;
int main()
{
	const char* p = "hello world";

	printf("ȫ�ֱ���: %p \n", &g_a);
	printf("����: %p \n", p);

	B b;
	printf("���: %p \n", *(int*)&b);

	// �Ӵ�ӡ����п���������ַ���볣����ַ�ǳ���---->���Ӧ���ڴ����
	return 0;
}
#endif


#if 0
class A
{
public:
	A(int a)
		: _a(a)
	{}

	void SetA(int a)
	{
		_a = a;
	}

	int GetA()
	{
		return _a;
	}
protected:
	int _a;
};


// B �� A�Ĺ�ϵ��is-a
class B : public A
{
public:
	B(int a, int b)
		: A(a)
		, _b(b)
	{}

	void SetB(int b)
	{
		_b = b;
	}

	int GetB()
	{
		return _b;
	}
protected:
	int _b;
};


// ��ϣ�C���а�����һ��A��Ķ���   has-a
class C
{
public:
	C(int a, int c)
		: _a(a)
		, _c(c)
	{}

	void SetA(int a)
	{
		_a.SetA(a);
	}

	void SetC(int c)
	{
		_c = c;
	}

	int GetC()
	{
		return _c;
	}

private:
	A _a;
	int _c;
};


int main()
{
	B b(1,2);
	b.SetA(10);

	C c(1, 2);
	c.SetA(10);
	return 0;
}
#endif


#if 0
class Base1 
{
public:
	int _b1;
};

class Base2 
{
public:
	int _b2;
};

class Derive : public Base1, public Base2 
{
public:
	int _d;
};


int main()
{
	// A. p1 == p2 == p3
	// B. p1 < p2 < p3
	// C. p1 == p3 != p2
	// D. p1 != p2 != p3

	Derive d;
	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;
	return 0;
}
#endif


#if 0
// �Ƚϱ��������Ǻ��Ѻ�
int Div(int left, int right)
{
	if (0 == right)
		exit(0);

	return left / right;
}
#endif

#if 0
#include <windows.h>

void Test()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		// ��ȡ�����������Ĵ�����(��windows����ϵͳά����)
		int errNo = GetLastError();
		cout << errNo << endl;

		return;
	}

	// ....
	fclose(pf);
}

int main()
{
	Test();
	//Test1();
	return 0;
}
#endif

#if 0
void Test()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		// ��ȡ�����������Ĵ�����(��windows����ϵͳά����)
		int errNo = GetLastError();
		cout << errNo << endl;

		goto L;
	}

	// ....
	fclose(pf);

	L:
}
#endif


#if 0
int main()
{
    https://www.baidu.com;

	return 0;
}
#endif

#if 0
#include <malloc.h>

#include <setjmp.h>

// ��ȫ�ֱ����н����������longjmp��������תλ��
jmp_buf buff;  // ��setjmp������buff����ת��Ϣ

void Test1()
{
	char* p = (char*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		// һ������ռ�ʧ��ʱ��longjmp����ת��buffָ����λ��
		longjmp(buff, 1);
	}

	///��������
}

void Test2()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		longjmp(buff, 2);
	}

	// ....
	fclose(pf);
}

int main()
{
	// setjmp����longjmp��������ת��
	// ע�⣺setjmp���״ε���ʱ��һ���᷵��0
	int iState = 0;//setjmp(buff);
	if (0 == iState)
	{
		// ��������
		Test1();
		Test2();
	}
	else
	{
		// ���������Ƿ������longjmp��ת����λ��
		// һ�������д���ǳ���Ĵ��������
		switch (iState)
		{
		case 1:
			cout << "malloc����ռ�ʧ��" << endl;
			break;
		case 2:
			cout << "���ļ�ʧ��" << endl;
			break;
		default:
			cout << "δ֪����" << endl;
		}
	}

	iState = setjmp(buff);
	return 0;
}
#endif


#if 0
void Test1()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}

	// ...
	// ���г�����ļ�����

	fclose(pf);
}


void Test2()
{
	char* p = (char*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw 1.0;
	}

	///��������
	free(p);
}


int main()
{
	int a = 10;
	double d = 12.34;
	a = d; // double��int֮����Է�����ʽ����ת��

	// �쳣�����ǰ������������в����
	// ����֮��������ᷢ������ת��
	try
	{
		Test2();
		Test1();
	}
	catch (int e)
	{
		// ��������int���͵��쳣
		// ����������
		cout << e << endl;
	}
	catch (double e)
	{
		cout << e << endl;
	}
	//...
	return 0;
}
#endif


#if 0
void Test1()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
		throw 1;

	// ...
	fclose(pf);
}


void Test2()
{
	int* p = new int[10];

	// ...
	try
	{
		Test1();
	}
	catch (int e)
	{
		delete[] p;
		cout << e << endl;
		return;
	}
	

	// ...
	delete[] p;
}

int main()
{
	try
	{
		Test2();
		Test1();
	}
	catch (int e)
	{
		cout << e << endl;
	}

	return 0;
}
#endif

#if 0
void Test()
{
	int a = 10;
	cout << &a << endl;

	// �����쳣ʱ�������ǽ�a�����׳��������׳���һ��a�ĸ���
	throw a;
}

int main()
{
	try
	{
		Test();
	}
	catch (int& ra)
	{
		cout << &ra << endl;
	}
	return 0;
}
#endif


#if 0
class A
{
public:
	A()
	{
		cout << "A::A()" <<this<< endl;
	}

	A(const A& a)
	{
		cout << "AA::(const A&):" << this << endl;
	}

	~A()
	{
		cout << "A::~A()" <<this<< endl;
	}
};
void Test()
{
	A  a;
	cout << &a << endl;

	// �����쳣ʱ�������ǽ�a�����׳��������׳���һ��a�ĸ���
	throw a;  // ʵ���׵���a�ĸ���
}

int main()
{
	try
	{
		Test();
	}
// 	catch (A& ra)
// 	{
// 		cout << &ra << endl;
// 	}
	catch (...) // ���ܲ��񣬼����������͵��쳣�����Բ���catch(...)�ķ�ʽ���в���
	{
		cout << "A" << endl;
	}
	return 0;
}
#endif

#if 0
void Test1()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
		throw 1;

	// ...
	fclose(pf);
}


void Test2()
{
	int* p = new int[10];

	// ...
	try
	{
		Test1();
	}
	catch (...)
	{
		// 1. ����Test2���ڸ�����֪��Test1�׳��쳣������
		// 2. ����Test2֪��Test1���׳��쳣�����ͣ�����Test2û�б�Ҫ����Ҫ���Test1�׳����쳣
		delete[] p;
		throw;   // �쳣�������׳�
	}

	// ...
	delete[] p;
}

int main()
{
	try
	{
		Test2();
	}
	catch (int e)
	{
		cout << e << endl;
	}
	
	return 0;
}
#endif

#if 0
void Test()
{
	throw 1;
}


template<class T>
void Test2(T a)
{
	throw a;
}

template<class T>
void Test3(T a)
{
	try
	{
		Test2(a);
	}
	catch (T a)
	{
		cout << a << endl;
	}
}

int main()
{
	Test3(10);
	return 0;
}
#endif

#if 0
// ������쳣��ֻ���׳����ε��쳣
// �����ڱ����ڼ�ͻᱨ��
void Test1()throw(int)
{
	throw 1.0;
}

// �ú���һ�������׳��쳣
// �����ڱ����ڼ�ͻᱨ��
void Test2()throw()
{
	throw 1;
}

int main()
{
	return 0;
}
#endif

class Exception
{
public:
	Exception(const string& errInfo, int errNo)
		: _errInfo(errInfo)
		, _errNo(errNo)
	{}

	virtual void What() = 0;

protected:
	string _errInfo;
	int _errNo;
};

class NetException : public Exception
{
public:
	NetException(const string& errInfo, int errNo)
		: Exception(errInfo, errNo)
	{}

	virtual void What()
	{
		cout << _errInfo << ":" << _errNo << endl;
	}
};


// 
class DBException : public Exception
{
public:
	DBException(const string& errInfo, int errNo)
		: Exception(errInfo, errNo)
	{}

	virtual void What()
	{
		cout << _errInfo << ":" << _errNo << endl;
	}
};

// ͨ�����紫������
void Test1()
{
	NetException e("�����ж�", 400);
	throw e;
}

// �������ݿ�
void Test2()
{
	DBException e("���ݿ�δ��", 500);
}

int main()
{
	try
	{
		char* p = new char[0x7fffffff];

		Test1();
		Test2();
		
	}
	catch (Exception& e)
	{
		e.What();
	}
	catch (exception& e)
	{
		e.what();
	}
	catch (...)
	{
		cout << "δ֪�쳣" << endl;
	}
	
	return 0;
}