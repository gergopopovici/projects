#ifndef VEREM_TPP
#define VEREM_TPP

#include <iostream>
#include "verem.h"
#include <ostream>


using namespace std;
template <typename T, std::size_t N>

Stack<T,N>::Stack()
{
	teteje = -1;
	for (int i = 0; i < N; ++i)
	{
		verem[i] = T();
	}
}
template <typename T, std::size_t N>
Stack<T,N>::~Stack() 
{
	
}
template <typename T, std::size_t N>
bool Stack<T,N>:: isempty()
{
	if (teteje == -1)
		return true;
	else
		return false;
}
template <typename T, std::size_t N>
bool Stack<T,N>::isfull()
{
	return(teteje == (N - 1));
}
template <typename T, std::size_t N>
void Stack<T,N>::push(T x)
{
	if (isfull())
	{
		cout << "Stack Overflow"<<endl;
	}
	else
	{
		++teteje;
		verem[teteje] = x;
	}
}
template <typename T, std::size_t N>
T Stack<T,N>::pop()
{
	if (isempty())
	{
		cout << "Stack Underflow" << endl;
		return T();
	}
	else
	{
		T elem = verem[teteje];
		--teteje;
		return elem;
	}
}
template <typename T, std::size_t N>
int Stack<T,N>::size()
{
	return (teteje + 1);
}
template <typename T, std::size_t N>

T Stack<T,N>::top()
{
	if (isempty())
	{
		cout << "Stack Underflow" << endl;
		return T();
	}
	else
	{
		return verem[teteje];
	}
}
template <typename T, std::size_t N>
void Stack<T, N>::print(std::ostream& os) const
{
	for (int i = teteje; i >= 0; --i)
	{
		os << verem[i] << " ";
	}
	os << std::endl;
}
template <typename T, std::size_t N>
void Stack<T, N>::pop_all()
{
	teteje = -1;
	return;
}
#endif