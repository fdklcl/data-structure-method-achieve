#include<stdio.h>
#pragma once
typedef struct Node
{
	int date;
	Node* next;
}Node, * List;
void InitList(List plist);//��ʼ��������

bool Insert_head(List plist, int val);//ͷ�巨

bool Insert_tail(List plist, int val);//β�巨

bool Insert_pos(List plist, int pos, int val);//pos λ�ò���

Node* Search_pre(List plist, int key);//���� key ��ǰ��

bool Delete(List plist, int key);//ɾ�� key ������

bool IsEmpty(List plist);//�Ƿ�Ϊ��

void Destroy(List plist);//�ݻٺ���������ж�̬�����ڴ棩

int GetLength(List plist);//�õ�������ĳ���

bool Reaserve_LIst(List plist);//��������

Node* Reverse1(List plist);   //��ת

Node* LastK(List plist, int k);   //���ʱ�����ҵ�����������K���ڵ�

void DeleteLastK(List plist, int k);//���ʱ����ɾ������������K���ڵ�

void DeleteNode(List plist, Node* pDel);//O(1)ʱ��ɾ���������һ���ڵ� 

void CreateCut(List plist1, List plist2);

bool IsCut(List plist1, List plist2);

Node* IsCutNode(List plist1, List plist2);

Node* Add_List(List plist, List plist2);//�ϲ�������������  

bool IsLoop(List plist);//�ж�һ���������Ƿ��л�

Node* FindEnter(List plist);

int Gerlength(List plist);

void Show(List plist);//��ӡ������

void Show2(Node* reverHead);    //�����ת���

#include"Link.h"
#include<stdlib.h>
#include<assert.h>
void InitList(List plist)//��ʼ��������
{
	assert(plist != NULL);
	plist->next = NULL;
}

static Node* GetNode(int val)
{
	Node* pGet = (Node*)malloc(sizeof(Node));
	assert(pGet != NULL);
	pGet->date = val;
	pGet->next = NULL;
	return pGet;
}

bool Insert_head(List plist, int val)//ͷ�巨
{
	assert(plist != NULL);
	Node* pGet = GetNode(val);
	pGet->next = plist->next;
	plist->next = pGet;
	return true;
}

bool Insert_tail(List plist, int val)//β�巨
{
	assert(plist != NULL);
	Node* cur = plist;    //ָ��ͷ���   ����ǰ����Ϣ��
	Node* pGet = GetNode(val);
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = pGet;
	return true;
}

bool Insert_pos(List plist, int pos, int val)//pos λ�ò���
{
	assert(plist != NULL);
	Node* cur = plist;
	int i = 0;
	while (i < pos)
	{
		cur = cur->next;
		i++;
	}
	Node* pGet = GetNode(val);
	pGet->next = cur->next;
	cur->next = pGet;
	return true;
}

static bool isEmpty(List plist)
{
	if (plist == NULL || plist->next == NULL)
	{
		return true;
	}
	return false;
}

