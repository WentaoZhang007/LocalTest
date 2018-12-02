/*****************************************************
Author：Simon_Kly    Version:0.1    Date:20170520
Description：带头接点的单链表
Funcion List:
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}Node, *Link;

/*判断malloc是否正确执行*/
void is_malloc_ok(Link head)
{
	if (head == NULL)
	{
		printf("malloc error!\n");
		exit(-1);
	}
}

/*建立链表*/
void create_link(Link * head)
{
	*head = (Link)malloc(sizeof(Node));
	is_malloc_ok(*head);
	(*head)->next = NULL;
}

/*创建节点*/
void create_node(Link * new_node)
{
	*new_node = (Link)malloc(sizeof(Node));
	is_malloc_ok(*new_node);
}

/*插入节点尾插*/
void insert_node_tail(Link head, Link new_node)
{
	Link p = NULL;

	p = head;

	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = new_node;
	new_node->next = NULL;
}

/*插入节点头插*/
void insert_node_head(Link head, Link new_node)
{
	Link p = NULL;

	p = head;

	new_node->next = head->next;
	head->next = new_node;
}

/*打印节点*/
void output_link(Link head)
{
	Link p = NULL;


	if (head == NULL)
	{//空链
		printf("link is empty!\n");
		return;
	}

	p = head->next;
	while (p != NULL)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}

/*置空链*/
void make_empty_link(Link *head)
{
	Link p = NULL;

	p = (*head)->next;

	while ((*head)->next != NULL)
	{
		(*head)->next = (*head)->next->next;
		free(p);
		p = (*head)->next;
	}
}

/*释放链表*/
void release_link(Link * head)
{
	make_empty_link(head);
	free(*head);
	*head = NULL;
}

int main()
{
	int i;

	Link head = NULL;
	Link new_node = NULL;

	create_link(&head);

	/*尾插*/
	for (i = 0; i < 10; i++)
	{
		create_node(&new_node);
		new_node->data = i + 1;
		insert_node_tail(head, new_node);
	}
	output_link(head);

	/*头插*/
	create_node(&new_node);
	new_node->data = 20;
	insert_node_head(head, new_node);
	output_link(head);

	/*释放链表阶段*/
	release_link(&head);
	output_link(head);
	return 0;
}