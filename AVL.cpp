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
			,_height(1)      //单独一个结点自身看来其深度为1
		{}
		int _data;
		AVLNode* _left;
		AVLNode* _right;
		int _height; //表示当前结点的高度
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
			//说明左子树失衡,此时需要判断是因为左子树左孩子导致的失衡,还是左子树右孩子导致的失衡
			if (height(node->_left->_left) >= height(node->_left->_right))
			{
				//左子树太高,属于LL情况
				node = RightRotate(node);
			}
			else
			{
				//右子树太高,属于LR情况
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
				// 右孩子的右子树太高,属于RR情况
				node = LeftRotate(node);
			}
			else
			{
				// 右孩子的左子树太高,属于RL情况
				node = RightBalance(node);
			}
		}
	}
	else
	{
		;
	}

	// 在递归回溯过程中，更新节点的高度值
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
				// 右孩子的右子树太高
				node = LeftRotate(node);
			}
			else
			{
				// 右孩子的左子树太高
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
				// 左孩子的左子树太高
				node = RightRotate(node);
			}
			else
			{
				// 左孩子的右子树太高
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
				// 前驱替换
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
				// 后继替换
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

	// 在递归回溯过程中，更新节点的高度值
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
			//说明右子树高
			if (height(node->_right->_right) >= height(node->_right->_left))
			{
				//属于RR
				node = LeftRotate(node);
			}
			else
			{
				//属于RL
				node = RightBalance(node);
			}
		}

	}
	else if (node->_data < val)
	{
		node->_right = erease(node->_right, val);

		if (height(node->_left) - height(node->_right) > 1)
		{
			//说明左子树高
			if (height(node->_left->_left) >= height(node->_left->_right))
			{
				//属于LL
				node = RightRotate(node);
			}
			else
			{
				//属于LR
				node = LeftBalance(node);
			}
		}
	}
	else 
	{
		//找到待删除结点的位置,判断情况二
		if (node->_left != nullptr && node->_right != nullptr)
		{
				// 前驱替换
				AVLNode* pre = node->_left;
				while (pre->_right != nullptr)
				{
					pre = pre->_right;
				}
				//将node的值改为前驱结点的值
				node->_data = pre->_data;
				//直接删除前驱结点,前驱结点一定在当前结点的左子树中
				node->_left = erease(node->_left, pre->_data);
				if (height(node->_right) - height(node->_left) > 1)
				{
					//说明右子树高
					if (height(node->_right->_right) >= height(node->_right->_left))
					{
						//属于RR
						node = LeftRotate(node);
					}
					else
					{
						//属于RL
						node = RightBalance(node);
					}
				}
			
		}
		//情况一,只有一个左子树
		else
		{
			if (node->_left != nullptr)
			{
				AVLNode* pcur = node->_left;
				delete node;
				return pcur;
			}
			//情况二,只有一个右子树
			else if (node->_right != nullptr)
			{
				AVLNode* pcur = node->_right;
				delete node;
				return pcur;
			}
			//情况二,为叶子结点
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