#include <iostream>
using namespace std;

#if 0
class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};

class Derived : public Base
{};

int main()
{
	// ������֤�������ཫ�����еĳ�Ա�����̳е�������
	cout << sizeof(Derived) << endl;

	// ��֤�������еĳ�Ա�����ͷű�����̳�
	Derived d;
	d.SetBase(10, 20, 30);
	d.PrintBase();
	return 0;
}
#endif

#if 0
// public�̳з�ʽ��

class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};

// �̳�Ȩ��--public
// ������public/protected�ĳ�Ա��������Ȩ�޲���
// ������private�ĳ�Ա�������в��ɼ�(������---�ó�Ա����ȷʵ�Ѿ��̳е�������)
class Derived : public Base
{
public:
	void SetDerived(int priD, int proD, int pubD)
	{
		_priD = priD;
		_proD = proD;
		_pubD = pubD;

		_pro = 10;
		// _pri = 20; // ���뱨�����������в��ܷ��ʻ�����˽�еĳ�Ա����
	}

	// ����Ȩ�ޣ��޶��ó�Ա�����Ƿ����ֱ����������е���
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void Test()
	{
		_pro = 10;
	}
};

int main()
{
	Derived d;
	cout << sizeof(d) << endl;

	d._pub = 10;
	// d._pro = 10;
	return 0;
}
#endif


#if 0
class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};


// �̳з�ʽ--protected
// ������public�ĳ�Ա�������з���Ȩ���Ѿ����protected
// ������protected�ĳ�Ա�������з���Ȩ�޲���
// ������private�ĳ�Ա�������в��ɼ�(������---�ó�Ա����ȷʵ�Ѿ��̳е�������)
class Derived : protected Base
{
public:
	void SetDerived(int priD, int proD, int pubD)
	{
		_priD = priD;
		_proD = proD;
		_pubD = pubD;

		_pro = 10;
		// _pri = 20; // ���뱨�����������в��ܷ��ʻ�����˽�еĳ�Ա����
	}

	// ����Ȩ�ޣ��޶��ó�Ա�����Ƿ����ֱ����������е���
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void Test()
	{
		_pub = 10;
		_pro = 20;
	}
};

int main()
{
	Derived d;
	// d._pub = 10;
	return 0;
}
#endif

#if 0
class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};


// �̳з�ʽ--private
// ������public�ĳ�Ա�������з���Ȩ���Ѿ����private
// ������protected�ĳ�Ա�������з���Ȩ���Ѿ����private
// ������private�ĳ�Ա�������в��ɼ�(������---�ó�Ա����ȷʵ�Ѿ��̳е�������)
class Derived : private Base
{
public:
	void SetDerived(int priD, int proD, int pubD)
	{
		_priD = priD;
		_proD = proD;
		_pubD = pubD;

		_pro = 10;
		// _pri = 20; // ���뱨�����������в��ܷ��ʻ�����˽�еĳ�Ա����
	}

	// ����Ȩ�ޣ��޶��ó�Ա�����Ƿ����ֱ����������е���
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void Test()
	{
		// _pub = 10;
		//_pro = 20;
	}
};

int main()
{
	Derived d;
	 d._pub = 10;
	return 0;
}
#endif


#if 0
class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};

 
// class �� struct��Ĭ�ϼ̳�Ȩ��
// classĬ�ϼ̳�Ȩ��---priavet
// structĬ�ϼ̳�Ȩ��---public
struct Derived : Base
{
public:
	void SetDerived(int priD, int proD, int pubD)
	{
		_priD = priD;
		_proD = proD;
		_pubD = pubD;

		_pro = 10;
		// _pri = 20; // ���뱨�����������в��ܷ��ʻ�����˽�еĳ�Ա����
	}

public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void Test()
	{
		_pub = 10;
	}
};

int main()
{
	D d;
	d._pub = 10;
	return 0;
}
#endif

#if 0
class B
{
public:
	void SetB(int b)
	{
		_b = b;
	}

protected:
	int _b;
};

