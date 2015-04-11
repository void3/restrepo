#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

typedef struct mach1 {
  int state; /* state */
} mach1_t;

mach1_t* mach1_create(void)
{
  mach1_t *objp;

  LOGFUNC();

  objp = (mach1_t *)malloc(sizeof(mach1_t));
  objp->state = 0;

  return objp;
}

void mach1_destroy(mach1_t *objp)
{
  LOGFUNC();

  free(objp);
}

void mach1_in(mach1_t *objp, int in)
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
      perror("mach1_in: illigal state");
  }
  printf("mach1(%d)", objp->state);
}

#ifdef DEBUG
int main()
{
  mach1_t *obj1p;
  int i, ret;

  LOGFUNC();

  obj1p = mach1_create();
  if (!obj1p) {
    perror("create error");
  }

  for (i = 0; i < 10; i++) { /* left */
    printf("%d:", i);
    mach1_in(obj1p, 0);
  }

  for (i = 0; i < 10; i++) { /* right */
    printf("%d:", i);
    mach1_in(obj1p, 1);
  }

  mach1_destroy(obj1p);
  printf("hoge");

  return 0;
}
#endif /* DEBUG */
