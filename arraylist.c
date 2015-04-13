#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

#define ELEM_MAX 10

typedef struct elem {
  int  number;
  char *member;
} elem_t;

/* append elem to head list */
int list_insert(elem_t *list, char *elem)
{
  int i;
  
  LOGFUNC();
  
  for (i = 0; i < ELEM_MAX; i++) {
    if (list[i].member == NULL) {
      list[i].member = elem;
      return 1;
	}
  }
  printf("add:full\n");
  return -1;
}

/* remove elem from head list */
int list_delete(elem_t *list, char *elem)
{
  int i, j;

  LOGFUNC();
  
  for (i = 0; i < ELEM_MAX; i++) {
  printf("list = %p\n", list);
  printf("%d comparing(%p,%p)\n", i, list[i].member, elem);
    if (list[i].member == elem) { /* found elem */
      for (j = i; j < ELEM_MAX-1; j++) { /* shift left elem */ 
        list[j].member = list[j+1].member;
      }
      list[j].member = NULL;
      printf("move end\n");
      return 1;
	}
  }
  printf("delete:not found\n");
  return -1;
}

/* show list */
void list_show(elem_t *list)
{
	int i;

  LOGFUNC();
  for (i = 0; i < ELEM_MAX && list[i].member != NULL; i++) {
      printf("(%d)", i);
      printf("(%p)", list[i]);
      if (list[i].member != NULL) printf("%c ", *(list[i].member));
	}
  printf("end");
}

int main()
{
	elem_t array[ELEM_MAX];
	char c[ELEM_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; 
    int i;

// DEBUG
    for (i = 0; i < ELEM_MAX; i++) {
		array[i].member = &c[i];
        printf("%p %c&%p %c", array[i].member, *array[i].member, &c[i], c[i]);
	}
    printf("array=%p array[0]=%p array[0].member=%p\n", array, &array[0], array[0].member);

    list_delete(&array, &c[1]);
    list_show(&array);
    list_delete(&array, &c[0]);
    list_show(&array);
    list_insert(&array, &c[1]);
    list_show(&array);

    return 0;
}

