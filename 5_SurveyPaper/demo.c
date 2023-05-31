#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct student
{
    int roll_no;
    char name[50];
    struct student *next;
};

void push(struct node **head, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = (*head);
    (*head) = new_node;
}

void display_SLL(struct node *head)
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int linear_search(struct node *head, int key)
{
    int pos = 0;
    struct node *ptr = head;
    while (ptr != NULL)
    {
        pos++;
        if (ptr->data == key)
            return pos;
        ptr = ptr->next;
    }
    return -1;
}

void concat_SLL(struct node **head1, struct node **head2)
{
    if (*head1 == NULL)
    {
        *head1 = *head2;
        return;
    }
    if (*head2 == NULL)
        return;
    struct node *ptr = *head1;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = *head2;
}

void enqueue(struct student **front, struct student **rear, struct student *s)
{
    struct student *new_node = (struct student *)malloc(sizeof(struct student));
    new_node = s;
    new_node->next = NULL;
    if (*front == NULL)
    {
        *front = new_node;
        *rear = new_node;
        return;
    }
    (*rear)->next = new_node;
    *rear = new_node;
}

void display_queue(struct student *front)
{
    struct student *ptr = front;
    while (ptr != NULL)
    {

        printf("%d %s\n", ptr->roll_no, ptr->name);
        ptr = ptr->next;
    }
}

int main()
{
    int n;
    printf("Enter the number of elements in Stack: ");
    scanf("%d", &n);
    struct node *stack = NULL;
    for (int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        push(&stack, temp);
    }
    printf("Stack elements are: ");
    display_SLL(stack);
    int key;
    printf("Enter the element to search: ");
    scanf("%d", &key);
    int pos = linear_search(stack, key);
    if (pos == -1)
        printf("%d not found in the stack.\n", key);
    else
        printf("%d found at position %d in the stack.\n", key, pos);
    printf("Enter the number of elements in second stack: ");
    scanf("%d", &n);
    struct node *stack2 = NULL;
    for (int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        push(&stack2, temp);
    }
    printf("Second stack elements are: ");
    display_SLL(stack2);
    concat_SLL(&stack, &stack2);
    printf("After concatenation: ");
    display_SLL(stack);
    printf("Enter the number of students in queue: ");
    scanf("%d", &n);
    struct student *front = NULL;
    struct student *rear = NULL;
    printf("Enter the details of students: Roll no and Name\n");
    struct student *s;
    for (int i = 0; i < n; i++)
    {
        s = (struct student *)malloc(sizeof(struct student));
        scanf("%d", &s->roll_no);
        scanf("%s", s->name);
        enqueue(&front, &rear, s);
    }
    printf("Queue elements are:\n");
    display_queue(front);
    return 0;
}