#pragma once

#include<iostream>
using namespace std;
#include<string>

//�����Զ�������
struct TrueType
{};

// ��Ӧ�Զ�������
struct FalseType
{};

//��ʾʵ����
template<class T>
struct TypeTraits
{
	typedef FalseType PODTYPE;  // plain old data
};

//��ʾʵ����
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
template<>
struct TypeTraits<long>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<long long>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<float>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<double>
{
	typedef TrueType PODTYPE;
};

void TestCopy();