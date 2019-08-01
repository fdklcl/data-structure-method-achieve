#include<iostream>
using namespace std;
template<typename T>
class SeqStack  //模板名称+参数类型列表 = 类名称
{
public:
	SeqStack(int size = 10)
		:_pstack(new T[size])
		, _top(0)
		, _size(size)
	{}
	~SeqStack()
	{
		delete[]_pstack;
		_pstack = nullptr;
	}
	SeqStack(const SeqStack<T>& stack)
		:_top(stack._top)
		, _size(stack._size)
	{
		_pstack = new T[size];
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}
	}
	SeqStack<T>& operator=(const SeqStack<T>& stack)
	{
		if (this == &stack)
			return *this;

		delete[]_pstack;

		_top = stack._top;
		_size = stack._size;
		_pstack = new T[_size];
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}

		return *this;
	}
	void push(const T& val)
	{
		if (full())
			expand();
		_pstack[_top++] = val;
	}
	void pop()
	{
		if (empty())
			return;
		--_top;
	}
	T top() const
	{
		if (empty())
			throw "stack is empty";
		return _pstack[_top - 1];
	}
	bool full() const
	{
		return _top == _size;
	}
	bool empty() const
	{
		return _top == 0;
	}
	int lenth() const
	{
		return _top;
	}
	void show()
	{
		while (!this->empty())
		{
			cout << this->top() << " ";
			this->pop();
		}
		/*
		//从栈底向上开始输出
		for (int i = 0; i < _top; ++i)
		{
			cout << _pstack[i] << " ";
		}
		cout << endl;
		*/
	}
private:
	T* _pstack;
	int _top;
	int _size;
	void expand()
	{
		T* ptmp = new T[_size * 2];
		for (int i = 0; i < _top; ++i)
		{
			ptmp[i] = _pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};

int main()
{
	SeqStack<int> stack1;
	for (int i = 0; i < 12; i++)
	{
		stack1.push(rand() % 20 + 1);
	}

	cout << "stack lenth:" << stack1.lenth() << endl;
	cout << "stack top:" << stack1.top() << endl;
	stack1.show();
	//stack1.pop();
	//stack1.show();
	return 0;
}