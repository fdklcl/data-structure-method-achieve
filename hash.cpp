#include <iostream>
#include <vector>  // ʹ��vector����
#include <algorithm>  // ʹ�÷����㷨
#include <functional> // C++ STL�ĺ������� greater less greater_equal less_
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
		//Ĭ���ó���������
		return val;
	}
};
#if 0
// string  User  People
template<>
class CHash<string>   //��ģ���������
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
// key ����ַ��ʵ�ֵĹ�ϣ��ṹ ��key,id value Person�� 
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
template<typename K, typename V, typename HashType = CHash<K>>  //ȱʡģ��ʵ��
class CHashMap // ӳ���  key -> value
{
public:
	CHashMap(int size = 7, double lf = 0.75)
		:_loadFactor(lf), _usedBuckets(0)
	{
		// ����ϣ��������ռ��
		_hashVec.resize(size);
	}
	//����ϣ���в���Ԫ��
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
			//��ʾ��ǰ�����в�����pair			
			if (it == curList.end())
			{
				curList.push_front(pair);
			}
		}
	}
	// ɾ����ϣ���е�Ԫ��
	void remove(const K& key)
	{
		int index = _hash(key) % _hashVec.size();
		list<MyPair<K, V>>& curList = _hashVec[index];
		if (!curList.empty())
		{
			// 1.��list��ô��val
			auto it = find(curList.begin(), curList.end(), MyPair<K, V>(key));
			// 2.�ҵ�val��ɾ�����Ҳ�����return
			if (it != curList.end())
			{
				curList.erase(it);
				// 3.ɾ��val�����Ͱ��ɿյģ�Ҫ��
				if (curList.empty())
				{
					_usedBuckets--;
				}
			}
		}
	}
	// �ڹ�ϣ���в���Ԫ��  
	// map["3452346"] 1.��ѯ���� 2.��ֵ���� map["3452346"]="zhangsan" 3.����
	V& operator[](const K& key)  // MyPair<K,V>
	{
		int index = _hash(key) % _hashVec.size();
		list<MyPair<K, V>>& curList = _hashVec[index];
		if (!curList.empty())
		{
			// 1.��list����val
			auto it = find(curList.begin(), curList.end(), MyPair<K, V>(key));
			// 2.�ҵ�val,return value
			if (it != curList.end())
			{
				return it->second;
			}
		}
		// û���ҵ�
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
	double _loadFactor; // ��¼��������
	int _usedBuckets;   //��ʾ��ʹ�õ��������Ԫ�ظ���
	HashType _hash;     //ר�ż���T���Ͷ���Ĺ�ϣֵ��
	//��ȡ����
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
	// ��̬����
	void resize()
	{
		// 1.�Ȱ����еĹ�ϣ�������ϵ���������
		vector<list<MyPair<K, V>>> _oldhash;
		_oldhash.swap(_hashVec);

		// 2.��_hashVec resizeͰ�ڴ�
		_hashVec.resize(getPrime(_oldhash.size()));

		// 3.����old��ϣ����ÿһ������Ľڵ㣬������ɢ���룬splice���µ�hash��
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
						// 4.���Ͱ����һ��ռ�ã�_usedBuckets++
						_usedBuckets++;
					}
					// �Ѿɵ�hash���е�list�ڵ�ֱ�Ӱᵽ�µĹ�ϣ����
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
