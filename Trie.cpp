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
		this->word = word;				//��ʾһ���ַ�               
		isWord = false;                 //��־λ,�Ƿ�Ϊһ������  
		count = 1;						//ÿ���ַ���ʼ������һ��ǰ׺��
		memset(next, 0, sizeof(next));  //�ӽڵ��ʼ��
	}
	bool isWord;    //����������־λ
	char word;      //���洢���ַ� 
	int count;      //�ж��ٵ���ͨ������ڵ�,���ɸ����ýڵ���ɵ��ַ���ģʽ���ֵĴ��� 
	TrieNode* next[MaxBranchNum]; //next����洢���е��ӽڵ�
	vector<string> priString;    // �洢�Ӹ����ý�㴦��ɵ��ַ�����Ϊǰ׺�ĵ��ʼ���*/
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
	
	void insert(string str);          //���뺯�� - ���뵥��
	void updateVec(TrieNode* curNode, string str);
	bool remove(string str);          //ɾ������ - ɾ������
	void delPriWord(string str);
	bool searchStr(string str);      //��ѯ���� - ��ѯ�������� 
	bool priSearchStr(string str);   //ǰ׺���� - ��ѯָ��ǰ׺ 
	int getPriNum(string str);        //ǰ׺�������� - ��ѯָ��ǰ׺���ֵĴ��� 
	TrieNode* getChKNode(string str, int k); //��ȡstr��k��λ�����ڵĽ�� 
	void printPriWord(string str);
	void show();
	void show(TrieNode* pRoot);
	void Destory(TrieNode* pRoot);    //���ٺ���
