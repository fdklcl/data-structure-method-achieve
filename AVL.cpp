#include<iostream>
#include<queue>
using namespace std;

class AVLTree
{
public:
	AVLTree() :_root(nullptr)
	{}
	void insert(const int val);
	void erese(const int val);
	void levelOrder();
	void norLevelOrder()const;
private:
	struct AVLNode 
	{
		AVLNode(int data = 10)
			:_data(data)
			,_left(nullptr)
			,_right(nullptr)
			,_height(1)      //����һ����������������Ϊ1
		{}
		int _data;
		AVLNode* _left;
		AVLNode* _right;
		int _height; //��ʾ��ǰ���ĸ߶�
	};
	AVLNode* _root;
	AVLNode* insert(AVLNode* node, const int val);
	AVLNode* erease(AVLNode* node, const int val);
	int height(AVLNode* node);
	int maxHeight(AVLNode* node1, AVLNode* node2);
	AVLNode* LeftRotate(AVLNode* node);
	AVLNode* RightRotate(AVLNode* node);
	AVLNode* LeftBalance(AVLNode* node);
	AVLNode* RightBalance(AVLNode* node);
	int AVLTreeLenth(AVLNode* node);
	void levelOrder(AVLNode* node,int lenth)const;
};

int AVLTree::height(AVLNode* node)
{
	return node == nullptr ? 0 : node->_height;
}
int AVLTree::maxHeight(AVLNode* node1, AVLNode* node2)
{
	return height(node1) > height(node2) ? height(node1) : height(node2);
}
AVLTree::AVLNode* AVLTree::LeftRotate(AVLNode* node)
{
	AVLNode* child = node->_right;
	node->_right = child->_left;
	child->_left = node;

	node->_height = maxHeight(node->_left,node->_right) + 1;
	child->_height = maxHeight(child->_left, child->_right) + 1;
	return child;
}
AVLTree::AVLNode* AVLTree::RightRotate(AVLNode* node)
{
	AVLNode* child = node->_left;
	node->_left = child->_right;
	child->_right = node;

	node->_height = maxHeight(node->_left, node->_right) + 1;
	child->_height = maxHeight(node->_left, node->_right) + 1;
	return child;
}
AVLTree::AVLNode* AVLTree::LeftBalance(AVLNode* node)
{
	node->_left = LeftRotate(node->_left);
	return RightRotate(node);
}
AVLTree::AVLNode* AVLTree::RightBalance(AVLNode* node)
{
	node->_right = RightRotate(node->_right);
	return LeftRotate(node);
}

void AVLTree::insert(const int val)
{
	this->_root = insert(_root, val);
}
AVLTree::AVLNode* AVLTree::insert(AVLNode* node, const int val)
{
	if (node == nullptr)
		return new AVLNode(val);

	if (node->_data > val)
	{
		node->_left = insert(node->_left, val);

		if (height(node->_left) - height(node->_right) > 1)
		{
			//˵��������ʧ��,��ʱ��Ҫ�ж�����Ϊ���������ӵ��µ�ʧ��,�����������Һ��ӵ��µ�ʧ��
			if (height(node->_left->_left) >= height(node->_left->_right))
			{
				//������̫��,����LL���
				node = RightRotate(node);
			}
			else
			{
				//������̫��,����LR���
				node = LeftBalance(node);
			}
		}
	}
	else if (node->_data < val)
	{
		node->_right = insert(node->_right, val);

		if (height(node->_right) - height(node->_left) > 1)
		{
			if (height(node->_right->_right) >= height(node->_right->_left))
			{
				// �Һ��ӵ�������̫��,����RR���
				node = LeftRotate(node);
			}
			else
			{
				// �Һ��ӵ�������̫��,����RL���
				node = RightBalance(node);
			}
		}
	}
	else
	{
		;
	}

	// �ڵݹ���ݹ����У����½ڵ�ĸ߶�ֵ
	node->_height = maxHeight(node->_left, node->_right) + 1;
	return node;
}

