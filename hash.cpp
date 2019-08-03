#include <iostream>
#include <vector>  // 使用vector容器
#include <algorithm>  // 使用泛型算法
#include <functional> // C++ STL的函数对象 greater less greater_equal less_
#include <typeinfo>
#include <string>
#include <cmath>
#include <list>
#include <time.h>
using namespace std;

template<typename T>
class CHash
{
public:
	int operator()(const T& val)
	{
		//默认用除留余数法
		return val;
	}
};
#if 0
// string  User  People
template<>
class CHash<string>   //类模板的特例化
{
public:
	int operator()(const string& val)
	{
		// hello  olleh
		int sum = 0;
		for (int i = 0; i < val.length(); ++i)
		{
			sum += (val[i] >> i);
		}
		return sum;
	}
};
#endif
// key 链地址法实现的哈希表结构 【key,id value Person】 
template<typename K, typename V>
struct MyPair
{
	MyPair(K k = K(), V v = V())
		:first(k), second(v) {}
	K first; // key
	V second; // value
};
template<typename K, typename V>
bool operator==(const MyPair<K, V>& lhs, const MyPair<K, V>& rhs)
{
	return lhs.first == rhs.first;
}
template<typename K, typename V>
MyPair<K, V> mymake_pair(const K& key, const V& val)
{
	return MyPair<K, V>(key, val);
}
template<typename K, typename V, typename HashType = CHash<K>>  //缺省模板实参
class CHashMap // 映射表  key -> value
{
public:
	CHashMap(int size = 7, double lf = 0.75)
		:_loadFactor(lf), _usedBuckets(0)
	{
		// 给哈希表开辟数组空间的
		_hashVec.resize(size);
	}
	//给哈希表中插入元素
	void put(const MyPair<K, V>& pair)
	{
		double lf = _usedBuckets * 1.0 / _hashVec.size();
		if (lf >= _loadFactor)
		{
			resize();
		}
		int index = _hash(pair.first) % _hashVec.size();
		list<MyPair<K, V>>& curList = _hashVec[index];
		if (curList.empty())
		{
			curList.push_front(pair);
			_usedBuckets++;
		}
		else
		{
			auto it = find(curList.begin(), curList.end(), pair);
			//表示当前链表中不包含pair			
			if (it == curList.end())
			{
				curList.push_front(pair);
			}
		}
	}
	// 删除哈希表中的元素
	void remove(const K& key)
	{
		int index = _hash(key) % _hashVec.size();
		list<MyPair<K, V>>& curList = _hashVec[index];
		if (!curList.empty())
		{
			// 1.在list怎么找val
			auto it = find(curList.begin(), curList.end(), MyPair<K, V>(key));
			// 2.找到val，删除，找不到，return
			if (it != curList.end())
			{
				curList.erase(it);
				// 3.删除val，如果桶变成空的，要给
				if (curList.empty())
				{
					_usedBuckets--;
				}
			}
		}
	}
	// 在哈希表中查找元素  
	// map["3452346"] 1.查询功能 2.赋值功能 map["3452346"]="zhangsan" 3.增加
	V& operator[](const K& key)  // MyPair<K,V>
	{
		int index = _hash(key) % _hashVec.size();
		list<MyPair<K, V>>& curList = _hashVec[index];
		if (!curList.empty())
		{
			// 1.在list查找val
			auto it = find(curList.begin(), curList.end(), MyPair<K, V>(key));
			// 2.找到val,return value
			if (it != curList.end())
			{
				return it->second;
			}
		}
		// 没有找到
		curList.push_front(MyPair<K, V>(key));
		return curList.begin()->second;
	}
	void show()
	{
		for (int i = 0; i < _hashVec.size(); ++i)
		{
			list<MyPair<K, V>>& list = _hashVec[i];
			if (!list.empty())
			{
				auto it = list.begin();
				for (; it != list.end(); ++it)
				{
					cout << "key:" << it->first << "value" << it->second << endl;
				}
			}	
		}
	}
private:
	vector<list<MyPair<K, V>>> _hashVec;
	double _loadFactor; // 记录加载因子
	int _usedBuckets;   //表示所使用单侧数组的元素个数
	HashType _hash;     //专门计算T类型对象的哈希值的
	//获取素数
	int getPrime(int n)
	{
		for (int i = n + 1;; ++i)
		{
			int k = (int)sqrt(i);
			int j = 2;
			for (; j <= k; ++j)
			{
				if (i % j == 0)
					break;
			}
			if (j > k)
			{
				return i;
			}
			else
			{
				continue;
			}
		}
	}
	// 动态扩容
	void resize()
	{
		// 1.先把现有的哈希表交换到老的容器当中
		vector<list<MyPair<K, V>>> _oldhash;
		_oldhash.swap(_hashVec);

		// 2.给_hashVec resize桶内存
		_hashVec.resize(getPrime(_oldhash.size()));

		// 3.遍历old哈希表，的每一个链表的节点，计算其散列码，splice到新的hash中
		for (auto it = _oldhash.begin(); // it -> list<int>
			it != _oldhash.end();
			++it)
		{
			if (!it->empty())
			{
				for (auto it1 = it->begin(); it1 != it->end();)
				{
					int index = _hash(it1->first) % _hashVec.size();
					list<MyPair<K, V>>& mylist = _hashVec[index];
					if (!mylist.empty())
					{
						// 4.如果桶被第一次占用，_usedBuckets++
						_usedBuckets++;
					}
					// 把旧的hash表中的list节点直接搬到新的哈希表当中
					mylist.splice(mylist.begin(), *it, it1);
					it1 = it->begin();
				}
			}
		}
	}
};

int main()
{
	CHashMap<int, int> hashMap;
	hashMap.put(mymake_pair(10, 20));
	hashMap.put(mymake_pair(14, 45));
	hashMap.put(mymake_pair(18, 73));
	hashMap.put(mymake_pair(19, 89));
	hashMap[20] = 987;
	cout << hashMap[10] << endl;
	cout << hashMap[20] << endl;
	hashMap.show();
	cout << endl;
	hashMap.remove(10);
	hashMap.show();
	cout << endl;
	return 0;
}
