#include <iostream>
using namespace std;

#if 0
// ������ģ�����
// C++11: array

namespace bite
{
	template<class T, size_t N>
	class array
	{
	public:
		void push_back(const T& data)
		{
			// N = 10;
			_array[_size++] = data;
		}

		T& operator[](size_t index)
		{
			assert(index < _size);
			return _array[index];
		}

		bool empty()const
		{
			return 0 == _size;
		}

		size_t size()const
		{
			return _size;
		}
	private:
		T _array[N];
		size_t _size;
	};
}



int main()
{
	int a = 10;
	int b = 20;

	// ������ģ����������ڱ�����ȷ������
	//bite::array<int, a+b> arr;
	bite::array<int, 10+20> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	return 0;
}
#endif

#if 0
template<class T>
T& Max(T& left, T& right)
{
	return left > right? left : right;
}

// ����ģ����ػ�
// template<>
// char*& Max<char*>(char*& left, char*& right)
// {
// 	if (strcmp(left, right) > 0)
// 		return left;
// 
// 	return right;
// }

// ����ģ��һ�㲻��Ҫ�ػ���ֱ�ӽ����ܴ������͵ľ��庯������
char* Max(char* left, char* right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}

class Date
{
public:
	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator>(const Date& d)const
	{
		return _day > d._day;
	}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "/" << d._month << "/" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	int a = 10;
	int b = 20;

	cout << Max(a, b) << endl;  //Max<int>
	cout << Max(b, a) << endl;

	Date d1(2019, 10, 22);
	Date d2(2019, 10, 23);

	cout << Max(d1, d2) << endl;
	cout << Max(d2, d1) << endl;

	char* p1 = "world";
	char* p2 = "hello";
	cout << Max(p1, p2) << endl;
	cout << Max(p2, p1) << endl;
	return 0;
}
#endif

#if 0
template<class T>
const T& Max(const T& left, const T& right)
{
	return left > right ? left : right;
}

template<>
const char*& Max<const char*&>(const char*& left, const char*& right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}


int main()
{
	int a = 10;
	int b = 20;

	Max(a, b);
	Max(10, 20);

	char* p1 = "world";
	char* p2 = "hello";
	cout << Max(p1, p2) << endl;
	cout << Max(p2, p1) << endl;
	return 0;
}
#endif

#if 0
template<class T>
void Test(const T& p) // const int*& p<---���� int*& const p
{
	*p = 100;

	int b = 20;
	p = &b;
}

int main()
{
	int a = 10;
	int* pa = &a;

	const int b1 = 10;
	int const b2 = 20;

	Test(pa); // int*
	return 0;
}
#endif

#if 0
template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};


// ȫ�ػ�---���������Ͳ��������ػ�
template<>
class Data<int, int>
{
public:
	Data() 
	{
		cout << "Data<int, int>" << endl; 
	}
private:
	int _d1;
	int _d2;
};


int main()
{
	Data<int, double> d1;
	Data<int, int> d2;
	return 0;
}
#endif

#if 0
template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};


// ƫ�ػ��������ػ�--->��ģ������б��в��ֲ������ͻ�
template<class T1>
class Data<T1, int>
{
public:
	Data() 
	{
		cout << "Data<T1, int>" << endl; 
	}

private:
	T1 _d1;
	int _d2;
};


int main()
{
	Data<int, double> d1;
	Data<int, int> d2;
	Data<double, int> d3;
	return 0;
}
#endif

#if 0
template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

// ƫ�ػ�����ģ������б��е��������Ƹ����ϸ�
template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data() 
	{ 
		cout << "Data<T1*, T2*>" << endl; 
	}
private:
	T1* _d1;
	T2* _d2;
};


int main()
{
	Data<int*, int> d1;
	Data<int, int*> d2;
	Data<int*, int*> d3;
	Data<int*, double*> d4;
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}


	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;
		}

		return *this;
	}

	~String()
	{
		delete[] _str;
	}

private:
	char* _str;
};

// дһ��ͨ�õĿ���������Ҫ��Ч�ʾ����ܸ�
// ������������-->O(1)
// ȱ�ݣ�ǳ����
template<class T>
void Copy1(T* dst, T* src, size_t size)
{
	memcpy(dst, src, sizeof(T)*size);
}

// �ŵ㣺һ���������
// ȱ�ݣ�O(N)
template<class T>
void Copy2(T* dst, T* src, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		dst[i] = src[i];
}


bool IsPODType(const char* strType)
{
	// �˴����Խ����е���������ö�ٳ���
	const char* strTypes[] = { "char", "short", "int", "long", "long long", "float", "double" };
	for (auto e : strTypes)
	{
		if (strcmp(strType, e) == 0)
			return true;
	}

	return false;
}

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	// ͨ��typeid���Խ�T��ʵ�����Ͱ����ַ����ķ�ʽ����
	if (IsPODType(typeid(T).name()))
	{
		// T�����ͣ���������
		memcpy(dst, src, sizeof(T)*size);
	}
	else
	{
		// T�����ͣ��Զ�������---ԭ���Զ��������п��ܻ����ǳ����
		for (size_t i = 0; i < size; ++i)
			dst[i] = src[i];
	}
}


void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);

	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];
	Copy(s2, s1, 3);
}

int main()
{
	TestCopy();
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}


	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;
		}

		return *this;
	}

	~String()
	{
		delete[] _str;
	}

private:
	char* _str;
};


// ȷ��T�����Ƿ�Ϊ�������ͣ�
// ��
// ����
// ��Ӧ��������
struct TrueType
{
	static bool Get()
	{
		return true;
	}
};