private:
	TrieNode* pRoot;
};
void TrieTree::insert(string str)      //���ʲ������
{
	if (str.length() == 0)
		return;
	TrieNode* curNode = pRoot;
	//���ø��±�־λ��ֻ���²���ĵ��ʽ����˽�㿪�ٲŻ���Ϊtrue 
	bool isUpdate = false;
	//���������뵥�ʵ�ÿ���ַ��������в��� 
	for (char str_ch : str)
	{
		/* ��·���и��ַ������ڣ�����count�򣬼������ӽڵ���� */
		if (curNode->next[str_ch] != nullptr)
		{
			curNode = curNode->next[str_ch];
			curNode->count++;
		}
		/**
		 * ��·���и��ַ���㲻���ڣ�Ϊ���ַ������µĽ�㣬
		 * ���������ӽڵ����
		 */
		else
		{
			TrieNode* newNode = new TrieNode(str_ch);
			curNode->next[str_ch] = newNode;
			curNode = curNode->next[str_ch];
			isUpdate = true; // ���±�־λ��Ϊtrue
		}
	}
	//���ʲ�����ɺ󣬸ý���������־λ��Ϊtrue 
	curNode->isWord = true;
	// ���ò�����º������и��� 
	if (isUpdate)
	{
		updateVec(curNode, str);
	}
}
void TrieTree::updateVec(TrieNode* curNode, string str)
{
	//�ɺ���ǰ������������ݲ�����,curNode->str���һ���ַ�
	assert(curNode != nullptr);
	int k = str.size();
	auto it = str.rbegin();
	while (it != str.rend())
	{
		TrieNode* node = curNode;
		if (node != pRoot)
		{
			//ÿ������һ����㣬������priString 
			node->priString.push_back(str);
		}
		else
		{
			/* ע����ڵ㲻����priString  */
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
	// curNode ָ��Trie���ĸ��ڵ� 
	TrieNode* curNode = pRoot;
	// ����ָ����ѯ���ʵ�ÿ���ַ�
	for (char str_ch : str)
	{
		// ��ǰ��㲻Ϊ�գ���curNode���������ӽڵ�ƥ���¸��ַ� 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	// ����ǰ��㲻Ϊ�ղ����䵥��������־λΪtrue�����ʾ���ʴ��ڡ�
	return (curNode != nullptr && curNode->isWord);
}
bool TrieTree::priSearchStr(string str)
{
	if (str.length() == 0)
	{
		return false;
	}
	// curNode ָ��Trie���ĸ��ڵ� 
	TrieNode* curNode = pRoot;
	// ����ָ��ǰ׺��ÿ���ַ�
	for (char str_ch : str)
	{
		// ��ǰ��㲻Ϊ�գ���curNode���������ӽڵ�ƥ���¸��ַ� 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	// ����ǰ��㲻Ϊ�գ����ʾǰ׺�Ǵ��ڵģ�����true��
	return (curNode != nullptr);
}
int TrieTree::getPriNum(string str)
{
	if (str.length() == 0)
	{
		return 0;
	}
	// �����ǰ׺û�г��ֹ���ֱ�ӷ���0 
	if (!priSearchStr(str))
		return 0;
	// curNode ָ��Trie���ĸ��ڵ� 
	TrieNode* curNode = pRoot;
	for (char str_ch : str)
	{
		// ��ǰ��㲻Ϊ�գ���curNode���������ӽڵ�ƥ���¸��ַ� 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	/* ֱ�ӷ��ص�ǰ����count */
	if (curNode != nullptr)
		return curNode->count;
	return 0;
}
TrieNode* TrieTree::getChKNode(string str, int k)
{
	// curNode ָ��Trie���ĸ��ڵ�
	TrieNode* curNode = pRoot;
	for (char str_ch : str)
	{
		// ��������k��Ԫ��ֱ������ѭ�� 
		if (k-- == 0)
			break;
		// ��ǰ��㲻Ϊ�գ���curNode���������ӽڵ�ƥ���¸��ַ� 
		if (curNode != nullptr)
		{
			curNode = curNode->next[str_ch];
		}
	}
	// ���ص�k���ַ����ڵĽ��
	return curNode;
}
bool TrieTree::remove(string str)     //strָһ������
{
	/* ͨ��searchStr��ѯ�����ж�Tire�����Ƿ����str �����ڷ���false */
	if (str.length() == 0 || !searchStr(str))
		return false;
	/**
	 * �����strΪǰ׺�ĵ��ʸ�������1����ô���ǲ���������ɾ���õ���
	 * ����ֻ�Ǹõ������һ���ַ���isword����false����ʾ��������
	 * �Ǹ��������ʡ��������������ǿ�������Ϊǰ׺�ģ���Ȼ������Trie����
	 *�����´���Ҫ�����Ľ���ʱ�򲻱ؿ���һ��һ���ģ�
	 * ��ע�⣬���ǻ���Ҫ���ϻ��ݵ���������ÿ������count��Ա
	 */
	delPriWord(str);   //����ɾ�����º��� 
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
	/* ���¸��ڵ��־λ */
	bool updateRoot = false;
	/* ������ַ���ǰ׺��Ӱ���κ�����Ԫ�أ�str[0]��ǰ׺����Ϊ1����ʾɾ�����ʵ�
	 * ·��û��������֧���õ��ʵ����н�㶼��ɾ�����������Ҫ����root�����Ӧ
	 * ��next��
	 */
	if (getPriNum(str.substr(0, 1)) == 1)
	{
		updateRoot = true;
	}
	// �Ӻ���ǰ������ɾ���ĵ���
	int k = str.size();
	auto it = str.rbegin();
	while (it != str.rend())
	{
		// �õ��ַ�����Ӧ����Ӧ��� 
		TrieNode* delNode = getChKNode(str, k--);
		/**
		 * count��Ϊ1���ҵ�ǰ��㲻�Ǹ��ڵ㣬�ͽ��н��ɾ������
		 * ��ע�⣬�������ǲ���������ɾ���ý�㣬������ʹ��delete
		 * ɾ����㣬�������ǽ��ý����Ϊnullptr���ɣ���Ϊ���ǻ�Ҫ
		 * ��֤�´ο��Լ���ʹ�øý�㣬���ұ�֤������������ȷִ��
		 * ��ע�⣬��
		 */
		if (delNode->count == 1 && delNode != pRoot)
		{
			delNode->isWord = false;
		}
		/*
		 * ����count��Ϊ1�����ϲ��ϻ��ݽ���Ӧ����count�����һ,
		 * ������ɾ������ǰ׺����count��
		 */
		else
		{
			delNode->count -= 1;
		}
		++it;
	}
	// ����root���ڵ� 
	if (updateRoot)
	{
		pRoot->next[str[0]] = nullptr;
	}
	return true;
}
void TrieTree::delPriWord(string str)
	{
		//�ɺ���ǰ������������ݲ����� 
		int k = str.size();
		auto it = str.rbegin();
		while (it != str.rend())
		{
			char str_ch = *it;
			TrieNode* node = getChKNode(str, k--);
			if (node != pRoot)
			{
				// ����priStringɾ��ָ����Ԫ�� 
				auto it = node->priString.begin();
				while (it != node->priString.end())
				{
					if (*it == str)
					{
						// ɾ��ָ��Ԫ�غ�ֱ���˳�ѭ�����������ϻ��� 
						node->priString.erase(it);
						break;
					}
					++it;
				}
			}
			else
			{
				// ���������ڵ㣬��������ֱ�ӽ������� 
				break;
			}
			++it;
		}
	}
void  TrieTree::printPriWord(string str)
{
	TrieNode* curNode = pRoot;
	/**
	 *	������ǰ׺�������һ���ַ�����Ϊ���һ���ַ��оʹ洢
	 *	�Ÿ�ǰ׺�����е���
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
		// ������ϸ�ǰ׺�����е��� 
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
			// ���ϵݹ�ؽ����пռ��ͷ� 
			Destory(pRoot->next[i]);
		}
	}
	delete pRoot; // �ӽڵ�ȫ��ɾ���������ͷŸ��ڵ� 
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
