/*!
  @file		stack.h
  @brief	stack definition
*/
#ifndef _STACK_H
#define _STACK_H
template<class T> class Stack
{
public:
	Stack():_num(0), _max(256)	{_stack = new T[256]; }	;
	~Stack()					{ delete [] _stack; };
	void Push( T p)				{ if (_num+1 == _max) realloc(); _stack[_num++] = p; };
	T Pop()						{ return _stack[--_num]; };
	T GetTop()					{ return _stack[_num-1]; };
	bool empty(void)			{ return _num == 0;		 };
private:
	void realloc(void)			{ T *_p; _p = new T[2*_max]; memcpy(_p, _stack, _max*sizeof(T)); _max*=2; delete[] _stack; _stack = _p ; };
	T *_stack;
	int _num;
	int _max;
};

#endif