// ��Ӧ�Զ�������
struct FalseType
{
	static bool Get()
	{
		return false;
	}
};

template<class T>
struct TypeTraits
{
	typedef FalseType PODTYPE;  // plain old data
};


template<>
struct TypeTraits<char>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<short>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType PODTYPE;
};

// ...

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	// ͨ��typeid���Խ�T��ʵ�����Ͱ����ַ����ķ�ʽ����
	if (TypeTraits<T>::PODTYPE::Get())
	{
		// T�����ͣ���������
		memcpy(dst, src, sizeof(T)*size);
	}
	else
	{
		// T�����ͣ��Զ�������---ԭ���Զ��������п��ܻ����ǳ����
		for (size_t i = 0; i < size; ++i)
			dst[i] = src[i];
	}
}


void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);

	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];
	Copy(s2, s1, 3);
}

int main()
{
	TestCopy();
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}


	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;
		}

		return *this;
	}

	~String()
	{
		delete[] _str;
	}

private:
	char* _str;
};


// ȷ��T�����Ƿ�Ϊ�������ͣ�
// ��
// ����
// ��Ӧ��������
struct TrueType
{};

// ��Ӧ�Զ�������
struct FalseType
{};

template<class T>
struct TypeTraits
{
	typedef FalseType PODTYPE;  // plain old data
};


template<>
struct TypeTraits<char>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<short>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType PODTYPE;
};

// ...

template<class T>
void Copy(T* dst, T* src, size_t size, TrueType)
{
	// T�����ͣ���������
	memcpy(dst, src, sizeof(T)*size);
}

template<class T>
void Copy(T* dst, T* src, size_t size, FalseType)
{
	// T�����ͣ��Զ�������---ԭ���Զ��������п��ܻ����ǳ����
	for (size_t i = 0; i < size; ++i)
		dst[i] = src[i];
}

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	Copy(dst, src, size, TypeTraits<T>::PODTYPE());
}


void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);

	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];
	Copy(s2, s1, 3);
}

int main()
{
	TestCopy();
	return 0;
}
#endif

#include "aaa.h"
// 15  

//int Add(int left, int right);
/*
template<class T>
T Sub(const T& left, const T& right);
*/

#if 0
// 7:50  
#include "aaa.hpp"

int main()
{
	//Add(10, 20);
	Sub(10, 20);
	Sub(10.0, 20.0);
	return 0;
}
#endif

#if 0
int main()
{
	printf("%d, %d", "hello", 12.34);
	int a = 0;
	scanf("%d", &a);
	return 0;
}
#endif

#if 0
#include <string>

int main()
{
	cerr << "error1";
	cerr << "error2" << endl;

	clog << "2019-10-27";
	clog << "2019-10-27"<<endl;

	int a;
	double b;
	string s;

	cin >> a;
	cin >> b >> s;

	cout << a << endl;
	cout << b << " " << s << endl;

	// IO�����㷨
	// ѭ������
	// ���н��� while(getline(cin, s)){}
	// while(cin>>a>>b>>c)
	// {}
	// while(cin>>s)
	return 0;
}
#endif

#if 0
int main()
{
	char c;
	//cin >> c;
	c = getchar();
	return 0;
}
#endif

#include <fstream>


// ʹ���ļ�IO�����ı��������Ʒ�ʽ��ʾ��д�����ļ�
struct ServerInfo
{
	char _ip[32]; // ip
	int _port; // �˿�
};


struct ConfigManager
{
public:
	ConfigManager(const char* configfile = "bitserver.config")
		:_configfile(configfile)
	{}

	void WriteBin(const ServerInfo& info)
	{
		// ����ע��ʹ�ö����Ʒ�ʽ��д
		ofstream ofs(_configfile, ifstream::out | ifstream::binary);
		ofs.write((const char*)&info, sizeof(ServerInfo));
		ofs.close();
	}

	void ReadBin(ServerInfo& info)
	{
		// ����ע��ʹ�ö����Ʒ�ʽ�򿪶�
		ifstream ifs(_configfile, ifstream::in | ifstream::binary);
		ifs.read((char*)&info, sizeof(ServerInfo));
		ifs.close();
	}

	void WriteText(const ServerInfo& info)
	{
		// ����ᷢ��IO��д���α�C�������׾ͼ򵥶��ˣ�
		// C ���Ե��Ȱ�����itoa��д
		ofstream ofs(_configfile);
		ofs << info._ip << endl;
		ofs << info._port << endl;
		ofs.close();
	}

	void ReadText(ServerInfo& info)
	{
		// ����ᷢ��IO�������α�C�������׾ͼ򵥶��ˣ�
		// C ���Ե��ȶ��ַ�������atoi
		ifstream ifs(_configfile);
		ifs >> info._ip;
		ifs >> info._port;
		ifs.close();
	}

private:
	string _configfile; // �����ļ�
};

int main()
{
	ConfigManager cfgMgr;
	ServerInfo wtinfo;
	ServerInfo rdinfo;
	strcpy(wtinfo._ip, "127.0.0.1");
	wtinfo._port = 80;
	// �����ƶ�д
	cfgMgr.WriteBin(wtinfo);
	cfgMgr.ReadBin(rdinfo);
	cout << rdinfo._ip << endl;
	cout << rdinfo._port << endl;
	// �ı���д
	cfgMgr.WriteText(wtinfo);
	cfgMgr.ReadText(rdinfo);
	cout << rdinfo._ip << endl;
	cout << rdinfo._port << endl;
	return 0;
}