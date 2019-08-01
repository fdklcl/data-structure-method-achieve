#include<iostream>
using namespace std;

template<typename T>
class SeqList
{
public:
	SeqList() :_phead(nullptr) 
	{
		_phead = new listNode();
		cout << "SeqList" << endl;
	}
	~SeqList() 
	{
		listNode* pcur = _phead;
		while (pcur != nullptr)
		{
			_phead = pcur->_pnext;
			delete pcur;
			pcur = _phead;
		}
	}
	SeqList(const SeqList& src) 
	{
		this->_phead = new listNode();
		listNode* p = this->_phead;
		listNode* pGet = nullptr;
		listNode* pcur = src._phead->_pnext;
		while(pcur != nullptr)
		{
			pGet = new listNode(pcur->_mdata);
			p->_pnext = pGet;
			pcur = pcur->_pnext;
			p = p->_pnext;
		}
		cout << "SeqList(const SeqList& src)" << endl;
	}
	SeqList& operator=(const SeqList& src)
	{
		if (this == &src)
			return *this;

		listNode* pre = _phead;
		listNode* pcur = _phead->_pnext;
		listNode* psrc = src._phead->_pnext;

		while(pcur != nullptr && psrc != nullptr)
		{ 
			pcur->_mdata = psrc->_mdata;
			pcur = pcur->_pnext;
			psrc = psrc -> _pnext;
			pre = pre->_pnext;
		}
		if (pcur != nullptr)
		{
			//说明mhead长，则需要删除多余部分
			pre->_pnext = nullptr;
			listNode* p = pcur;
			while (pcur != nullptr)
			{
				pcur = pcur->_pnext;
				delete p;
				p = pcur;
			}
		}
		else
		{
			listNode* pGet = nullptr;
			while (psrc != nullptr)
			{
				pGet = new listNode(pcur->_mdata);
				pre->_pnext = pGet;
				pre = pre->_pnext;
				psrc = psrc->_pnext;
			}
			
		}
		cout << "SeqList& operator=(const SeqList& src)" << endl;
		return *this;
	}
	void headInsert(const T& val);
	void rearInsert(const T& val);
	void insert(const T& val,const T& val2);
	void headRemove();
	void rearRemove();
	void remove(const T& val);
	void reverse();
	void show()const;
private:
	struct listNode
	{
		listNode(T mdata = T())
			:_mdata(mdata),_pnext(nullptr) {}
		T _mdata;
		listNode* _pnext;
	};
	listNode* _phead;
};
template<typename T>
void SeqList<T>::headInsert(const T& val)
{
	listNode* pGet = new listNode(val);
	pGet->_pnext = _phead->_pnext;
	_phead->_pnext = pGet;
}
template<typename T>
void SeqList<T>::rearInsert(const T& val)
{
	listNode* pGet = new listNode(val);
	listNode* pcur = _phead;
	while (pcur->_pnext != nullptr)
	{
		pcur = pcur->_pnext;
	}
	pcur->_pnext = pGet;
}
template<typename T>
void SeqList<T>::insert(const T& val,const T& val2)
{
	listNode* pGet = new listNode(val2);
	listNode* pcur = _phead->_pnext;
	while (pcur->_mdata != val)
	{
		if (pcur == nullptr)
			throw"list no exist data!";
		pcur = pcur->_pnext;
	}
	pGet->_pnext = pcur->_pnext;
	pcur->_pnext = pGet;
}
template<typename T>
void SeqList<T>::headRemove()
{
	listNode* pcur = _phead->_pnext;
	_phead->_pnext = pcur->_pnext;
	delete pcur;
}
template<typename T>
void SeqList<T>::rearRemove()
{
	listNode* pre = nullptr;
	listNode* pcur = _phead;
	while (pcur->_pnext != nullptr)
	{
		pre = pcur;
		pcur = pcur->_pnext;
	}
	//退出循环时，pcur指向最后一个结点
	delete pcur;
	pre->_pnext = nullptr;
}
template<typename T>
void SeqList<T>::remove(const T& val)
{
	listNode* pcur = _phead;
	while (pcur->_pnext->_mdata != val)
	{
		pcur = pcur->_pnext;
		if (pcur->_pnext == nullptr)
		{
			throw "list not exist data!";
			//return;
		}
	}
	pcur->_pnext = pcur->_pnext->_pnext;
	
}
template<typename T>
void SeqList<T>::reverse()
{
	listNode* pre = nullptr;
	listNode* pcur = _phead->_pnext;
	_phead->_pnext = nullptr;
	while (pcur != nullptr)
	{
		pre = pcur;
		pcur = pcur->_pnext;
		pre->_pnext = _phead->_pnext;
		_phead->_pnext = pre;
	}
}
template<typename T>
void SeqList<T>::show()const
{
	listNode* pcur = _phead;
	while (pcur->_pnext != nullptr)
	{
		cout << pcur->_pnext->_mdata << " ";
		pcur = pcur->_pnext;
	}
	cout << endl;
}

int main()
{
	SeqList<int> list;
	for (int i = 0; i < 10; ++i)
	{
		//list.headInsert(i);
		list.rearInsert(i);
	}        //list 0 1 2 3 4 5 6 7 8 9
	SeqList<int> list2;
	for (int i = 10; i < 22; ++i)
	{
		//list.headInsert(i);
		list2.rearInsert(i);
	}        //list2 10 11 12 13 14 15 16 17 18 19 20 21 22
	list2 = list;   //list2  0 1 2 3 4 5 6 7 8 9
	cout << "list2:";
	list2.show();
	SeqList<int> list3(list);
	cout << "list3:";
	list3.show(); //list3  0 1 2 3 4 5 6 7 8 9
	list.headRemove();
	list.rearRemove();
	list.remove(5);
	list.insert(4, 5);
	list.insert(8, 9);
	list.show();
	list.reverse();
	list.show();
	return 0;
}