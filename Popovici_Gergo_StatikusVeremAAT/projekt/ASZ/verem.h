/*Popovici Gergo-Benone
513*/
#ifndef VEREM_H
#define VEREM_H

#include <cstddef>

template <typename T, std::size_t N>
class Stack
{
	int teteje;
	T verem[N];
public:
	Stack();
	~Stack();
	bool isempty();
	bool isfull();
	void push(T x);
	T pop();
	int size();
	T top();
	void print(std::ostream& os) const;
	void pop_all() ;
};
#include "verem.tpp"
#endif