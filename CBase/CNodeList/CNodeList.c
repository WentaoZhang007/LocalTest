/*****************************************************
Author��Simon_Kly    Version:0.1    Date:20170520
Description����ͷ�ӵ�ĵ�����
Funcion List:
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}Node, *Link;

/*�ж�malloc�Ƿ���ȷִ��*/
void is_malloc_ok(Link head)
{
	if (head == NULL)
	{
		printf("malloc error!\n");
		exit(-1);
	}
}

/*��������*/
void create_link(Link * head)
{
	*head = (Link)malloc(sizeof(Node));
	is_malloc_ok(*head);
	(*head)->next = NULL;
}

/*�����ڵ�*/
void create_node(Link * new_node)
{
	*new_node = (Link)malloc(sizeof(Node));
	is_malloc_ok(*new_node);
}

/*����ڵ�β��*/
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

/*����ڵ�ͷ��*/
void insert_node_head(Link head, Link new_node)
{
	Link p = NULL;

	p = head;

	new_node->next = head->next;
	head->next = new_node;
}

/*��ӡ�ڵ�*/
void output_link(Link head)
{
	Link p = NULL;


	if (head == NULL)
	{//����
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

/*�ÿ���*/
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

/*�ͷ�����*/
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

	/*β��*/
	for (i = 0; i < 10; i++)
	{
		create_node(&new_node);
		new_node->data = i + 1;
		insert_node_tail(head, new_node);
	}
	output_link(head);

	/*ͷ��*/
	create_node(&new_node);
	new_node->data = 20;
	insert_node_head(head, new_node);
	output_link(head);

	/*�ͷ�����׶�*/
	release_link(&head);
	output_link(head);
	return 0;
}