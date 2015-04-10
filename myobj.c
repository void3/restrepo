#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

typedef struct myobj {
  int state; /* state */
} myobj_t;

myobj_t* myobj_create(void)
{
  myobj_t *objp;

  LOGFUNC();

  objp = (myobj_t *)malloc(sizeof(myobj_t));
  objp->state = 0;

  return objp;
}

void myobj_destroy(myobj_t *objp)
{
  LOGFUNC();

  free(objp);
}

void myobj_in(myobj_t *objp, int in)
{
  int oldstate;

  LOGFUNC();

  switch (objp->state) {
    case 0:
      objp->state = 1;
      break;
    case 1:
      if(in == 0) { objp->state = 2; } else { objp->state = 3; }
      break;
    case 2:
      if(in == 0) { objp->state = 3; } else { objp->state = 1; }
      break;
    case 3:
      if(in == 0) { objp->state = 1; } else { objp->state = 2; }
      break;
    default:
      perror("myobj_in: illigal state");
  }
  printf("new state = %d\n", objp->state);
}

int main()
{
  myobj_t *obj1p;
  int i, ret;

  LOGFUNC();

  obj1p = myobj_create();
  if (!obj1p) {
    perror("create error");
  }

  for (i = 0; i < 10; i++) { /* left */
    printf("%d:", i);
    myobj_in(obj1p, 0);
  }

  for (i = 0; i < 10; i++) { /* right */
    printf("%d:", i);
    myobj_in(obj1p, 1);
  }

  myobj_destroy(obj1p);

  return 0;
}
