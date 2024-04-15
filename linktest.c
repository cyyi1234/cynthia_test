#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct List
{
	int  data;
	struct List *next;
}list,*p_list;
 
void creat_list(list **p)//如果链表为空，则创建一个链表，指针域指向自己，否则寻找尾节点，将
{						 //将尾节点的指针域指向这个新节点，新节点的指针域指向头结点
	int item;
	list *temp;
	list *target;
	printf("输入节点的值，输入0结束\n");
	while(1)
	{
		scanf("%d",&item);
		if(item==0)return;
 
		if(*p==NULL)   //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己  (*head)->next=*head;
		{
			*p=(list *)malloc(sizeof(list));
			if(!*p)exit(0);
			(*p)->data=item;
			(*p)->next=*p;
		}
		else		//输入的链表不是空的，寻找链表的尾节点，使尾节点的next=新节点。新节点的next指向头节点
		{
			for(target=*p;target->next!=*p;target=target->next);//寻找尾节点
 
			temp=(list *)malloc(sizeof(list));
			if(!temp)exit(0);
			temp->data=item;
			temp->next=*p;  //新节点指向头节点
			target->next=temp;//尾节点指向新节点
		}
	}
}
void show(list *p)//遍历，循环链表的遍历最好用do while语句 ，因为头节点就有值
{
	list *temp;
	temp=p;
	do
	{
		printf("%5d",temp->data);
		temp=temp->next;	
	}
	while(temp!=p);
 
	printf("\n");
}
