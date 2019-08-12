#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
///-z:65-90    A-Z:97-122*/
const int MaxBranchNum = 123;
struct TrieNode
{
	TrieNode(char word = 0)
	{
		this->word = word;				//表示一个字符               
		isWord = false;                 //标志位,是否为一个单词  
		count = 1;						//每个字符初始化就算一个前缀了
		memset(next, 0, sizeof(next));  //子节点初始化
	}
	bool isWord;    //单词完整标志位
	char word;      //结点存储的字符 
	int count;      //有多少单词通过这个节点,即由根至该节点组成的字符串模式出现的次数 
	TrieNode* next[MaxBranchNum]; //next数组存储所有的子节点
	vector<string> priString;    // 存储从根到该结点处组成的字符串作为前缀的单词集合*/
};
class TrieTree {
public:
	TrieTree()
	{
		pRoot = new TrieNode();
	}
	~TrieTree()
	{
		Destory(pRoot);
	}
	
	void insert(string str);          //插入函数 - 插入单词
	void updateVec(TrieNode* curNode, string str);
	bool remove(string str);          //删除函数 - 删除单词
	void delPriWord(string str);
	bool searchStr(string str);      //查询函数 - 查询完整单词 
	bool priSearchStr(string str);   //前缀搜索 - 查询指定前缀 
	int getPriNum(string str);        //前缀次数搜索 - 查询指定前缀出现的次数 
	TrieNode* getChKNode(string str, int k); //获取str第k个位置所在的结点 
	void printPriWord(string str);
	void show();
	void show(TrieNode* pRoot);
	void Destory(TrieNode* pRoot);    //销毁函数
private:
	TrieNode* pRoot;
};
void TrieTree::insert(string str)      //单词插入操作
{
	if (str.length() == 0)
		return;
	TrieNode* curNode = pRoot;
	//设置更新标志位，只有新插入的单词进行了结点开辟才会置为true 
	bool isUpdate = false;
	//遍历待插入单词的每个字符，并进行插入 
	for (char str_ch : str)
	{
		/* 在路径中该字符结点存在，更新count域，继续向子节点遍历 */
		if (curNode->next[str_ch] != nullptr)
		{
			curNode = curNode->next[str_ch];
			curNode->count++;
		}
		/**
		 * 在路径中该字符结点不存在，为该字符创建新的结点，
		 * 并继续向子节点遍历
		 */
		else
		{
			TrieNode* newNode = new TrieNode(str_ch);
			curNode->next[str_ch] = newNode;
			curNode = curNode->next[str_ch];
			isUpdate = true; // 更新标志位置为true
		}
	}
	//单词插入完成后，该结点的完整标志位置为true 
	curNode->isWord = true;
	// 调用插入更新函数进行更新 
	if (isUpdate)
	{
		updateVec(curNode, str);
	}
}
void TrieTree::updateVec(TrieNode* curNode, string str)
{
	//由后向前遍历，向根回溯并更新,curNode->str最后一个字符
	assert(curNode != nullptr);
	int k = str.size();
	auto it = str.rbegin();
	while (it != str.rend())
	{
		TrieNode* node = curNode;
		if (node != pRoot)
		{
			//每遍历到一个结点，更新其priString 
			node->priString.push_back(str);
		}
		else
		{
			/* 注意根节点不更新priString  */
			break;
		}
		++it;
		curNode = getChKNode(str, --k);
	}
}
bool TrieTree::searchStr(string str)
{
	if (str.length() == 0)
	{
		return false;
	}
	// curNode 指向Trie树的根节点 
	TrieNode* curNode = pRoot;
	// 遍历指定查询单词的每个字符
	for (char str_ch : str)
	{
		// 当前结点不为空，则curNode继续走向子节点匹配下个字符 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	// 若当前结点不为空并且其单词完整标志位为true，则表示单词存在。
	return (curNode != nullptr && curNode->isWord);
}
bool TrieTree::priSearchStr(string str)
{
	if (str.length() == 0)
	{
		return false;
	}
	// curNode 指向Trie树的根节点 
	TrieNode* curNode = pRoot;
	// 遍历指定前缀的每个字符
	for (char str_ch : str)
	{
		// 当前结点不为空，则curNode继续走向子节点匹配下个字符 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	// 若当前结点不为空，则表示前缀是存在的，返回true。
	return (curNode != nullptr);
}
int TrieTree::getPriNum(string str)
{
	if (str.length() == 0)
	{
		return 0;
	}
	// 如果该前缀没有出现过，直接返回0 
	if (!priSearchStr(str))
		return 0;
	// curNode 指向Trie树的根节点 
	TrieNode* curNode = pRoot;
	for (char str_ch : str)
	{
		// 当前结点不为空，则curNode继续走向子节点匹配下个字符 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	/* 直接返回当前结点的count */
	if (curNode != nullptr)
		return curNode->count;
	return 0;
}
TrieNode* TrieTree::getChKNode(string str, int k)
{
	// curNode 指向Trie树的根节点
	TrieNode* curNode = pRoot;
	for (char str_ch : str)
	{
		// 遍历到第k个元素直接跳出循环 
		if (k-- == 0)
			break;
		// 当前结点不为空，则curNode继续走向子节点匹配下个字符 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	// 返回第k个字符所在的结点
	return curNode;
}
bool TrieTree::remove(string str)     //str指一个单词
{
	/* 通过searchStr查询函数判断Tire树中是否存在str 不存在返回false */
	if (str.length() == 0 || !searchStr(str))
		return false;
	/**
	 * 如果以str为前缀的单词个数超过1，那么我们并不是真正删除该单词
	 * 而是只是该单词最后一个字符的isword域置false，表示它将不再
	 * 是个完整单词。但是其他单词是可以以它为前缀的，仍然存在于Trie树中
	 *（当下次需要这样的结点的时候不必开辟一个一样的）
	 * 请注意，我们还需要向上回溯到根，更新每个结点的count成员
	 */
	delPriWord(str);   //调用删除更新函数 
	if (getPriNum(str) > 1)
	{
		int k = str.size();
		TrieNode* lastNode = getChKNode(str, k);
		lastNode->isWord = false;
		while (lastNode != pRoot)
		{
			lastNode->count--;
			lastNode = getChKNode(str, --k);
		}
		return true;
	}
	/* 更新根节点标志位 */
	bool updateRoot = false;
	/* 如果该字符的前缀不影响任何其他元素，str[0]的前缀次数为1，表示删除单词的
	 * 路径没有其他分支，该单词的所有结点都将删除，但是最后要更新root结点相应
	 * 的next域
	 */
	if (getPriNum(str.substr(0, 1)) == 1)
	{
		updateRoot = true;
	}
	// 从后向前遍历待删除的单词
	int k = str.size();
	auto it = str.rbegin();
	while (it != str.rend())
	{
		// 拿到字符所对应的相应结点 
		TrieNode* delNode = getChKNode(str, k--);
		/**
		 * count域为1并且当前结点不是根节点，就进行结点删除操作
		 * 请注意，这里我们不能真正的删除该结点，即不能使用delete
		 * 删除结点，而仅仅是将该结点置为nullptr即可，因为我们还要
		 * 保证下次可以继续使用该结点，并且保证析构函数的正确执行
		 * 请注意，当
		 */
		if (delNode->count == 1 && delNode != pRoot)
		{
			delNode->isWord = false;
		}
		/*
		 * 否则count域不为1则向上不断回溯将相应结点的count的域减一,
		 * 即更新删除结点的前缀结点的count域
		 */
		else
		{
			delNode->count -= 1;
		}
		++it;
	}
	// 更新root根节点 
	if (updateRoot)
	{
		pRoot->next[str[0]] = nullptr;
	}
	return true;
}
void TrieTree::delPriWord(string str)
	{
		//由后向前遍历，向根回溯并更新 
		int k = str.size();
		auto it = str.rbegin();
		while (it != str.rend())
		{
			char str_ch = *it;
			TrieNode* node = getChKNode(str, k--);
			if (node != pRoot)
			{
				// 遍历priString删除指定的元素 
				auto it = node->priString.begin();
				while (it != node->priString.end())
				{
					if (*it == str)
					{
						// 删除指定元素后，直接退出循环，继续向上回溯 
						node->priString.erase(it);
						break;
					}
					++it;
				}
			}
			else
			{
				// 遍历到根节点，不作操作直接结束函数 
				break;
			}
			++it;
		}
	}
void  TrieTree::printPriWord(string str)
{
	TrieNode* curNode = pRoot;
	/**
	 *	遍历到前缀串的最后一个字符，因为最后一个字符中就存储
	 *	着该前缀的所有单词
	 */
	for (char str_ch : str)
	{
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	if (curNode != nullptr)
	{
		// 输出符合该前缀的所有单词 
		vector<string> &res = curNode->priString;
		for (string val : res)
		{
			cout << val << endl;
		}
		cout << "---------------------" << endl;
	}
}
void TrieTree::show()
{
	show(this->pRoot);
}
void TrieTree::show(TrieNode* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}
	int i;
	static char word[1024 + 1] = { 0 };
	static int j = 0;
	for (i = 64; i < MaxBranchNum; ++i)
	{
		if (pRoot->next[i] == NULL)
		{
			continue;
		}
		word[j++] = pRoot->next[i]->word;
		if (pRoot->next[i]->isWord == true)
		{
			word[j +1] = '\0';
			printf("%-20s %-8d\n", word, pRoot->next[i]->count);
		}
		show(pRoot->next[i]);
		j--;
		word[j] = 0;
	}
	return;
}
void TrieTree::Destory(TrieNode* pRoot)
{
	if (pRoot == nullptr)
		return;

	for (int i = 0; i < MaxBranchNum; i++)
	{
		if (pRoot->next[i] != nullptr)
		{
			// 不断递归地将所有空间释放 
			Destory(pRoot->next[i]);
		}
	}
	delete pRoot; // 子节点全部删除后便可以释放根节点 
	pRoot = nullptr;
	return;
}

int main()
{
	TrieTree trie;
	trie.insert("apps");
	trie.insert("apply");
	trie.insert("apple");
	trie.insert("append");
	trie.insert("append");
	trie.insert("acccccc");
	trie.insert("addddd");
	trie.insert("bbbbbbb");
	trie.printPriWord("ap");
	trie.remove("apps");
	trie.remove("apply");
	trie.remove("bbbbbbb");
	trie.printPriWord("ap");
	trie.show();
	return 0;
}