class D : public B
{
public:
	void SetD(int b, int d)
	{
		_b = b;
		_d = d;
	}

//protected:
	int _d;
};

// ��ֵ���ݹ���ǰ��---->public
// �����public�̳з�ʽ����������������֮����--is-a�Ĺ�ϵ
// is-a: ��һ�������Խ�һ��������󿴳���һ���������
// �����õ���������λ�ö�����ʹ�����������д���
int main()
{
	B b;
	b.SetB(10);

	D d;
	//d.SetB(10);
	d.SetD(20, 30);

	// ��������������������������и�ֵ
	b = d;

	// һ������ָ�����ָ���������
	// һ�������ָ�벻��ֱ��ָ��һ������Ķ���
	B* pb = &d;

	D* pd = (D*)&b;
	pd->_d = 10;

	B& rb = d;
	//D& rd = b;

	// d = b;
	return 0;
}
#endif

#if 0
class B
{
public:
	void SetB(int b)
	{
		_b = b;
	}

	void Test(int a)
	{}

// protected:
	char _b;
};

// ͬ�����أ�������������о�����ͬ���Ƶĳ�Ա(��Ա���� || ��Ա����)
// ���ͨ�����������ֱ�ӷ���ͬ����Ա�����ȷ��ʵ������������Լ��ģ������
// ͬ����Ա����ֱ�ӷ��ʵ�(�����ཫ�����е�ͬ����Ա����)

// ��Ա����������������Ƿ���ͬ�޹�
// ��Ա���������Ա����ԭ���Ƿ���ͬ�޹�
class D : public B
{
public:
	void SetD(int b, int d)
	{
		_b = b;
	}

	void Test()
	{}

//protected:
	int _b;
};

int main()
{
	cout << sizeof(D) << endl;

	D d;
	d._b = '1';
	d.B::_b = '2';

	d.Test(10);
	d.B::Test(10);

	d.SetD(1, 2);
	return 0;
}
#endif

#if 0
// �������Ĺ��캯�����޲λ���ȫȱʡ�Ĺ��캯����
// �������๹�캯����ʼ���б��λ�õ��û򲻵��ö�����
// ����û�û�е��ã����������Ĭ�ϵ���
class B
{
public:
	B()
	{
		cout << "B()" << endl;
	}

protected:
	int _b;
};

class D : public B
{
public:
	D()
	{
		cout << "D()" << endl;
	}

protected:
	int _d;
};

int main()
{
	D d;
	return 0;
}
#endif

#if 0
class B
{
public:
	B(int b)
	{
		cout << "B()" << endl;
	}

protected:
	int _b;
};

// �������Ĺ��캯�����в����Ĺ��캯�����û�������
// �����๹�캯����ʼ���б��λ����ʽ���ã�����ɻ���
// ���ֳ�Ա�ĳ�ʼ��
class D : public B
{
public:
	D()
		: B(1)
		, _d(2)
	{
		cout << "D()" << endl;
	}

protected:
	int _d;
};

int main()
{
	D d;
	return 0;
}
#endif

class B
{
public:
	B(int b)
		: _b(b)
	{
		cout << "B()" << endl;
	}

	B(const B& b)
		: _b(b._b)
	{}

	B& operator=(const B& b)
	{
		if (this != &b)
		{
			_b = b._b;
		}

		return *this;
	}

protected:
	int _b;
};

// �������Ĺ��캯�����в����Ĺ��캯�����û�������
// �����๹�캯����ʼ���б��λ����ʽ���ã�����ɻ���
// ���ֳ�Ա�ĳ�ʼ��
class D : public B
{
public:
	D(int b, int d)
		: B(b)
		, _d(d)
	{
		cout << "D()" << endl;
	}

	D(const D& d)
		: B(d)
		, _d(d._d)
	{}

	D& operator=(const D& d)
	{
		if (this != &d)
		{
			//*this = d;
			B::operator=(d);
			_d = d._d;
		}

		return *this;
	}
protected:
	int _d;
};

int main()
{
	D d1(1, 2);
	D d2(d1);

	D d3(3, 4);
	d2 = d3;
	return 0;
}