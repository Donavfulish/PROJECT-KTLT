#include <iostream>
#include "Struct.h"

str_node* createNode(int data)
{
	str_node* new_node = new str_node;
	new_node->val = data;
	return new_node;
}

void addTail(str_linkedList& list, int data)
{
	list.width++;
	str_node* new_node = createNode(data);
	// 0 1 2 3
	if (list.pHead == NULL || list.pTail == NULL)
	{
		list.pHead = new_node;
		list.pTail = new_node;
		list.pTail->pNext = nullptr;
		return;
	}
	else
	{
		list.pTail->pNext = new_node;
		list.pTail = new_node;
		list.pTail->pNext = nullptr;
	}
}

void removeHead(str_linkedList& list)
{
	if (list.pHead == NULL) return;
	str_node* pTemp = list.pHead;
	list.pHead = pTemp->pNext;
	pTemp->pNext = nullptr;
	delete pTemp;
	list.width--;
}

void removeAtK(str_linkedList& list, int k)
{
	str_node* pPrev = nullptr;
	str_node* pCurr = list.pHead;
	if (k == 1)
	{
		removeHead(list);
		return;
	}
	for (int i = 1; i < k; i++)
	{
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
	pPrev->pNext = pCurr->pNext;
	pCurr->pNext = nullptr;

	delete pCurr;
	list.width--;
}

void deleteLinkedList(str_linkedList& list)
{
	while (list.pHead != NULL)
	{
		removeHead(list);
	}
}