Node* Search_pre(List plist, int key)//���� key ��ǰ��
{
	assert(plist != NULL);
	if (isEmpty(plist))
	{
		return NULL;
	}
	Node* cur = plist;
	while (cur->next != NULL)
	{
		if (cur->next->date == key)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

bool Delete(List plist, int key)//ɾ�� key ������
{
	assert(plist != NULL);
	Node* cur = Search_pre(plist, key);
	if (cur == NULL)
	{
		return false;
	}
	Node* p = plist->next;
	while (p != NULL)
	{
		if (p->date == key)
		{
			cur->next = p->next;
			free(p);
			p = NULL;
			return true;
		}
		p = p->next;
	}
	return false;
}

void Destroy(List plist)//�ݻٺ���������ж�̬�����ڴ棩
{
	assert(plist != NULL);
	while (plist->next != NULL)
	{
		Node* s = plist->next;
		plist->next = s->next;
		free(s);
		s = NULL;
	}
	return;
}

int GetLength(List plist)//�õ�������ĳ���
{
	assert(plist != NULL);
	int count = 0;   //������
	Node* cur = plist->next;
	while (cur != NULL)
	{
		count++;
		cur = cur->next;
	}
	return count;
}

bool Reaserve_LIst(List plist)   //���õ�����
{
	assert(plist != NULL);
	Node* cur = plist->next;
	plist->next = NULL;
	while (cur != NULL)
	{
		Node* s = cur;
		cur = cur->next;
		s->next = plist->next;
		plist->next = s;
	}
	return true;
}
Node* Reverse1(List plist)   //��ת
{
	Node* prev = NULL;      //
	Node* reverHead = NULL;
	Node* cur = plist;
	while (cur != NULL)
	{
		Node* curNext = cur->next;
		if (curNext == NULL)
		{
			reverHead = cur;
		}
		cur->next = prev;//NULL
		prev = cur;
		cur = curNext;
	}
	return reverHead;
}

Node* LastK(List plist, int k)   //���ʱ�����ҵ�����������K���ڵ�
{
	if (k < 0 || plist == NULL)
	{
		return NULL;
	}
	Node* p1 = plist;
	Node* p2 = plist;
	while (k - 1 > 0)
	{
		if (p1->next != NULL)
		{
			p1 = p1->next;
			--k;
		}
		else
		{
			return NULL;
		}
	}
	while (p1->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	return p2->next;
}

void DeleteLastK(List plist, int k)//���ʱ����ɾ������������K���ڵ�
{
	if (k < 0 || plist == NULL)
	{
		return;
	}
	Node* p1 = plist;
	Node* p2 = plist;
	while (k > 0)
	{
		if (p1->next != NULL)
		{
			p1 = p1->next;
			--k;
		}
		else
		{
			return;
		}
	}
	while (p1->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	Node* pDel = p2->next;
	p2->next = pDel->next;
	free(pDel);
	pDel = NULL;
}

void DeleteNode(List plist, Node* pDel)//O(1)ʱ��ɾ���������һ���ڵ� 
{
	assert(plist != NULL && pDel != NULL);
	if (pDel->next != NULL)
	{
		Node* pDelNext = pDel->next;
		pDel->date = pDelNext->date;
		pDel->next = pDelNext->next;
		free(pDelNext);
	}
	else
	{
		Node* pCur = plist;
		while (pCur->next != pDel)
		{
			pCur = pCur->next;
		}
		pCur->next = NULL;
		free(pDel);
	}
}


Node* Add_List(List plist, List plist2)//�ϲ�������������  
{
	assert(plist != NULL && plist2 != NULL);
	Node* p = plist->next;
	Node* q = plist2->next;
	Node* newhead = NULL;
	if (p->date < q->date)
	{
		newhead = plist;
	}
	else
	{
		newhead = plist2;
	}
	Node* temhead = newhead;
	while (p != NULL && q != NULL)
	{
		if (p->date >= q->date)
		{
			temhead->next = q;
			q = q->next;
		}
		else
		{

			temhead->next = p;
			p = p->next;
		}
		temhead = temhead->next;
	}
	if (p != NULL)
	{
		temhead->next = p;
	}
	if (q != NULL)
	{
		temhead->next = q;
	}
	return newhead;
}
static void Creat_loop(List plist)
{
	Node* p = plist;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = plist->next->next->next;
	return;
}
bool IsLoop(List plist)
{
	assert(plist != NULL);
	Creat_loop(plist);
	Node* pf = plist;
	Node* ps = plist;
	while (pf != NULL && pf->next != NULL)
	{
		ps = ps->next;
		pf = pf->next->next;
		if (pf == ps)
		{
			break;
		}
	}
	if (pf == NULL || pf->next == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Node* FindEnter(List plist)
{
	assert(plist != NULL);
	Creat_loop(plist);
	Node* pf = plist;
	Node* ps = plist;
	while (pf != NULL && pf->next != NULL)
	{
		ps = ps->next;
		pf = pf->next->next;
		if (pf == ps)
		{
			break;
		}
	}
	if (pf == NULL || pf->next == NULL)
	{
		return NULL;
	}
	ps = plist;
	while (ps != pf)
	{
		ps = ps->next;
		pf = pf->next;
	}
	return ps;
}

int Gerlength(List plist)
{
	assert(plist != NULL);
	Creat_loop(plist);
	Node* pf = plist;
	Node* ps = plist;
	while (pf != NULL && pf->next != NULL)
	{
		ps = ps->next;
		pf = pf->next->next;
		if (pf == ps)
		{
			break;
		}
	}
	if (pf == NULL || pf->next == NULL)
	{
		return -1;
	}
	int count = 1;
	ps = ps->next;
	while (ps != pf)
	{
		ps = ps->next;
		count++;
	}
	return count;
}

void Show(List plist)//��ӡ������
{
	assert(plist != NULL);
	while (plist->next != NULL)
	{
		plist = plist->next;
		printf("%d ", plist->date);
	}
	printf("\n");
}

void Show2(Node* reverHead)
{
	Node* p = reverHead;
	while (p->next != NULL)
	{
		printf("%d ", p->date);
		p = p->next;
	}
	printf("\n");
}

#include"Link.h"
int main2()
{
	int arr[] = { 12,15,16,18,19,21,25,36,66 };
	int len = sizeof(arr) / sizeof(arr[0]);
	Node mylist;
	InitList(&mylist);
	for (int i = 0; i < len; i++)
	{
		Insert_head(&mylist, arr[i]);
		//Insert_tail(&mylist,arr[i]);
	}
	Show(&mylist);
	//int lenth = GetLength(&mylist);
	//printf("%d\n",lenth);
	//Destroy(&mylist);
	//Reaserve_LIst(&mylist);
	//Show(&mylist);
	//Show(&mylist2);
	//Node * p = Add_List(&mylist,&mylist2);
	//Show(p);
	//Node *p =LastK(&mylist,3);
	//printf("%d\n",p->date);
	//DeleteNode(&mylist,mylist.next->next->next);
	 //Show2(Reverse1(&mylist));
	/*if(!IsLoop(&mylist))
	{
		printf("no\n");
	}
	else
	{
		printf("yes\n");
	}
	Node *p = FindEnter(&mylist);
	printf("%d\n",p->date);*/
	return 0;
}