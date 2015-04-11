#include <stdio.h>
#include <stdlib.h>

#include "machine.h"

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

typedef struct list {
  struct list *next;
  void        *member;
} list_t;

/* append elem to head list */
int list_insert(list_t *head, list_t *elem)
{
  list_t *p;
  
  if (head == NULL) {
	head->member = elem->member;
    head->next   = NULL;
  } else {  
    for (p = head; p->next; p = p->next); /* find the last element */
    p->next = elem;                       /* append element */
    elem->next = NULL;
  }
  
  return 1;
  
}

/* remove elem from head list */
int list_delete(list_t *head, list_t *elem)
{
  list_t *p, *prev;

  for (p = head, prev = NULL; p->next; prev = p, p = p->next) {
    if (p == elem) {
      printf("found %d\n", p->member);
	  if (prev == NULL) { /* head change */
        printf("head is changed\n");
      } else {
        printf("removing %d->%d->%d\n", prev->member, elem->member, elem->next->member);
        prev->next = p->next;
      }
      return 1;	  
    }
  }
  printf("not found\n");
  return -1;
}

void list_show(list_t *head)
{
	list_t *p;
    for (p = head->next; p; p = p->next) {
      printf("%d ", (int)p->member);
	}
}

int main()
{
	list_t head;
	list_t a, b, c;

    head.next = NULL;
    head.member = 0;
    list_show(&head);
    a.member=1; a.next=NULL;list_insert(&head, &a);
    list_show(&head);
    b.member=2; b.next=NULL;list_insert(&head, &b);
    list_show(&head);
    c.member=3; c.next=NULL;list_insert(&head, &c);
    list_show(&head);
    list_delete(&head, &b);
    list_show(&head);
    list_delete(&head, &a);
    list_show(&head);
    
    return 0;
}