/*
AVLTree::AVLNode* AVLTree::erease(AVLNode* node, const int val)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->_data > val)
	{
		node->_left = erease(node->_left, val);
		if (height(node->_right) - height(node->_left) > 1)
		{
			if (height(node->_right->_right) >= height(node->_right->_left))
			{
				// �Һ��ӵ�������̫��
				node = LeftRotate(node);
			}
			else
			{
				// �Һ��ӵ�������̫��
				node = RightBalance(node);
			}
		}
	}
	else if (node->_data < val)
	{
		node->_right = erease(node->_right, val);
		if (height(node->_left) - height(node->_right) > 1)
		{
			if (height(node->_left->_left) >= height(node->_left->_right))
			{
				// ���ӵ�������̫��
				node = RightRotate(node);
			}
			else
			{
				// ���ӵ�������̫��
				node = LeftBalance(node);
			}
		}
	}
	else
	{
		if (node->_left != nullptr && node->_right != nullptr)
		{
			if (height(node->_left) >= height(node->_right))
			{
				// ǰ���滻
				AVLNode* pre = node->_left;
				while (pre->_right != nullptr)
				{
					pre = pre->_right;
				}
				node->_data = pre->_data;
				node->_left = erease(node->_left, pre->_data);
			}
			else
			{
				// ����滻
				AVLNode* post = node->_right;
				while (post->_left != nullptr)
				{
					post = post->_left;
				}
				node->_data = post->_data;
				node->_right = erease(node->_right, post->_data);
			}
		}
		else
		{
			if (node->_left != nullptr)
			{
				AVLNode* left = node->_left;
				delete node;
				return left;
			}
			else if (node->_right != nullptr)
			{
				AVLNode* right = node->_right;
				delete node;
				return right;
			}
			else
			{
				return nullptr;
			}
		}
	}

	// �ڵݹ���ݹ����У����½ڵ�ĸ߶�ֵ
	node->_height = maxHeight(node->_left, node->_right) + 1;
	return node;
}*/
void AVLTree::erese(const int val)
{
	this->_root = erease(_root, val);
}
AVLTree::AVLNode* AVLTree::erease(AVLNode* node, const int val)
{
	if (node == nullptr)
		return nullptr;

	if (node->_data > val)
	{
		node->_left = erease(node->_left, val);

		if (height(node->_right) - height(node->_left) > 1)
		{
			//˵����������
			if (height(node->_right->_right) >= height(node->_right->_left))
			{
				//����RR
				node = LeftRotate(node);
			}
			else
			{
				//����RL
				node = RightBalance(node);
			}
		}

	}
	else if (node->_data < val)
	{
		node->_right = erease(node->_right, val);

		if (height(node->_left) - height(node->_right) > 1)
		{
			//˵����������
			if (height(node->_left->_left) >= height(node->_left->_right))
			{
				//����LL
				node = RightRotate(node);
			}
			else
			{
				//����LR
				node = LeftBalance(node);
			}
		}
	}
	else 
	{
		//�ҵ���ɾ������λ��,�ж������
		if (node->_left != nullptr && node->_right != nullptr)
		{
				// ǰ���滻
				AVLNode* pre = node->_left;
				while (pre->_right != nullptr)
				{
					pre = pre->_right;
				}
				//��node��ֵ��Ϊǰ������ֵ
				node->_data = pre->_data;
				//ֱ��ɾ��ǰ�����,ǰ�����һ���ڵ�ǰ������������
				node->_left = erease(node->_left, pre->_data);
				if (height(node->_right) - height(node->_left) > 1)
				{
					//˵����������
					if (height(node->_right->_right) >= height(node->_right->_left))
					{
						//����RR
						node = LeftRotate(node);
					}
					else
					{
						//����RL
						node = RightBalance(node);
					}
				}
			
		}
		//���һ,ֻ��һ��������
		else
		{
			if (node->_left != nullptr)
			{
				AVLNode* pcur = node->_left;
				delete node;
				return pcur;
			}
			//�����,ֻ��һ��������
			else if (node->_right != nullptr)
			{
				AVLNode* pcur = node->_right;
				delete node;
				return pcur;
			}
			//�����,ΪҶ�ӽ��
			{
				return nullptr;
			}
		}
	}

	node->_height = maxHeight(node->_left, node->_right) + 1;
	return node;
}

void AVLTree::norLevelOrder()const
{
	if (_root == nullptr)
		return;
	
	queue<AVLNode*> queue;
	queue.push(_root);
	while (!queue.empty())
	{
		AVLNode* pcur = queue.front();
		if (pcur->_left != nullptr)
		{
			queue.push(pcur->_left);
		}
		if (pcur->_right != nullptr)
		{
			queue.push(pcur->_right);
		}
		cout << pcur->_data << " ";
		queue.pop();
	}
}
void AVLTree::levelOrder()
{
	int lenth = AVLTreeLenth(_root);
	for (int i = 0; i < lenth; ++i)
	{
		levelOrder(_root, i);
	}
}
int AVLTree::AVLTreeLenth(AVLNode* node)
{
	if (node == nullptr)
		return 0;

	int leftTree = AVLTreeLenth(node->_left);
	int rightTree = AVLTreeLenth(node->_right);
	return (leftTree > rightTree ? leftTree : rightTree) + 1;
}
void AVLTree::levelOrder(AVLNode* node, int lenth)const
{
	if (node == nullptr)
		return;
	if (lenth == 0)
	{
		cout << node->_data << " ";
	}

	levelOrder(node->_left, lenth - 1);
	levelOrder(node->_right, lenth - 1);
}
#if 0
int main()
{
	AVLTree avl;
	for (int i = 1; i < 10; ++i)
	{
		avl.insert(i);
	}
	avl.norLevelOrder();
	cout << endl;
	avl.erese(6);
	avl.levelOrder();
	return 0;
}
#endif